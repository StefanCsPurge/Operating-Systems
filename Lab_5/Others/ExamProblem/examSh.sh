#!/bin/bash

echo "Insert strings"
declare arr=()
declare arrf=()
declare -i s=0
declare -i tf=0


while read str; do
	if [[ " ${arr[@]} " =~ " ${str} " ]]; then
		echo The sum of the numbers is $s
		echo The total number of file names is $tf
		echo -n "The files with read permissions for owner: " 
		echo ${arrf[@]}
		break
	else
		arr+=($str)
		#Now we work with str
		if test -d $str; then
			find $str -type f -name "*.c" | xargs -r ls -l 2> /dev/null| awk '{print $5, $NF}' | sort -k1nr | cut -d ' ' -f2- | head -n 3
		elif echo $str | grep -q "^[0-9]\+$"; then
			s=$(($s+$str))
		elif [ -f $str ]; then
			tf=$(($tf+1))
			if ls -l $str | cut -d' ' -f1 | grep -q "^-r"; then
				arrf+=($str)
			fi
		elif grep -q "^$str:" /etc/passwd; then
			proc=`who -a | grep -c "^$str"`
			echo $str $proc >> myprocesses.txt
		fi 
	fi
done
