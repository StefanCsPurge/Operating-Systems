
$5 ~ / [a-zA-Z]*[b-z]\>/ {m++}
$5 ~ / [a-zA-Z]*a\>/ {w++}
END {
     print "Men:", m
     print "Women:", w
}

