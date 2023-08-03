#!/bin/bash

if [[ ${#} -ne 1 ]]; then
	echo "usage: ${0} <c file>"
	echo "${0} finds the max nesting level in the given c file"
	exit 1
fi

if [[ ! -f "${1}" ]]; then
	echo "${1} is not a file"
	exit 1
fi

temp_file="$(mktemp)"

cat "${1}" | tr -d -c '{}' > "${temp_file}"

while grep -q '{}' "${temp_file}"; do
	sed -i 's/{}//g' "${temp_file}"
	echo "level"
done | wc -l

rm "${temp_file}"

temp_file="$(mktemp)"

cat "${1}" | tr -dc '{}' > "${temp_file}"

count=0
while grep -q . "${temp_file}"; do
	sed -i 's/{}//g' "${temp_file}"
	count=$((count + 1))
done

rm "${temp_file}"

echo "number of nestings: ${count}"
