#!/bin/bash
TTY=`tty`

find $1 -type f | while read F; do
	rights=`stat -c "%a" $F`
	if [ $rights -eq 755 ];then
		echo Do you want to change access rights for file $F to 744? [y/n]
		read ans <$TTY
		if [ $ans = y ];then
		       chmod 744 $F
	        else continue
	 	fi
	fi
done	
