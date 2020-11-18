#!/usr/bin/env bash

BIN_DIR='.circleci'

projects=`cat ${BIN_DIR}/projects.txt`
repo='{ "items": [] }'

for project in ${projects}
do
	app_code=`${BIN_DIR}/get_attr.sh ${project} APP_CODE`
	version=`${BIN_DIR}/get_attr.sh ${project} APP_VERSION`
	if [ -z ${app_code} ] || [ -z ${version} ]
	then
		echo "Failed to get attribute of \"${project}\"" >&2
		exit 1
	fi
	ITEM=`${BIN_DIR}/jq_info.sh ${project} ${app_code} ${version} | sed -e 's/"/\\"/g'` || exit 1
	repo=`echo ${repo} | jq ".items |= .+[${ITEM}]"` || exit 1
done
echo ${repo} | jq --tab .
