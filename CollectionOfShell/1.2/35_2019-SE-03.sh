#!/bin/bash
unix="$(stat -c %Y ${0})"
while read t file; do
	if [ "${t}" -gt "${unix}" ]; then
		name="$(echo "${file}" | sed -E 's/([^_]*)_.*/\1/g')"
		time="$(echo "${file}" | sed -E 's/[^_]*_report-(.*)\.tgz/\1/g')"
		#todo
	fi
done < <(find "${1}" -type f -name "*.tgz" -printf "%T@ %f\n" | egrep '[^_]*_report-[0-9\.]*\.tgz')  


