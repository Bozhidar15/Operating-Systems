#!/bin/bash

read -p "Enter file with code: " file1

grep -o '[{}]' "${file1}" | uniq -c | awk \
	'BEGIN{max=0; curr=0}
	$2 == "{" { curr += $1 }
	$2 == "}" { curr -= $1 }

	curr > max { max=curr }

	END { print max }
	'
