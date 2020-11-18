#!/usr/bin/env bash

if [ $# -lt 1 ]
then
	echo "Usage: $0 <project> | all"
	exit 1
fi

BIN_DIR='.circleci'
OUT_DIR='_hexs'

if [ $1 = 'all' ]
then
	projects=`cat ${BIN_DIR}/projects.txt`
else
	projects=$1
fi

for project in ${projects}
do
	version=`${BIN_DIR}/get_attr.sh ${project} APP_VERSION`
	if [ -z ${version} ]
	then
		echo "Failed to get version of \"${project}\"" >&2
		exit 1
	fi
	echo "--- Building \"${project}\"..."
	arduino-cli compile --fqbn ATTinyCore:avr:attinyx5:LTO=enable,TimerClockSource=default,chip=85,clock=16pll,eesave=aenable,bod=disable,millis=enabled ${project} || exit 1
	cp -f ${project}/build/ATTinyCore.avr.attinyx5/${project}.ino.hex ${OUT_DIR}/${project}_v${version}.hex
	echo "--- Completed!"
	echo
done
