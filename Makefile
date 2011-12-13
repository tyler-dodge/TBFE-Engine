CC=gcc
bin=bin/
outputName=Tbfe
fonts=font.ttf
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
SwigObjs=$(objs)LibTbfe.cxx $(objs)LibActor.cxx $(objs)LibMap.cxx $(objs)LibMisc.cxx $(objs)LibUI.cxx
SwigHeaderDir=include/
src=src/
srcInterpreter=$(src)Main.cpp
srcTbfe=$(tbfe)Base.cpp $(tbfe)Console.cpp $(tbfe)Logic.cpp $(tbfe)Main.cpp $(tbfe)Render.cpp
srcActor=$(actor)Actor.cpp $(actor)Action.cpp $(actor)ActorCreate.cpp  $(actor)Animation.cpp \
	 $(actor)CollisionBox.cpp $(actor)NonLiving.cpp $(actor)Npc.cpp $(actor)Pulse.cpp 
srcMap=$(map)Map.cpp $(map)OverMap.cpp $(map)TileLayer.cpp
srcMisc=$(misc)Matrix.cpp $(misc)PositionF.cpp $(misc)Quaternion.cpp $(misc)SdlFunctions.cpp $(misc)StringConversion.cpp $(misc)Timer.cpp
srcUi=$(ui)Element.cpp $(ui)ImageBox.cpp $(ui)Label.cpp $(ui)StatBar.cpp $(ui)TextBox.cpp $(ui)Window.cpp $(ui)WindowCreate.cpp
srcFiles=$(srcInterpreter) $(srcTbfe) $(srcActor) $(srcMap) $(srcMisc) $(srcUi)
objFiles=$(subst $(src),$(objs),$(srcFiles:.cpp=.o))
swigFiles=$(SwigHeaderDir)tbfe/PyTbfe.i $(SwigHeaderDir)tbfe/actor/PyActor.i $(SwigHeaderDir)tbfe/map/PyMap.i \
	  $(SwigHeaderDir)tbfe/misc/PyMisc.i $(SwigHeaderDir)tbfe/UI/PyUI.i
objSwigFiles=$(subst $(include),$(objs),$(swigFiles:.i=.o))
SHELL=/bin/sh
DEFINES=
.PHONY: clean
$(bin)$(outputName):$(objFiles) $(swigFiles:.i=.cxx) $(objSwigFiles)
	g++ $(objFiles) $(objSwigFiles) $(libDirs) $(libs)  -o $@
$(objs)%.d:$(src)%.cpp
	$(CC) -MM $(libDirs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P
$(objs)%.d:$(include)%.cxx
	$(CC) -MM $(libDirs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P
$(objs)%.o:$(src)%.cpp
	g++ -g -c $(libDirs) $(DEFINES) $< -o $@
$(objs)%.o:$(include)%.cxx
	g++ -g -c $(libDirs) $(DEFINES) $< -o $@
include $(objFiles:.o=.d)
include $(objSwigFiles:.o=.d)
$(swigFiles:.i=.cxx):%.cxx:%.i;
	$(Swig) $(SwigArgs) -o $@ -I$(SwigHeaderDir) $<
	mv $(@:.cxx=.py) $(tbfePy)
$(di)Agrarious:$(TbfeLibs)
	gcc -g $(TbfeLibs) -o $(di)Agrarious $(libs)
$(dirLibs)Misc.lib $(dirLibs)MiscI.lib:tbfe/misc/*.h
	swig -python -c++ -o tbfe/misc/Misc.cxx tbfe/misc/LibMisc.i
	g++ -g -c tbfe/misc/Misc.cxx $(libDirs) -o $(dirLibs)MiscI.lib
	g++ -g -c $(libDirs) $(misc)Lib.cpp -o $(dirLibs)Misc.lib
	cp tbfe/misc/Misc.py ../debug/TbfePy/Misc.py
clean:
	rm $(objFiles)
	rm $(swigFiles:.i=.cxx)
	rm $(addprefix $(tbfePy),$(notdir $(swigFiles:.i=.py)))