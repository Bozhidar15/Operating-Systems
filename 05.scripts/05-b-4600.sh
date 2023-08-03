#!/bin/bash


if [ $# -ne 3 ]; then 
	echo "trqbva da ima tri vuvedeni parametura! Error ..."
	exit 4
fi

number="${1}"
left="${2}"
right="${3}"

if grep -E -q '[^0-9 ]'  <(echo $@ ) ; then 
	exit 3
fi

if [ ${left} -ge ${right} ]; then 
	echo "granicite sa razmeneni!"
	exit 2
fi
if [[ ${number} -ge ${left} -a ${number} -le ${right}  ]]; then 
	exit 0
else
	exit 1
fi


