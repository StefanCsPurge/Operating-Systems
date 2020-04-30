#!/bin/bash

# Find recursively in a directory, all the files with the extension ".log" 
# and sort their lines (replace the original file with the sorted content).

find dir -regex ".*\.log" | while read F; do
	 sort $F > temp
 	 rm $F
	 mv temp $F	 
done
