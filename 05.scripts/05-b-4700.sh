#!/bin/bash

number="${1}"
delim=" "

if [[ $# -gt 2 ]] || echo "${1}" | egrep -q '[^0-9]'; then
	echo "Error! "
	exit 1
fi

if [ $# -eq 2  ]; then 
	delim="${2}"
fi
newOne=""
while [ "${number}" -gt 999 ]; do 
	three=$(( number % 1000 ))
	newOne="${three}${delim}${newOne}"

	number=$(( number / 1000 ))
done
newOne="${number}${delim}${newOne}"
if [ "${delim}" != " " ]; then
	sed -E 's/^(.*).$/\1/g' <(echo "${newOne}")
else
	echo "${newOne}"
fi

