#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include </usr/sys/h/timeb.h>


int improvedbubble(int a[],int n)
{
  int i, pass = 1, sorted = 0;
  int temp;
  while (sorted == 0)
    {
      sorted = 1;
      for (i = 0; i < n - pass; i++)
	if (a[i] > a[i+1])
	  {
	    temp = a[i];
	    a[i] = a[i+1];
	    a[i+1] = temp;
	    sorted = 0;
	  }
      pass++;
    }
}

/*int bubblesort (int a[], int n )

  int i,j,t ;
  for(i = 0; i < n ; i++ )
    for ( j = i + 1 ; j < n ; j++)
      if (a[i] > a[j])
	{ t = a[i];
	  a[i] = a[j];
	  a[j] = t;
	}
}*/

int main(void){
  
  int a[10000];
  int i;
  int j;
  int r;
  struct timeb t1,t2;
  double difftime;
  
 /* ftime(&t1) ; */
  
  for(i=0;i<10000;i++){                   
    r = rand();
    a[i] = r;
  } 
  
  printf("seconds since 1/1/1970 gmt: %1d\n",t1.time);
  printf("thousandths of a second: %d\n", t1.millitm);
 ftime(&t1);
 improvedbubble(a,10000);
 

  ftime (&t2);
  printf("seconds since 1/1/1970 gmt: %1d\n",t1.time);
  printf("thousandths of a second: %d\n", t1.millitm);
  
  difftime = (double)t2.time-t1.time+(t2.millitm-t1.millitm)/1000.0;

  printf ("elapsed time = %.3f seconds\n", difftime);
/*  return 0; */
  
  for(i=0;i<10000;i++)
    fprintf(stderr,"a[%d] = %d\n",i,a[i]); 
  
  printf ("elapsed time = %.3f seconds\n", difftime);

}

