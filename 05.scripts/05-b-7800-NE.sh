#!/bin/bash 

old="${IFS}"
IFS=
if [[ "${#}" -ne 1 ]]; then 
	echo "error"
	exit 1
fi
count=0
read -r -d '' dir
for file in find "${dir}" -type f -perm -700  -maxdepth 1 -mindepth 1; do 
	if [[ -x "${file}" ]]; then 
		count="$(( count + 1 ))"
	fi
done
echo "${count}"
IFS="${old}"
