#!/bin/bash

if [[ ${#} -ne 3 ]]; then
	echo "usage: ${0} <conf file> <key> <value>"
	exit 1
fi

conf_file="${1}"
key="${2}"
value="${3}"

if [[ ! -r "${conf_file}" ]]; then
	echo "could not read ${conf_file}"
	exit 1
fi

function mod_comment {
	echo "at $(date) by $(whoami)"
}

function find_key {
	grep -q -E "^\s*${key}\s*=\s*[[:alnum:]]+"
	return $?
}

function new_line {
	echo "${key} = ${value} # added $(mod_comment)"
}

function process_line {
	if echo "${1}" | find_key; then
		echo "# ${line} # edited $(mod_comment)"
		new_line
	else
		echo "${line}"
	fi
}

function process_file {
	if cat "${1}" | find_key; then
		while read line; do
			process_line "${line}"
		done < "${1}"
	else
		cat "${1}"
		new_line
	fi
}

process_file "${conf_file}" > "${conf_file}.new"
mv -f "${conf_file}.new" "${conf_file}"
