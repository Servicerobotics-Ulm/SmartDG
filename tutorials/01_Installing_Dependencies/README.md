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
[I] sudo apt-get install libxft-dev
[J] git clone https://github.com/fltk/fltk.git
[K] Building fltk
mkdir build
cd build
cmake ..
make
sudo make install

[L] sudo apt-get install openjdk-11-jdk
java --version
sudo update-alternatives --config java

[M] Installing Node.js
sudo apt install nodejs
node -v
[N] Installing NPM
sudo apt install npm
npm -v
[O] Installing Browsersync
sudo npm install -g browser-sync
Test Browsersync
browser-sync start --server --directory --files '**/*' 
