#!/bin/bash

if [[ "${#}" -ne 2 ]] || egrep -q '[^0-9]' <(echo "${1}") || egrep -q '[^0-9]' <(echo "${2}"); then 
	echo 'error parameters should be two numbers!\n left border right border!'
	exit 1
fi

number="$(( (RANDOM % ${2}) + ${1} ))"
entered=""
count=0
while read -p "Guess? " entered && [[ number -ne entered ]]; do
	count="$((count + 1))"
	if [[ entered -gt number ]]; then
		echo "...smaller!"
		continue
	else
		echo "...greater!"
	fi
done
echo "you guess the right number for only ${count} tries. Nice"
