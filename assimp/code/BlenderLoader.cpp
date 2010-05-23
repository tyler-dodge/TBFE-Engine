/*
Open Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2010, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

/** @file  BlenderLoader.cpp
 *  @brief Implementation of the Blender3D importer class.
 */
#include "AssimpPCH.h"

#ifndef ASSIMP_BUILD_NO_BLEND_IMPORTER
#include "BlenderLoader.h"
#include "BlenderDNA.h"
#include "BlenderScene.h"
#include "BlenderSceneGen.h"

#include "StreamReader.h"
#include "TinyFormatter.h"

//#include <boost/make_shared.hpp>

using namespace Assimp;
using namespace Assimp::Blender;
using namespace Assimp::Formatter;

#define for_each(x,y) BOOST_FOREACH(x,y)

static const aiLoaderDesc blenderDesc = {
	"Blender 3D Importer \nhttp://www.blender3d.org",
	"Alexander Gessler <alexander.gessler@gmx.net>",
	"",
	"",
	aiLoaderFlags_SupportBinaryFlavour | aiLoaderFlags_Experimental,
	0,
	0,
	2,
	50
};

namespace Assimp {
namespace Blender {

	/** Mini smart-array to avoid pulling in even more boost stuff. usable with vector and deque */
	template <template <typename,typename> class TCLASS, typename T>
	struct TempArray	{

		TempArray() {
		}

		~TempArray () {
			for_each(T* elem, arr) {
				delete elem;
			}
		}

		void dismiss() {
			arr.clear();
		}

		TCLASS< T*,std::allocator<T*> >* operator -> () {
			return &arr;
		}

		operator TCLASS< T*,std::allocator<T*> > () {
			return arr;
		}

		TCLASS< T*,std::allocator<T*> >& get () {
			return arr;
		}

		const TCLASS< T*,std::allocator<T*> >& get () const {
			return arr;
		}

		T* operator[] (size_t idx) const {
			return arr[idx];
		}

	private:
		// no copy semantics
		void operator= (const TempArray&)  {
		}

		TempArray(const TempArray& arr) {
		}

	private:
		TCLASS< T*,std::allocator<T*> > arr;
	};
	
	/** ConversionData acts as intermediate storage location for
	 *  the various ConvertXXX routines in BlenderImporter.*/
	struct ConversionData	{
		std::set<const Object*> objects;

		TempArray <std::vector, aiMesh> meshes;
		TempArray <std::vector, aiCamera> cameras;
		TempArray <std::vector, aiLight> lights;
		TempArray <std::vector, aiMaterial> materials;

		// set of all materials referenced by at least one mesh in the scene
		std::deque< boost::shared_ptr< Material > > materials_raw;
	};
}
}

// ------------------------------------------------------------------------------------------------
// Constructor to be privately used by Importer
BlenderImporter::BlenderImporter()
{}

// ------------------------------------------------------------------------------------------------
// Destructor, private as well 
BlenderImporter::~BlenderImporter()
{}

// ------------------------------------------------------------------------------------------------
// Returns whether the class can handle the format of the given file. 
bool BlenderImporter::CanRead( const std::string& pFile, IOSystem* pIOHandler, bool checkSig) const
{
	const std::string& extension = GetExtension(pFile);
	if (extension == "blend") {
		return true;
	}

	else if ((!extension.length() || checkSig) && pIOHandler)	{
		const char* tokens[] = {"BLENDER"};
		return SearchFileHeaderForToken(pIOHandler,pFile,tokens,1);
	}
	return false;
}

// ------------------------------------------------------------------------------------------------
// List all extensions handled by this loader
void BlenderImporter::GetExtensionList(std::set<std::string>& app) 
{
	app.insert("blend");
}

// ------------------------------------------------------------------------------------------------
// Loader registry entry
const aiLoaderDesc& BlenderImporter::GetInfo () const
{
	return blenderDesc;
}

// ------------------------------------------------------------------------------------------------
// Setup configuration properties for the loader
void BlenderImporter::SetupProperties(const Importer* pImp)
{
	// nothing to be done for the moment
}

// ------------------------------------------------------------------------------------------------
// Imports the given file into the given scene structure. 
void BlenderImporter::InternReadFile( const std::string& pFile, 
	aiScene* pScene, IOSystem* pIOHandler)
{
	FileDatabase file; 
	boost::shared_ptr<IOStream> stream(pIOHandler->Open(pFile,"rb"));
	if (!stream) {
		ThrowException("Could not open file for reading");
	}

	char magic[8] = {0};
	stream->Read(magic,7,1);
	if (strcmp(magic,"BLENDER")) {
		ThrowException("BLENDER magic bytes are missing");
	}

	file.i64bit = (stream->Read(magic,1,1),magic[0]=='-');
	file.little = (stream->Read(magic,1,1),magic[0]=='v');

	stream->Read(magic,3,1);
	magic[3] = '\0';

	LogInfo((format(),"Blender version is ",magic[0],".",magic+1,
		" (64bit: ",file.i64bit?"true":"false",
		", little endian: ",file.little?"true":"false",")"
	));

	ParseBlendFile(file,stream);

	Scene scene;
	ExtractScene(scene,file);

	ConvertBlendFile(pScene,scene);
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::ParseBlendFile(FileDatabase& out, boost::shared_ptr<IOStream> stream) 
{
	out.reader = boost::shared_ptr<StreamReaderAny>(new StreamReaderAny(stream,out.little));

	DNAParser dna_reader(out);
	const DNA* dna = NULL;

	out.entries.reserve(128); { // even small BLEND files tend to consist of many file blocks
		SectionParser parser(*out.reader.get(),out.i64bit);

		// first parse the file in search for the DNA and insert all other sections into the database
		while ((parser.Next(),1)) {
			const FileBlockHead& head = parser.GetCurrent();

			if (head.id == "ENDB") {
				break; // only valid end of the file
			}
			else if (head.id == "DNA1") {
				dna_reader.Parse();
				dna = &dna_reader.GetDNA();
				continue;
			}

			out.entries.push_back(head);
		}
	}
	if (!dna) {
		ThrowException("SDNA not found");
	}

	std::sort(out.entries.begin(),out.entries.end());
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::ExtractScene(Scene& out, const FileDatabase& file) 
{
	const FileBlockHead* block = NULL;
	std::map<std::string,size_t>::const_iterator it = file.dna.indices.find("Scene");
	if (it == file.dna.indices.end()) {
		ThrowException("There is no `Scene` structure record");
	}

	const Structure& ss = file.dna.structures[(*it).second];

	// we need a scene somewhere to start with. 
	for_each(const FileBlockHead& bl,file.entries) {
		if (bl.id == "SC") {
			block = &bl;
			break;
		}
	}

	if (!block) {
		ThrowException("There is not a single `Scene` record to load");
	}

	file.reader->SetCurrentPos(block->start);
	ss.Convert(out,file);

#ifndef ASSIMP_BUILD_BLENDER_NO_STATS
	DefaultLogger::get()->info((format(),
		"(Stats) Fields read: "	,file.stats().fields_read,
		", pointers resolved: "	,file.stats().pointers_resolved,  
		", cache hits: "        ,file.stats().cache_hits,  
		", cached objects: "	,file.stats().cached_objects
	));
#endif
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::ConvertBlendFile(aiScene* out, const Scene& in) 
{
	ConversionData conv;

	// FIXME it must be possible to take the hierarchy directly from
	// the file. This is terrible. Here, we're first looking for
	// all objects which don't have parent objects at all -
	std::deque<const Object*> no_parents;
	for (boost::shared_ptr<Base> cur = boost::static_pointer_cast<Base> ( in.base.first ); cur; cur = cur->next) {
		if (cur->object) {
			if(!cur->object->parent) {
				no_parents.push_back(cur->object.get());
			}
			else conv.objects.insert(cur->object.get());
		}
	}
	for (boost::shared_ptr<Base> cur = in.basact; cur; cur = cur->next) {
		if (cur->object) {
			if(cur->object->parent) {
				conv.objects.insert(cur->object.get());
			}
		}
	}

	if (no_parents.empty()) {
		ThrowException("Expected at least one object with no parent");
	}

	aiNode* root = out->mRootNode = new aiNode("<BlenderRoot>");

	root->mNumChildren = static_cast<unsigned int>(no_parents.size());
	root->mChildren = new aiNode*[root->mNumChildren]();
	for (unsigned int i = 0; i < root->mNumChildren; ++i) {
		root->mChildren[i] = ConvertNode(in, no_parents[i], conv);	
		root->mChildren[i]->mParent = root;
	}

	BuildMaterials(conv);

	if (conv.meshes->size()) {
		out->mMeshes = new aiMesh*[out->mNumMeshes = static_cast<unsigned int>( conv.meshes->size() )];
		std::copy(conv.meshes->begin(),conv.meshes->end(),out->mMeshes);
		conv.meshes.dismiss();
	}

	if (conv.lights->size()) {
		out->mLights = new aiLight*[out->mNumLights = static_cast<unsigned int>( conv.lights->size() )];
		std::copy(conv.lights->begin(),conv.lights->end(),out->mLights);
		conv.lights.dismiss();
	}

	if (conv.cameras->size()) {
		out->mCameras = new aiCamera*[out->mNumCameras = static_cast<unsigned int>( conv.cameras->size() )];
		std::copy(conv.cameras->begin(),conv.cameras->end(),out->mCameras);
		conv.cameras.dismiss();
	}

	if (conv.materials->size()) {
		out->mMaterials = new aiMaterial*[out->mNumMaterials = static_cast<unsigned int>( conv.materials->size() )];
		std::copy(conv.materials->begin(),conv.materials->end(),out->mMaterials);
		conv.materials.dismiss();
	}


	// acknowledge that the scene might come out incomplete
	// by Assimps definition of `complete`: blender scenes
	// can consist of thousands of cameras or lights with
	// not a single mesh between them.
	if (!out->mNumMeshes) {
		out->mFlags |= AI_SCENE_FLAGS_INCOMPLETE;
	}
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::BuildMaterials(ConversionData& conv_data) 
{
	conv_data.materials->reserve(conv_data.materials_raw.size());

	// add a default material if necessary
	unsigned int index = static_cast<unsigned int>( -1 );
	for_each( aiMesh* mesh, conv_data.meshes.get() ) {
		if (mesh->mMaterialIndex == static_cast<unsigned int>( -1 )) {

			if (index == static_cast<unsigned int>( -1 )) {

				// ok, we need to add a dedicated default material for some poor material-less meshes
				boost::shared_ptr<Material> p(new Material());
				strcpy( p->id.name, "$AssimpDefault" );

				p->r = p->g = p->b = 0.6f;
				p->specr = p->specg = p->specb = 0.6f;
				p->ambir = p->ambig = p->ambib = 0.0f;
				p->emit = 0.f;
				p->alpha = 0.f;

				// XXX add more / or add default c'tor to Material

				index = static_cast<unsigned int>( conv_data.materials_raw.size() );
				conv_data.materials_raw.push_back(p);

				LogInfo("Adding default material ...");
			}
			mesh->mMaterialIndex = index;
		}
	}

	for_each(boost::shared_ptr<Material> mat, conv_data.materials_raw) {
	
		MaterialHelper* mout = new MaterialHelper();
		conv_data.materials->push_back(mout);

		// set material name
		aiString name = aiString(mat->id.name);
		mout->AddProperty(&name,AI_MATKEY_NAME);


		// basic material colors
		aiColor3D col(mat->r,mat->g,mat->b);
		mout->AddProperty(&col,1,AI_MATKEY_COLOR_DIFFUSE);

		col = aiColor3D(mat->specr,mat->specg,mat->specb);
		mout->AddProperty(&col,1,AI_MATKEY_COLOR_SPECULAR);

		col = aiColor3D(mat->ambir,mat->ambig,mat->ambib);
		mout->AddProperty(&col,1,AI_MATKEY_COLOR_AMBIENT);
	}
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::CheckActualType(const ElemBase* dt, const char* check)
{
	ai_assert(dt);
	if (strcmp(dt->dna_type,check)) {
		ThrowException((format(),
			"Expected object at ",std::hex,dt," to be of type `",check, 
			"`, but it claims to be a `",dt->dna_type,"`instead"
		));
	}
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::NotSupportedObjectType(const Object* obj, const char* type)
{
	LogWarn((format(), "Object `",obj->id.name,"` - type is unsupported: `",type, "`, skipping" ));
}

// ------------------------------------------------------------------------------------------------
void BlenderImporter::ConvertMesh(const Scene& in, const Object* obj, const Mesh* mesh, 
	ConversionData& conv_data, TempArray<std::vector,aiMesh>&  temp
	) 
{
	typedef std::pair<const int,size_t> MyPair;
	if (!mesh->totface || !mesh->totvert) {
		return;
	}

	// some sanity checks
	if (mesh->totface > mesh->mface.size() ){
		ThrowException("Number of faces is larger than the corresponding array");
	}

	if (mesh->totvert > mesh->mvert.size()) {
		ThrowException("Number of vertices is larger than the corresponding array");
	}

	// collect per-submesh numbers
	std::map<int,size_t> per_mat;
	for (int i = 0; i < mesh->totface; ++i) {

		const MFace& mf = mesh->mface[i];
		per_mat[ mf.mat_nr ]++;
	}

	// ... and allocate the corresponding meshes
	const size_t old = temp->size();
	temp->reserve(temp->size() + per_mat.size());

	std::map<size_t,size_t> mat_num_to_mesh_idx;
	for_each(MyPair& it, per_mat) {

		mat_num_to_mesh_idx[it.first] = temp->size();
		temp->push_back(new aiMesh());

		aiMesh* out = temp->back();
		out->mVertices = new aiVector3D[it.second*4];
		out->mNormals  = new aiVector3D[it.second*4];

		//out->mNumFaces = 0
		//out->mNumVertices = 0
		out->mFaces = new aiFace[it.second]();

		// all submeshes created from this mesh are named equally. this allows
		// curious users to recover the original adjacency.
		out->mName = aiString(mesh->id.name);

		// resolve the material reference and add this material to the set of
		// output materials. The (temporary) material index is the index 
		// of the material entry within the list of resolved materials.
		if (mesh->mat) {

			if (it.first >= mesh->mat.size() ) {
				ThrowException("Material index is out of range");
			}

			boost::shared_ptr<Material> mat = mesh->mat[it.first];
			const std::deque< boost::shared_ptr<Material> >::iterator has = std::find(
					conv_data.materials_raw.begin(),
					conv_data.materials_raw.end(),mat
			);

			if (has != conv_data.materials_raw.end()) {
				out->mMaterialIndex = static_cast<unsigned int>( std::distance(conv_data.materials_raw.begin(),has));
			}
			else {
				out->mMaterialIndex = static_cast<unsigned int>( conv_data.materials_raw.size() );
				conv_data.materials_raw.push_back(mat);
			}
		}
		else out->mMaterialIndex = static_cast<unsigned int>( -1 );
	}

	for (int i = 0; i < mesh->totface; ++i) {

		const MFace& mf = mesh->mface[i];

		aiMesh* const out = temp[ mat_num_to_mesh_idx[ mf.mat_nr ] ];
		aiFace& f = out->mFaces[out->mNumFaces++];

		f.mIndices = new unsigned int[ f.mNumIndices = mf.v4?4:3 ];
		aiVector3D* vo = out->mVertices + out->mNumVertices;
		aiVector3D* vn = out->mNormals + out->mNumVertices;

		// XXX we can't fold this easily, because we are restricted
		// to the member names from the BLEND file (v1,v2,v3,v4) ..

		if (mf.v1 >= mesh->totvert) {
			ThrowException("Vertex index v1 out of range");
		}
		const MVert* v = &mesh->mvert[mf.v1];
		vo->x = v->co[0];
		vo->y = v->co[1];
		vo->z = v->co[2];
		vn->x = v->no[0];
		vn->y = v->no[1];
		vn->z = v->no[2];
		f.mIndices[0] = out->mNumVertices++;
		++vo;
		++vn;

		//	if (f.mNumIndices >= 2) {
		if (mf.v2 >= mesh->totvert) {
			ThrowException("Vertex index v2 out of range");
		}
		v = &mesh->mvert[mf.v2];
		vo->x = v->co[0];
		vo->y = v->co[1];
		vo->z = v->co[2];
		vn->x = v->no[0];
		vn->y = v->no[1];
		vn->z = v->no[2];
		f.mIndices[1] = out->mNumVertices++;
		++vo;
		++vn;

		if (mf.v3 >= mesh->totvert) {
			ThrowException("Vertex index v3 out of range");
		}
		//	if (f.mNumIndices >= 3) {
		v = &mesh->mvert[mf.v3];
		vo->x = v->co[0];
		vo->y = v->co[1];
		vo->z = v->co[2];
		vn->x = v->no[0];
		vn->y = v->no[1];
		vn->z = v->no[2];
		f.mIndices[2] = out->mNumVertices++;
		++vo;
		++vn;

		if (mf.v4 >= mesh->totvert) {
			ThrowException("Vertex index v4 out of range");
		}
		//	if (f.mNumIndices >= 4) {
		if (mf.v4) {
			v = &mesh->mvert[mf.v4];
			vo->x = v->co[0];
			vo->y = v->co[1];
			vo->z = v->co[2];
			vn->x = v->no[0];
			vn->y = v->no[1];
			vn->z = v->no[2];
			f.mIndices[3] = out->mNumVertices++;
			++vo;
			++vn;

			out->mPrimitiveTypes |= aiPrimitiveType_POLYGON;
		}
		else out->mPrimitiveTypes |= aiPrimitiveType_TRIANGLE;

		//	}
		//	}
		//	}
	}

	// collect texture coordinates, they're stored in a separate per-face buffer
	if (mesh->mtface) {
		if (mesh->totface > mesh->mtface.size()) {
			ThrowException("Number of UV faces is larger than the corresponding UV face array (#1)");
		}
		for (std::vector<aiMesh*>::iterator it = temp->begin()+old; it != temp->end(); ++it) {
			ai_assert((*it)->mNumVertices && (*it)->mNumFaces);

			(*it)->mTextureCoords[0] = new aiVector3D[(*it)->mNumVertices];
			(*it)->mNumFaces = (*it)->mNumVertices = 0;
		}

		for (int i = 0; i < mesh->totface; ++i) {
			const MTFace* v = &mesh->mtface[i];

			aiMesh* const out = temp[ mat_num_to_mesh_idx[ mesh->mface[i].mat_nr ] ];
			const aiFace& f = out->mFaces[out->mNumFaces++];
			
			aiVector3D* vo = &out->mTextureCoords[0][out->mNumVertices];
			for (unsigned int i = 0; i < f.mNumIndices; ++i,++vo,++out->mNumVertices) {
				vo->x = v->uv[i][0];
				vo->y = v->uv[i][1];
			}
		}
	}

	// collect texture coordinates, old-style (marked as deprecated in current blender sources)
	if (mesh->tface) {
		if (mesh->totface > mesh->mtface.size()) {
			ThrowException("Number of faces is larger than the corresponding UV face array (#2)");
		}
		for (std::vector<aiMesh*>::iterator it = temp->begin()+old; it != temp->end(); ++it) {
			ai_assert((*it)->mNumVertices && (*it)->mNumFaces);

			(*it)->mTextureCoords[0] = new aiVector3D[(*it)->mNumVertices];
			(*it)->mNumFaces = (*it)->mNumVertices = 0;
		}

		for (int i = 0; i < mesh->totface; ++i) {
			const TFace* v = &mesh->tface[i];

			aiMesh* const out = temp[ mat_num_to_mesh_idx[ mesh->mface[i].mat_nr ] ];
			const aiFace& f = out->mFaces[out->mNumFaces++];
			
			aiVector3D* vo = &out->mTextureCoords[0][out->mNumVertices];
			for (unsigned int i = 0; i < f.mNumIndices; ++i,++vo,++out->mNumVertices) {
				vo->x = v->uv[i][0];
				vo->y = v->uv[i][1];
			}
		}
	}

	// collect vertex colors, stored separately as well
	if (mesh->mcol) {
		if (mesh->totface > (mesh->mcol.size()/4)) {
			ThrowException("Number of faces is larger than the corresponding color face array");
		}
		for (std::vector<aiMesh*>::iterator it = temp->begin()+old; it != temp->end(); ++it) {
			ai_assert((*it)->mNumVertices && (*it)->mNumFaces);

			(*it)->mColors[0] = new aiColor4D[(*it)->mNumVertices];
			(*it)->mNumFaces = (*it)->mNumVertices = 0;
		}

		for (int i = 0; i < mesh->totface; ++i) {

			aiMesh* const out = temp[ mat_num_to_mesh_idx[ mesh->mface[i].mat_nr ] ];
			const aiFace& f = out->mFaces[out->mNumFaces++];
			
			aiColor4D* vo = &out->mColors[0][out->mNumVertices];
			for (unsigned int n = 0; n < f.mNumIndices; ++n, ++vo,++out->mNumVertices) {
				const MCol* col = &mesh->mcol[(i<<2)+n];

				vo->r = col->r;
				vo->g = col->g;
				vo->b = col->b;
				vo->a = col->a;
			}
			for (unsigned int n = f.mNumIndices; n < 4; ++n);
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
aiCamera* BlenderImporter::ConvertCamera(const Scene& in, const Object* obj, const Camera* mesh, ConversionData& conv_data) 
{
	ScopeGuard<aiCamera> out(new aiCamera());

	return NULL ; //out.dismiss();
}

// ------------------------------------------------------------------------------------------------
aiLight* BlenderImporter::ConvertLight(const Scene& in, const Object* obj, const Lamp* mesh, ConversionData& conv_data) 
{
	ScopeGuard<aiLight> out(new aiLight());

	return NULL ; //out.dismiss();
}

// ------------------------------------------------------------------------------------------------
aiNode* BlenderImporter::ConvertNode(const Scene& in, const Object* obj, ConversionData& conv_data) 
{
	std::deque<const Object*> children;
	for(std::set<const Object*>::iterator it = conv_data.objects.begin(); it != conv_data.objects.end() ;) {
		const Object* object = *it;
		if (object->parent.get() == obj) {
			children.push_back(object);

			conv_data.objects.erase(it++);
			continue;
		}
		++it;
	}

	ScopeGuard<aiNode> node(new aiNode(obj->id.name));
	if (obj->data) {
		switch (obj->type)
		{
		case Object :: Type_EMPTY:
			break; // do nothing


			// supported object types
		case Object :: Type_MESH: {
			const size_t old = conv_data.meshes->size();

			CheckActualType(obj->data.get(),"Mesh");
			ConvertMesh(in,obj,static_cast<const Mesh*>(obj->data.get()),conv_data,conv_data.meshes);

			if (conv_data.meshes->size() > old) {
				node->mMeshes = new unsigned int[node->mNumMeshes = static_cast<unsigned int>(conv_data.meshes->size()-old)];
				for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
					node->mMeshes[i] = i + old;
				}
			}}
			break;
		case Object :: Type_LAMP: {
			CheckActualType(obj->data.get(),"Lamp");
			aiLight* mesh = ConvertLight(in,obj,static_cast<const Lamp*>(
				obj->data.get()),conv_data);

			if (mesh) {
				conv_data.lights->push_back(mesh);
			}}
			break;
		case Object :: Type_CAMERA: {
			CheckActualType(obj->data.get(),"Camera");
			aiCamera* mesh = ConvertCamera(in,obj,static_cast<const Camera*>(
				obj->data.get()),conv_data);

			if (mesh) {
				conv_data.cameras->push_back(mesh);
			}}
			break;


			// unsupported object types / log, but do not break
		case Object :: Type_CURVE:
			NotSupportedObjectType(obj,"Curve");
			break;
		case Object :: Type_SURF:
			NotSupportedObjectType(obj,"Surface");
			break;
		case Object :: Type_FONT:
			NotSupportedObjectType(obj,"Font");
			break;
		case Object :: Type_MBALL:
			NotSupportedObjectType(obj,"MetaBall");
			break;
		case Object :: Type_WAVE:
			NotSupportedObjectType(obj,"Wave");
			break;
		case Object :: Type_LATTICE:
			NotSupportedObjectType(obj,"Lattice");
			break;

			// invalid or unknown type
		default:
			break;
		}
	}

	for(unsigned int x = 0; x < 4; ++x) {
		for(unsigned int y = 0; y < 4; ++y) {
			node->mTransformation[y][x] = obj->parentinv[x][y];
		}
	}

	aiMatrix4x4 m;
	for(unsigned int x = 0; x < 4; ++x) {
		for(unsigned int y = 0; y < 4; ++y) {
			m[y][x] = obj->obmat[x][y];
		}
	}

	node->mTransformation = m*node->mTransformation;
	
	if (children.size()) {
		node->mNumChildren = static_cast<unsigned int>(children.size());
		aiNode** nd = node->mChildren = new aiNode*[node->mNumChildren]();
		for_each (const Object* nobj,children) {
			*nd = ConvertNode(in,nobj,conv_data);
			(*nd++)->mParent = node;
		}
	}

	return node.dismiss();
}

// ------------------------------------------------------------------------------------------------
/*static*/ void BlenderImporter::ThrowException(const std::string& msg)
{
	throw DeadlyImportError("BLEND: "+msg);
}

// ------------------------------------------------------------------------------------------------
/*static*/ void BlenderImporter::LogWarn(const Formatter::format& message)	{
	DefaultLogger::get()->warn(std::string("BLEND: ")+=message);
}

// ------------------------------------------------------------------------------------------------
/*static*/ void BlenderImporter::LogError(const Formatter::format& message)	{
	DefaultLogger::get()->error(std::string("BLEND: ")+=message);
}

// ------------------------------------------------------------------------------------------------
/*static*/ void BlenderImporter::LogInfo(const Formatter::format& message)	{
	DefaultLogger::get()->info(std::string("BLEND: ")+=message);
}

// ------------------------------------------------------------------------------------------------
/*static*/ void BlenderImporter::LogDebug(const Formatter::format& message)	{
	DefaultLogger::get()->debug(std::string("BLEND: ")+=message);
}

#endif
