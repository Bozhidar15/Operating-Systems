#!/bin/bash

if [ "${#}" -ne 2 ]; then 
	echo error
	exit 1
fi

dir="${1}"
str="${2}"

find "${dir}" -mindepth 1 -maxdepth 1 -type f -printf "%f\n" | egrep "vmlinuz-[0-9]*\.[0-9]*\.[0-9]-${str}" | sort 
