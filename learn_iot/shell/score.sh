#!/bin/bash

scores=0
echo -n "please input your score:"
read scores

if [ $scores -lt 0 -o $scores -gt 100 ]
then
	echo "input score wrong"
	exit
fi

case `expr $scores / 10` in
	9 | 10)
		echo "A"
		;;
	8 | 7)
		echo "B"
		;;
	6)
		echo "C"
		;;
	5 | 4 | 3 | 2 | 1 | 0)
		echo "D"
		;;
	*)
		echo "error"
		;;
esac
