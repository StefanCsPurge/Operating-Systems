/Mo/ { 
	for(i=2;i<=NF;i++)
		mondays[n++] = $i
}
/Su/{
    for(j=0;j<n;j++)
       for(i=2;i<=NF;i++)
       		if($i == mondays[j]+6)
		{ print mondays[j]
			break
		}
}


