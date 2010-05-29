di=../debug/
dirLibs=../libs/
fonts=font.ttf
misc=tbfe/misc/
ui=tbfe/UI/
actor=tbfe/actor/
map=tbfe/map/
libs=-lSDL -lSDL_image -lSDL_ttf -lpython2.6 -L ../assimp/lib -lassimp -lGL -lGLU
TbfeLibs=$(dirLibs)Actor.lib $(dirLibs)ActorI.lib $(dirLibs)Ui.lib $(dirLibs)UiI.lib $(dirLibs)MapI.lib $(dirLibs)Map.lib $(dirLibs)Tbfe.lib $(dirLibs)TbfeI.lib $(dirLibs)Misc.lib $(dirLibs)MiscI.lib $(dirLibs)Interpreter.o
headerDirs=tbfe/Main.* tbfe/Logic.* tbfe/Render.* tbfe/Base.* tbfe/Console.*
libDirs=-I/usr/include/python2.6 -I ../assimp/include
$(di)Agrarious:$(TbfeLibs)
	g++ -g $(TbfeLibs) -o $(di)Agrarious $(libs)
$(dirLibs)Misc.lib $(dirLibs)MiscI.lib:tbfe/misc/
	swig -python -c++ -o tbfe/misc/Misc.cxx tbfe/misc/LibMisc.i
	g++ -g -c tbfe/misc/Misc.cxx $(libDirs) -o $(dirLibs)MiscI.lib
	g++ -g -c $(libDirs) $(misc)Lib.cpp -o $(dirLibs)Misc.lib
	cp tbfe/misc/Misc.py ../debug/TbfePy/Misc.py
$(dirLibs)Interpreter.o:Main.cpp
	g++ -g -c Main.cpp $(libDirs) -o $(dirLibs)Interpreter.o
$(dirLibs)Ui.lib $(dirLibs)UiI.lib:tbfe/UI/
	swig -python -c++ -o tbfe/UI/UI.cxx tbfe/UI/LibUI.i
	g++ -g -c tbfe/UI/UI.cxx $(libDirs) -o $(dirLibs)UiI.lib
	g++ -g -c $(libDirs) $(ui)Lib.cpp -o $(dirLibs)Ui.lib
	cp tbfe/UI/UI.py ../debug/TbfePy/UI.py
$(dirLibs)Tbfe.lib $(dirLibs)TbfeI.lib:$(headerDirs)
	swig -python -c++ -o tbfe/TBFE.cxx tbfe/LibTbfe.i
	g++ -g -c tbfe/TBFE.cxx $(libDirs) -o $(dirLibs)TbfeI.lib
	g++ -g -c $(libDirs) tbfe/Lib.cpp -o $(dirLibs)Tbfe.lib
	cp tbfe/TBFE.py ../debug/TbfePy/Tbfe.py
$(dirLibs)Actor.lib:tbfe/actor/
	swig -python -c++ -o tbfe/actor/Actor.cxx tbfe/actor/LibActor.i
	g++ -g -c tbfe/actor/Actor.cxx $(libDirs) -o $(dirLibs)ActorI.lib
	g++ -g -c $(libDirs) $(actor)Lib.cpp -o $(dirLibs)Actor.lib
	cp tbfe/actor/Actor.py ../debug/TbfePy/Actor.py
$(dirLibs)Map.lib $(dirLibs)MapI.lib:tbfe/map/
	swig -python -c++ -o tbfe/map/Map.cxx tbfe/map/LibMap.i
	g++ -g -c tbfe/map/Map.cxx $(libDirs) -o $(dirLibs)MapI.lib
	g++ -g -c $(libDirs) $(map)Lib.cpp -o $(dirLibs)Map.lib
	cp tbfe/map/Map.py ../debug/TbfePy/Map.py