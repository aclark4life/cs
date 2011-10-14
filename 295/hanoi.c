/*aclark*/              

main()
{ 

	int m[64];    
	int k;
	int i;

	for(k=0;k<64;k++)
	{    					
    		m[k]=2*m[k-1]+1;
    	}   
 
 	for(i=0;i<64;i++) printf("m[%d]=%d\n",i,m[i]); 	

}

 
