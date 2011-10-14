#include <stdio.h>
#include <math.h>
    
main(int argc , char *argv[])

{
	float a, b, c, x;
  	float b1, b2, h1, h2;
  	float base, oldtrap, newtrap, answer, distance;
  	int count,number;
   
   	if (argc != 7) 
	{  
      		printf("usage: %s a b c base1 base2 x\n",argv[0]);
      		exit(-1);
    	}
  
  	a = atof(argv[1]);
  	b = atof(argv[2]);
  	c = atof(argv[3]);
  	b1 = atof(argv[4]);
  	b2 = atof(argv[5]);
  	number = atof(argv[6]);

  	distance = b2-b1;
  	base = distance/number;
  	oldtrap = 0;
    	for ( count = 0; count < number ; count++) 
	{
      		x = b1;
      
      		h1 = a*pow(x,2) + b*x + c;
      		x = b1 + base;
      		h2 = a*pow(x,2) + b*x + c;
      		b1 = x;
      		newtrap = (distance)/number * (h1+h2)/2;
      		answer = newtrap + oldtrap;
      		oldtrap = answer;
	}
  	printf("AREA OF TRAPEZOID: ");
  	printf("%f\n",answer);
  	exit ();
}

