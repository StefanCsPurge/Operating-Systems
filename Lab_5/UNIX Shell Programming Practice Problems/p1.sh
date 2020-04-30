#!/bin/bash

# Display a report showing the full name of all the users currently connected,
# and the number of processes belonging to each of them. 

cat who.fake | cut -d' ' -f1 | while read name; do
		nr=`cat ps.fake | grep "^$name" | wc -l`
		echo $name $nr
	done		
