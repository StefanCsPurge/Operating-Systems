#!/bin/bash

find $1 -type f|while read F; do
	fileName=`basename $F`
	len=${#fileName}
	if [ $len -lt 8 ]; then
		echo "File name: " $fileName
		if file "$F" | grep -q "ASCII text";then
		       head $F
		fi
 		echo		
	fi	
done
