BEGIN{ n }
length($6){
	split($6,a,"/")
	group = a[length(a)-1]
	if(!f[group]) gr[n++] = group
	f[group]++
}
END{	
	for(i=0;i<n;i++)
		print "From group " gr[i] " there are " f[gr[i]] " users connected."
}
