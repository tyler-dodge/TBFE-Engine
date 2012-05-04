CC=gcc -g
bin=bin/
outputName=Tbfe
src=src/
misc=$(tbfe)misc/
ui=$(tbfe)UI/
actor=$(tbfe)actor/
map=$(tbfe)map/
raster=$(tbfe)raster/
objs=objs/
tbfe=$(src)tbfe/
tbfePy=TbfePy/
python=python2.7
appleGL=-framework Carbon -framework OpenGL -framework GLUT 
linuxGL= -lGL -lGLU
libs=-lSDL -lSDL_image -lSDL_ttf -l$(python) $(appleGL)
libDirs=-I/usr/include/$(python) -Iinclude/
include=include/
Swig=swig
SwigArgs=-python -c++
SwigCXX=$(objs)LibTbfe.cxx $(objs)LibActor.cxx $(objs)LibMap.cxx $(objs)LibMisc.cxx $(objs)LibUI.cxx
SwigHeaderDir=include/

#Interpreter source files
srcInterpreter=$(src)Main.cpp

#Tbfe source files
srcTbfe=$(tbfe)Console.cpp $(tbfe)Logic.cpp $(tbfe)Main.cpp $(tbfe)Render.cpp $(tbfe)Camera.cpp

#Actor source files
srcActor=$(actor)Actor.cpp $(actor)Action.cpp $(actor)Animation.cpp \
	 $(actor)CollisionBox.cpp $(actor)NonLiving.cpp $(actor)Npc.cpp

#Map source files 
srcMap=$(map)Map.cpp $(map)OverMap.cpp $(map)TileLayer.cpp

#Misc source files
srcMisc=$(misc)Matrix.cpp $(misc)Position.cpp $(misc)Quaternion.cpp \
	$(misc)SdlFunctions.cpp $(misc)StringConversion.cpp $(misc)Timer.cpp $(misc)TFont.cpp $(misc)Texture.cpp \
	$(misc)PropContainer.cpp $(misc)Identifier.cpp

srcRaster=$(raster)Model.cpp $(raster)Renderable.cpp $(raster)RenderParameters.cpp $(raster)RenderPipeline.cpp \
	$(raster)ScreenImage.cpp $(raster)ScreenImageRenderParams.cpp
#engine source files
srcFiles=$(srcInterpreter) $(srcTbfe) $(srcActor) $(srcMap) $(srcMisc) $(srcRaster)

#Compiled source files
objFiles=$(subst $(src),$(objs),$(srcFiles:.cpp=.o))

#Header files used by swig to generate wrappers
swigFiles=$(SwigHeaderDir)tbfe/PyTbfe.i $(SwigHeaderDir)tbfe/actor/PyActor.i $(SwigHeaderDir)tbfe/map/PyMap.i \
	  $(SwigHeaderDir)tbfe/misc/PyMisc.i

#Compiled swig wrappers
objSwigFiles=$(subst $(include),$(objs),$(swigFiles:.i=.o))
.PHONY: clean
$(bin)$(outputName):$(objFiles) $(swigFiles:.i=.cxx) $(objSwigFiles) #Final Linking Stage
	mkdir -p $(dir $@)
	g++ $(objFiles) $(objSwigFiles) $(libDirs) $(libs)  -o $@


#Uses makefiles created by dependency generation for source files
-include $(objFiles:.o=.d)

#used to ignore removed header files in auto dependency generation
%.h:
	#Does Nothing if header file does not exist
#Dependency generation for source files 
ifneq ($(MAKECMDGOALS),clean)
$(objs)%.d:$(include)%.h 
	mkdir -p $(dir $@)
	$(CC) -MM $(libDirs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P

#Dependency generation for swig files 
$(objs)%.d:$(include)%.cxx
	mkdir -p $(dir $@) 
	$(CC) -MM $(libDirs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P
-include $(objSwigFiles:.o=.d)
endif


#Uses makefiles created by dependency generation for swig files


#Compile instructions for source files
$(objs)%.o:$(src)%.cpp 
	mkdir -p $(dir $@)
	g++ -g -c $(libDirs) $(DEFINES) $< -o $@

#Compile instructions for swig files
$(objs)%.o:$(include)%.cxx 
	mkdir -p $(dir $@)
	g++ -g -c $(libDirs) $(DEFINES) $< -o $@


#Swig header generation
$(swigFiles:.i=.cxx):%.cxx:%.i; 
	mkdir -p $(dir $@)
	$(Swig) $(SwigArgs) -o $@ -I$(SwigHeaderDir) $<
	mkdir -p $(tbfePy)
	mv $(@:.cxx=.py) $(tbfePy)
clean:
	rm -f $(objFiles)
	rm -f $(objFiles:.o=.d)
	rm -f $(swigFiles:.i=.cxx)
	rm -f $(addprefix $(tbfePy),$(notdir $(swigFiles:.i=.py)))