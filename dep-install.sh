sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev libsdl-image1.2-dev swig libboost1.40-dev g++

cd Python-2.6.5
./configure
make
sudo make install
sudo make clean
cd ../

sudo cp assimp/lib/libassimp.so /usr/lib/libassimp.so
sudo cp assimp/lib/libassimp.so.1 /usr/lib/libassimp.so.1