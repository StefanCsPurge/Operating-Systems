#!/bin/bash

# Display all the mounted file systems who are either smaller than 1GB 
# or have less than 20% free space. 

cat df.fake | awk '$2 ~ "M$"{
	size = substr($2,1,length($2)-1) + 0
	free = 100 - substr($5,1,length($5)-1)	
	if (size < 1024 || free < 20)
		print $NF}'
