#!/bin/bash

if [[ "${#}" -eq 0 ]] || [[ "${#}" -gt 2 ]]; then
	echo "parameters: color text"
	exit 1
fi
color="${1}"
text="${2}"
if [[ "${#}" -eq 1 ]]; then
	echo "${1}"
else 
	case "${color}" in
		"-r")
			echo -e "\033[0;31m ${text}"
			;;
		"-g")
			echo -e "\033[0;32m ${test}"
			;;
		"-b")
			echo -e "\033[0;34m ${text}"
			;;
		*)
			echo "Unknown colour"
			;;
	esac
fi
		
echo -e '\033[0m'
