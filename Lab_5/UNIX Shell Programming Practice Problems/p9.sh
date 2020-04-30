#!/bin/bash

# Write a script that finds in a given directory hierarchy, 
# all duplicate files and displays their paths.

echo The identical found files are \(in groups\):
echo
find $1 -type f | xargs md5sum | sort | uniq -w32 --all-repeated=separate | cut -c 35-
