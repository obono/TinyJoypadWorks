#!/usr/bin/env bash
if [ $# -lt 2 ]
then
	echo "Usage: $0 <project> <attribute name>"
	exit 1
fi
grep -hE "^#define\s+$2" $1/*.* | awk '{print $3}' | sed -e 's/["\r]//g'
