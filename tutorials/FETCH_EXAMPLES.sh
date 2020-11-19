#!/bin/bash
SMARTDG_REPO_URL=https://github.com/Servicerobotics-Ulm/SmartDG-DSL
SMARTDG_FEATURE_NAME=org.SmartDG.DSL.feature
SMARTDG_RELEASE_NAME=v1.0
SMARTDG_RELEASE_BUILD_FILENAME=SmartDG-DSL-v1.tar.gz
SMARTDG_RELEASE_BUILD_DIRNAME=SmartDG-DSL-v1

SMARTDG_RELEASE_BUILD_URL=${SMARTDG_REPO_URL}/releases/download/${SMARTDG_RELEASE_NAME}/${SMARTDG_RELEASE_BUILD_FILENAME}
wget --no-check-certificate --content-disposition ${SMARTDG_RELEASE_BUILD_URL}
tar -xf ${SMARTDG_RELEASE_BUILD_FILENAME}
rm ${SMARTDG_RELEASE_BUILD_FILENAME}
rm -rf examples
mv ${SMARTDG_RELEASE_BUILD_DIRNAME}/examples .
rm -r ${SMARTDG_RELEASE_BUILD_DIRNAME}