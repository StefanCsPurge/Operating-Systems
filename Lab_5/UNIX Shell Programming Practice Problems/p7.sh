#!/bin/bash

# Consider a file containing a username on each line. 
# Generate a comma-separated string with email addresses of the users that exist. 
# The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each 
# username. Make sure the generated string does NOT end in a comma. 

D=@scs.ubbcluj.ro
string=""

cat p7input.txt | (while read line; do
	if [ ! -z $line ]; then
		user=`echo $line | cut -d' ' -f1`
		if [ -z $string ]; then
			string="$user$D"
		else
			string+=",$user$D"
		fi
	fi
done
# string=`echo $string | sed 's/,$//'`
echo $string )
