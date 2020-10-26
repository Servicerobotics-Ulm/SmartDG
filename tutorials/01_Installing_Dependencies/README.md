# SmartDG
A C++ Library used by Dependency-Graph extension of SmartMDSD Toolchain
## Tutorial: Installing Dependencies


[A] sudo apt-get update
[B] sudo apt-get install build-essential
cat /usr/share/doc/build-essential/list
[C] sudo apt install cmake
[D] sudo apt install git
[E] sudo apt install libx11-dev
[F] sudo apt-get install libglu1-mesa-dev
[G] sudo apt-get install freeglut3-dev
[H] sudo apt-get install mesa-common-dev
[I] sudo apt-get -y install libxft-dev
[J] git clone https://github.com/fltk/fltk.git
[K] Building fltk
mkdir build
cd build
cmake ..
make
sudo make install




[L] Installing Node.js
sudo apt install nodejs
node -v
[M] Installing NPM
sudo apt install npm
npm -v
[N] Installing Browsersync
sudo npm install -g browser-sync
[O] Test Browsersync
browser-sync start --server --directory --files '**/*' 