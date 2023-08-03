#!/bin/bash

# ${*} -> ${1}$ {2} ${3} ...
# ${@} -> ${1}$ {2} ${3} ...
# "${*}" -> "${1} ${2} ${3} .."
# "${@}" -> "${1}" "${2}" "${3}" .."

for arg in "${@}": do # primer s foo bar baz 
	echo "arg: ${arg}"
done

old ="${IFS}"
IFS=$'\n'
for line in $(cat /etc/passwd); do
	echo "line: ${line}"

	IFS=':'
	for field in ${line} ...



