#!/bin/bash

grep_user()
{
	r=`grep "^$1:" /etc/passwd | wc -l`
	return $r
}

echo -n "input a name:"
read name
grep_user $name
ret=$?
if [ $ret -ge 1 ]
then 
	echo "$name user exist"
else
	echo "$name user not exist"
fi
