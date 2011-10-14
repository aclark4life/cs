#include <iostream.h>
main()
{
	int Max_Sum = 0 ;
	int S = 0 ;
  	int	 j   =  0 ;
	int i, n;
	int A[100];
	int Max_i = 0 , Max_j = 0 ;
	int end1 =  0 ;
	

	for ( i= 1; i <=n; i++)
	{
		S += A[i];
		if (S < 0)
		{
			S = 0;
			j=i+1;
	
		}
		else if (S > Max_Sum)
		{
			Max_Sum = S;
			Max_j = j;
			Max_i = 1;






		}





	}
	if (Max_Sum == 0 )
	{
		cout<< "A has no positive values " << end1;




	}
	else
	{
		cout<< "Max-sum subarray is A [" << Max_i << " .. "
			<< Max_j << "] with sum = " << Max_Sum << end1;


	}





}

