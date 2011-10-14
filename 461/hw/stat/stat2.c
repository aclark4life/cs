#include <stdio.h>

main (int argc, char *argv[])
{

/*	int n;

	n=scanf("stdin:", stdin);
	printf("n=%c",n);
*/

   	int i, n; float x; char name[50]; /* from man page on scanf */
	n = scanf ("%d%f%s", &i, &x, name);

	printf("n=%d",n);

}
