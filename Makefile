SHELL=/bin/sh
CC=gcc
bin=bin/
outputName=Tbfe
src=src/
misc=$(tbfe)misc/
ui=$(tbfe)UI/
actor=$(tbfe)actor/
map=$(tbfe)map/
objs=objs/
tbfe=$(src)tbfe/
tbfePy=TbfePy/
python=python2.7
libs=-lSDL -lSDL_image -lSDL_ttf -l$(python) -lGL -lGLU
libDirs=-I/usr/include/$(python) -Iinclude/
include=include/
Swig=swig
SwigArgs=-python -c++
SwigCXX=$(objs)LibTbfe.cxx $(objs)LibActor.cxx $(objs)LibMap.cxx $(objs)LibMisc.cxx $(objs)LibUI.cxx
SwigHeaderDir=include/

#Interpreter source files
srcInterpreter=$(src)Main.cpp

#Tbfe source files
srcTbfe=$(tbfe)Base.cpp $(tbfe)Console.cpp $(tbfe)Logic.cpp $(tbfe)Main.cpp $(tbfe)Render.cpp

#Actor source files
srcActor=$(actor)Actor.cpp $(actor)Action.cpp $(actor)ActorCreate.cpp  $(actor)Animation.cpp \
	 $(actor)CollisionBox.cpp $(actor)NonLiving.cpp $(actor)Npc.cpp $(actor)Pulse.cpp

#Map source files 
srcMap=$(map)Map.cpp $(map)OverMap.cpp $(map)TileLayer.cpp

#Misc source files
srcMisc=$(misc)Matrix.cpp $(misc)PositionF.cpp $(misc)Quaternion.cpp $(misc)SdlFunctions.cpp $(misc)StringConversion.cpp $(misc)Timer.cpp

#Ui source files
srcUi=$(ui)Element.cpp $(ui)ImageBox.cpp $(ui)Label.cpp $(ui)StatBar.cpp $(ui)TextBox.cpp $(ui)Window.cpp $(ui)WindowCreate.cpp

#engine source files
srcFiles=$(srcInterpreter) $(srcTbfe) $(srcActor) $(srcMap) $(srcMisc) $(srcUi)

#Compiled source files
objFiles=$(subst $(src),$(objs),$(srcFiles:.cpp=.o))

#Header files used by swig to generate wrappers
swigFiles=$(SwigHeaderDir)tbfe/PyTbfe.i $(SwigHeaderDir)tbfe/actor/PyActor.i $(SwigHeaderDir)tbfe/map/PyMap.i \
	  $(SwigHeaderDir)tbfe/misc/PyMisc.i $(SwigHeaderDir)tbfe/UI/PyUI.i

#Compiled swig wrappers
objSwigFiles=$(subst $(include),$(objs),$(swigFiles:.i=.o))
.PHONY: clean
$(bin)$(outputName):$(objFiles) $(swigFiles:.i=.cxx) $(objSwigFiles) #Final Linking Stage
	g++ $(objFiles) $(objSwigFiles) $(libDirs) $(libs)  -o $@


#Uses makefiles created by dependency generation for source files
include $(objFiles:.o=.d)

#Dependency generation for source files 
$(objs)%.d:$(src)%.cpp 
	$(CC) -MM $(libDirs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P


#Uses makefiles created by dependency generation for swig files
include $(objSwigFiles:.o=.d)

#Dependency generation for swig files 
$(objs)%.d:$(include)%.cxx 
	$(CC) -MM $(libDirs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P


#Compile instructions for source files
$(objs)%.o:$(src)%.cpp 
	g++ -g -c $(libDirs) $(DEFINES) $< -o $@

#Compile instructions for swig files
$(objs)%.o:$(include)%.cxx 
	g++ -g -c $(libDirs) $(DEFINES) $< -o $@

#Swig header generation
$(swigFiles:.i=.cxx):%.cxx:%.i; 
	$(Swig) $(SwigArgs) -o $@ -I$(SwigHeaderDir) $<
	mv $(@:.cxx=.py) $(tbfePy)
clean:
	rm $(objFiles)
	rm $(swigFiles:.i=.cxx)
	rm $(addprefix $(tbfePy),$(notdir $(swigFiles:.i=.py)))