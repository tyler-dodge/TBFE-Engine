di=../debug/
dirLibs=../libs/
fonts=font.ttf
libs=-lSDL -lSDL_image -lSDL_ttf -lboost_thread -lpython2.6
headerDirs=tbfe/Main.* tbfe/Logic.* tbfe/Render.* tbfe/Base.* tbfe/Console.*
pyDirs=-I/usr/include/python2.6
$(di)Agrarious:$(dirLibs)Actor.lib $(dirLibs)UI.lib $(dirLibs)Misc.lib  $(dirLibs)Map.lib  $(dirLibs)TBFE.lib $(dirLibs)Interpreter.o 
	g++ -g $(dirLibs)UI.lib $(dirLibs)TBFE.lib $(dirLibs)Actor.lib $(dirLibs)Misc.lib $(dirLibs)Map.lib $(dirLibs)Interpreter.o -o $(di)Agrarious $(libs)
$(dirLibs)Misc.lib:tbfe/misc/
	swig -python -c++ -o tbfe/misc/Misc.cxx tbfe/misc/LibMisc.i
	g++ -g -c tbfe/misc/Misc.cxx $(pyDirs) -o $(dirLibs)Misc.lib
	cp tbfe/misc/Misc.py ../debug/TbfePy/Misc.py
$(dirLibs)Interpreter.o:Main.cpp
	g++ -g -c Main.cpp $(pyDirs) -o $(dirLibs)Interpreter.o
$(dirLibs)UI.lib:tbfe/UI/
	swig -python -c++ -o tbfe/UI/UI.cxx tbfe/UI/LibUI.i
	g++ -g -c tbfe/UI/UI.cxx $(pyDirs) -o $(dirLibs)UI.lib
	cp tbfe/UI/UI.py ../debug/TbfePy/UI.py
$(dirLibs)TBFE.lib:$(headerDirs)
	swig -python -c++ -o tbfe/TBFE.cxx tbfe/LibTbfe.i
	g++ -g -c tbfe/TBFE.cxx $(pyDirs) -o $(dirLibs)TBFE.lib
	cp tbfe/TBFE.py ../debug/TbfePy/Tbfe.py
$(dirLibs)Actor.lib:tbfe/actor/
	swig -python -c++ -o tbfe/actor/Actor.cxx tbfe/actor/LibActor.i
	g++ -g -c tbfe/actor/Actor.cxx $(pyDirs) -o $(dirLibs)Actor.lib
	cp tbfe/actor/Actor.py ../debug/TbfePy/Actor.py
$(dirLibs)Map.lib:tbfe/map/
	swig -python -c++ -o tbfe/map/Map.cxx tbfe/map/LibMap.i
	g++ -g -c tbfe/map/Map.cxx $(pyDirs) -o $(dirLibs)Map.lib
	cp tbfe/map/Map.py ../debug/TbfePy/Map.py