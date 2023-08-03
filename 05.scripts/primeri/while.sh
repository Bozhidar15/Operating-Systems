#!/bin/bash

#primer 1

while ps -o comm= -u human | grep -q '^vim$'; do
	echo "vim is still alive"
	sleep 1
done

echo "vim is now dead, yay"

#primer 2

#!/bin/bash

who | cut -d ' ' -f 1 | sort | uniq \
	| while read name; do
		echo "hello, ${name}"
	done

#primer 3

#!/bin/bash

count=0
who | cut -d ' ' -f 1 | sort | uniq \
	| while read name; do
		count=$(( count + 1 ))
	done
echo "count: ${count}"

count2=0
while read name; do
	count2=$(( count2 + 1 ))
done < <(who | cut -d ' ' -f 1 | sort | uniq)
echo "count2: ${count2}"

# primer 4

#!/bin/bash

while read line; do
	echo "line: ${line}"
	while read -d ':' field; do
		echo "field: ${field}"
	done < <(echo "${line}")
done < /etc/passwd
