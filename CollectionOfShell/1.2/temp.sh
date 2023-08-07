#!/bin/bash

function check {
 return 1
}

function idd {
	if [ "${1}" == "s0600004" ]; then
		return 0
	fi
} 
if check || idd s0600004; then 
	echo daaaa
fi
