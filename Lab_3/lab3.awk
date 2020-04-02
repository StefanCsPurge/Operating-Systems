BEGIN {n=0 }
/Dan/ && substr($1,length($1))%2==0{
	split($6,a,"/")
	group = a[length(a)-1]
	if(f[group] == 0)
		gr[n++] = group
	f[group]++
}
END{
	for(i=0;i<n;i++)
		print gr[i] ": " f[gr[i]]
	print "Therefore there are " n " groups that contain students with the name Dan that have an even ID"
}
