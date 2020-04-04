#!/bin/bash

find $1 -type f | while read F; do
	if egrep -q '[0-9]{6,}' "$F"; then
		basename $F
	       	echo "The numbers are " `grep -o '[0-9]\{6,\}' "$F" | sed 's/\n/ /g'`
		echo
	fi
done
