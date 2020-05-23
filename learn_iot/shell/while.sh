#!/bin/bash

if [ $# -eq 2 ]
then
	loop=$2
else
	loop=5
fi

i=1
while [ $i -le $loop ]
do
	touch $1$i
	i=`expr $i + 1`
done
echo "newfile complete"
