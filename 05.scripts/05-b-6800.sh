#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
	echo "Error"
	exit 1
fi

dir="${1}"

for arg in $(find "${dir}" -mindepth 1 -maxdepth 1) ; do
	if [[ -f "${arg}" ]]; then
		bytes="$(stat -c="%s" ${arg})"
		echo "${arg} (${bytes} bytes)"
	else
		dirfiles="$(find ${arg} -mindepth 1 -maxdepth 1 | wc -l)"
		echo "${arg} (entries ${dirfiles})"
	fi
done
