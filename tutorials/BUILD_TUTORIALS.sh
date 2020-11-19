#!/bin/bash
base_directory=$(pwd)
rm -f .gitignore
for tutorial_directory in */ ; do
	if (test -f "$tutorial_directory/CMakeLists.txt") && (test -d "$tutorial_directory/src/"); then
		echo "Found CMakeLists.txt and src folder for : Tutorial $tutorial_directory"
		rm -f -r "$tutorial_directory/build/"
		mkdir "$tutorial_directory/build/"
		echo "$tutorial_directory/build/" >> .gitignore
		cd "$tutorial_directory/build/"
		pwd
		cmake ..
		make
		cd $base_directory
	else
		echo "Nothing to build for		        : Tutorial $tutorial_directory"
		rm -f -r "$tutorial_directory/build/"
	fi
	echo "-----------------------------------------------------------------------------"
done
echo $base_directory
