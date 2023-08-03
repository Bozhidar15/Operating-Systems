#!/bin/bash

dirfiles="${1}"
dirTo="${2}"

if [[ -z "${dirTo}" ]]; then
	dirTo="$(date +'%d-%H')"
	mkdir ${dirTo}
fi

while read line; do
	echo ${line}
	cp ${line} ${dirTo}
done < <(find ${dirfiles} -mmin -45 -type f -printf "%p\n")

