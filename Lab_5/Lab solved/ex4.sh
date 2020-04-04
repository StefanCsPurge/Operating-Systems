#!/bin/bash

find $1 -type f -perm -222 | while read F; do
	mv "$F" "$F.all"
done
