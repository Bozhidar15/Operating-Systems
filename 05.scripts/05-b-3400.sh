#!/bin/bash

# Да се напише shell скрипт, който приема като аргументи име на файл и символен низ, проверява дали низа се съдържа във файла и извежда на стандартния изход кода на завършване на командата с която сте проверили наличието на низа.

file="${1}"
string="${2}"

if [[ ${#} -ne 2 ]]; then
	echo "${0} tests whether a given string is found in a given file"
	echo "usage: ${0} <filename> <string>"
	exit 1
fi

if [[ ! -f "${file}" ]] ; then
	echo "file ${file} does not exist, giving up"
	exit 1
fi

cat "${file}" | grep -q "${string}"

echo "The exit status is: ${?}"
