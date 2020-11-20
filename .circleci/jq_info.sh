#!/usr/bin/env bash

if [ $# -lt 3 ]
then
	echo "Usage: $0 <project> <app_code> <version>"
	exit 1
fi

project=$1
app_code=$2
version=$3

base_json=`cat ${project}/info.json` || exit 1
preview=`find ${project}/preview -iregex ".*\.\(gif\|png\)$" | sort | sed 's/[^ ]\+/"&",/g' | sed -e "$ s/,//"`

echo ${base_json} | jq ". | .+
{
	\"codeName\": \"${app_code}\",
	\"version\": \"${version}\",
	\"hexFile\": \"_hexs/${project}_v${version}.hex\",
	\"preview\": [
		${preview}
	]
}" || exit 1
