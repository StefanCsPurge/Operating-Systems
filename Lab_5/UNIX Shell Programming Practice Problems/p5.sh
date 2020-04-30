#!/bin/bash

# Write a script that receives dangerous program names as command line arguments. 
# The script will monitor all the processes in the system, and whenever a program 
# known to be dangerous is run, the script will kill it and display a message. 

if [ -z $1 ]; then
	echo No dangerous program names provided!
	exit 1
fi

echo Monitoring started...
while true; do 
	for A in $@; do
		ps -aux | grep $A | while read P; do
			if ! echo $P | egrep -q 'p5|grep|ps'; then
				pid=`echo $P | awk '{print $2}'`
				echo Found $A PID $pid !
				kill -9 $pid
				echo $pid killed
				echo
			fi
		done
	done
done
