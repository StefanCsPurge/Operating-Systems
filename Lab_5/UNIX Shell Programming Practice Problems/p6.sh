#!/bin/bash

# Find recursively in a directory, all the files that have write permissions for everyone. 
# Display their names, and the permissions before and after removing the write permission 
# for everybody.

find dir -type f -perm -002 | while read F; do
		echo `ls -l $F | cut -d' ' -f1` $F
		chmod o-w $F
		echo `ls -l $F | cut -d' ' -f1` $F
	done
