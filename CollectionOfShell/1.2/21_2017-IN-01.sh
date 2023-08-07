#!/bin/bash

if [[ "${#}" -ne 3 ]]; then 
	echo error
	exit 1
fi

file="${1}"
str1="${2}"
str2="${3}"

line1="$( cat "${file}" | grep "${str1}=" | cut -d '=' -f2 )"
line2="$( cat "${file}" | grep "${str2}=" | cut -d '=' -f2 )"
new="$( comm -1 -3 <(echo "${line1}" | egrep -o '[^ \n]*') <(echo "${line2}" | egrep -o '[^ \n]*') | tr '\n' ' ' )"
echo "tuk ${new}"
sed -E -i "s%(${str2}=).*%\1${new}%" "${file}"
