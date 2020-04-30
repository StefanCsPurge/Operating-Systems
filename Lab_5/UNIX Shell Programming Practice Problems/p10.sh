#!/bin/bash

# Display the session count and full names of all the users who logged into the system 
# this month, sorting the output by the session count in descending order.

echo The users who logged into the system this month are:
last -s `date +"%Y-%m-01"` | sort | cut -d' ' -f1 | uniq -c | sort -k1nr |\
	while read U; do
		count=`echo $U | awk '{print $1}'`
		user=`echo $U | awk '{print $2}'`
		if [ ! -z $user ]; then
			found=`grep "^$user" /etc/passwd`
			if [ ! -z $found ]; then
				fullName=`echo $found|awk -F: '{print $5}'`
				echo "Session count: $count   Full name: $fullName"
			fi
		fi
	done
