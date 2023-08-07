#!/bin/bash

if [ $# -ne 2 ]; then
	echo "ERROR: Arg count. Expected 2 args"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "ERROR: File $1 does not exist"
	exit 1
fi

BINARY=$1
OUTPUT=$2

touch $OUTPUT
echo "#include <stdint.h>" > $OUTPUT

ARR=""

for UINT16 in $(xxd $BINARY | cut -d' ' -f2-9); do
	ARR="${ARR}0x${UINT16},"
done

ARR=$(echo ${ARR} | sed -E "s/,$//" )

echo "uint32_t arr[] = { ${ARR} };" >> $OUTPUT
