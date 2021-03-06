#!/bin/bash
TARGET_FOLDER_NAME="examples"
if [ -d ${TARGET_FOLDER_NAME} ]
then
	echo "A folder by the name ${TARGET_FOLDER_NAME} already exists. Remove or rename that folder and run this script again."
else
	SMARTDG_DSL_REPO_URL=https://github.com/Servicerobotics-Ulm/SmartDG-DSL
	SMARTDG_DSL_RELEASE_NAME=v1.0
	SMARTDG_DSL_RELEASE_BUILD_FILENAME=SmartDG-DSL-v1.tar.gz
	SMARTDG_DSL_RELEASE_BUILD_DIRNAME=SmartDG-DSL-v1

	SMARTDG_DSL_RELEASE_BUILD_URL=${SMARTDG_DSL_REPO_URL}/releases/download/${SMARTDG_DSL_RELEASE_NAME}/${SMARTDG_DSL_RELEASE_BUILD_FILENAME}
	wget --no-check-certificate --content-disposition ${SMARTDG_DSL_RELEASE_BUILD_URL}
	tar -xf ${SMARTDG_DSL_RELEASE_BUILD_FILENAME}
	rm ${SMARTDG_DSL_RELEASE_BUILD_FILENAME}
	rm -rf ${TARGET_FOLDER_NAME}
	mv ${SMARTDG_DSL_RELEASE_BUILD_DIRNAME}/${TARGET_FOLDER_NAME} .
	rm -r ${SMARTDG_DSL_RELEASE_BUILD_DIRNAME}
fi
