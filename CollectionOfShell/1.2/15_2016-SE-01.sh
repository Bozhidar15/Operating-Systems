#!/bin/dash
if [ $# -ne 1 -o ! -d $1 ]; then
exit 1
fi
for i in $(find $1 -type l); do
dst=$(stat -c %N $i | cut -d "'" -f 4)
if [ ! -e $(dirname $i)/$dst ]; then
echo $i
fi
done

