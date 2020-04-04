#!/bin/bash

for A in $@; do
	if [ -f $A ]; then
		echo "Name of file: " `basename $A`
		echo "Number of characters: " $((`cat "$A"|wc -c`-1))
		echo "Number of lines: " `cat "$A"|wc -l`
		echo
	elif [ -d $A ]; then
		echo "Name of directory: " `basename $A`
		echo "Number of files: " `find $A -type f|wc -l`
	       	echo	
	else printf "$A is not a file or directory \n"
	fi
done
