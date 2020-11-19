#!/bin/bash
for tutorial_directory in */ ; do
	rm -f -r "$tutorial_directory/build/"
done
