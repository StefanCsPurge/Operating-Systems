#!/bin/bash

# Find recursively in a given directory all the symbolic links, 
# and report those that point to files/directories that no longer exist.

find $1 -type l | while read L; do
	if [ ! -e $L ]; then
		echo $L points to a file/directory that no longer exists
	fi
done
