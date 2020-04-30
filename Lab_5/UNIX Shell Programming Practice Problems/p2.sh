#!/bin/bash

# Find recursively in a directory all ".c" files having more than 500 lines. 
# Stop after finding 2 such files. 

cnt=0
find dir -type f | grep ".c$" | while read F; do
		nrl=`cat $F|wc -l`
		if [ $nrl -gt 500 ]; then
			echo $F
			cnt=$(($cnt+1))
		fi
		if [ $cnt -eq 2 ]; then
			break
		fi
	done	
