#!/bin/bash

find -type f | while read F; do
	if file "$F" | grep -q "ASCII text"; then
		nrL=`cat "$F"|wc -l`
		echo "The text file is: " `basename "$F"`
		echo
		if [ $nrL -lt 10 ]; then 
			cat "$F"
		else
			head -n 5 "$F"; tail -n 5 "$F"
		fi
		echo
	fi
done
