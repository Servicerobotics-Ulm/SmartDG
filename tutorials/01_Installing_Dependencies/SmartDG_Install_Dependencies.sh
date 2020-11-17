YOPTION="-y"
#YOPTION=""
echo "########################################## SmartDG_Install_Dependencies START"
echo "########################################## Updateing apt-get"
sudo apt-get update
echo "########################################## Installing build-essential"
sudo apt-get $YOPTION install build-essential
echo "########################################## Installing cmake"
sudo apt $YOPTION install cmake
echo "########################################## Installing git"
sudo apt $YOPTION install git
echo "########################################## Installing libx11-dev"
sudo apt $YOPTION install libx11-dev
echo "########################################## Installing libglu1-mesa-dev"
sudo apt-get $YOPTION install libglu1-mesa-dev
echo "########################################## Installing freeglut3-dev"
sudo apt-get $YOPTION install freeglut3-dev
echo "########################################## Installing mesa-common-dev"
sudo apt-get $YOPTION install mesa-common-dev
echo "########################################## Installing libxft-dev"
sudo apt-get $YOPTION install libxft-dev
echo "########################################## Installing fltk"
if [ -e "/usr/local/lib/libfltk.a" ]
then
echo "########################################## fltk | /usr/local/lib/libfltk.a already exists"
echo "########################################## fltk | Manually re-install if desired"
else
echo "########################################## fltk | Cloning fltk"
	mkdir -p ~/SOFTWARE/
	cd ~/SOFTWARE/
	sudo rm -r ~/SOFTWARE/fltk
	git clone https://github.com/fltk/fltk.git
	cd ~/SOFTWARE/fltk	
echo "########################################## fltk | Building fltk"		
	mkdir ~/SOFTWARE/fltk/build
	cd ~/SOFTWARE/fltk/build
	cmake ..
	make
echo "########################################## fltk | Installing fltk"		
	sudo make install
fi
echo "########################################## Installing openjdk-11-jdk"
sudo apt-get $YOPTION install openjdk-11-jdk
java --version
echo "########################################## Installing nodejs"
sudo apt $YOPTION install nodejs
node -v
echo "########################################## Installing npm"
sudo apt $YOPTION install npm
npm -v
echo "########################################## Installing Browsersync"
sudo npm $YOPTION install -g browser-sync
echo "########################################## SmartDG_Install_Dependencies DONE "
