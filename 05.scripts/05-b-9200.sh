#!/bin/bash

while [[ "${#}" -ne 0 ]]; do 
	curr="${1}"
	shift
	if [[ -d "${curr}" ]] && [[ "$(find "${curr}" -mindepth 1 -type f | wc -l)" -eq 0 ]]; then 
		if [[ "$(find "${curr}" -mindepth 1 -type d | wc -l)" -eq 0 ]]; then
			rm -r "${curr}"
			echo "$(date +"%Y-%m-%d %T") Removed directory recursivly ${curr}" >> "${logf}"
		else
			rm -d "${curr}"
			echo "$(date +"%Y-%m-%d %T") Removed directory ${curr}" >> "${logf}"
		fi
	fi
	if [[ -f "${curr}" ]]; then
		rm "${curr}" 
		echo "$(date +"%Y-%m-%d %T") Removed file ${curr}" >> "${logf}"
	fi
done
