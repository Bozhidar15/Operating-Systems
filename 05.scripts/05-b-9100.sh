#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
	echo "You should enter two parameters SOURCE DESTINATION: "
	exit 1
fi

sorc="${1}" 
dest="${2}"

while read file; do 
	if grep -q '\.' <(echo "${file}") ; then
		dot="$(echo "${file}" | sed -E 's/.*(\.)(.*)/\2/g')"
		check="${dest}/${dot}"
		if [[ ! -d "${check}" ]]; then
			mkdir "${check}"
		fi
		cp "${sorc}/${file}" "${check}"
	else
		if [[ ! -d "${dest}/none"  ]]; then 
			mkdir "${dest}/none"
		fi
		cp "${sorc}/${file}" "${dest}/none"
	fi
done < <(find "${sorc}" -mindepth 1 -maxdepth 1 -not -path '*/.*' -type f -printf "%f\n")

