//  coolness.h
//
//  Frequently used routines.

#include  <iostream.h>
#include  <iomanip.h>
#include  <fstream.h>

#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>
#include  <ctype.h>
#include  <limits.h>
#include  <float.h>
#include  <time.h>
#include  <assert.h>

#ifndef  __COOLNESS_H_INCLUDED
#define  __COOLNESS_H_INCLUDED


#define  TRUE  1
#define  FALSE  0
#ifndef  EXIT_FAILURE
#define  EXIT_FAILURE  -1
#endif
#ifndef  EXIT_SUCCESS
#define  EXIT_SUCCESS  0
#endif


#if 0

FILE *  File_Open  (const char *, const char *);
void *  Safe_malloc  (size_t);
void *  Safe_realloc  (void *, size_t);
char *  strdup  (char * &, const char *);
void Pause(void);


FILE *  File_Open  (const char * Filename, const char * Mode)

/* Open  Filename  in  Mode  and return a pointer to its control
*  block.  If fail, print a message and exit. */

  {
   FILE  *  fp;

   fp = fopen (Filename, Mode);
   if  (fp == NULL)
       {
        fprintf (stderr, "ERROR:  Could not open file  %s \n", Filename);
        exit (EXIT_FAILURE);
       }

   return  fp;
  }



void *  Safe_malloc  (size_t Len)

/* Allocate and return a pointer to  Len  bytes of memory.
*  Exit if fail. */

  {
   void  * P;

   P = malloc (Len);
   if  (P == NULL)
       {
        fprintf (stderr, "ERROR:  malloc failed\n");
        exit (EXIT_FAILURE);
       }

   return  P;
  }



void *  Safe_realloc  (void * Q, size_t Len)

/* Reallocate memory for  Q  to  Len  bytes and return a
*  pointer to the new memory.  Exit if fail. */

  {
   void  * P;

   P = realloc (Q, Len);
   if  (P == NULL)
       {
        fprintf (stderr, "ERROR:  realloc failed\n");
        exit (EXIT_FAILURE);
       }

   return  P;
  }



char *  strdup  (char * & S1, const char * S2)

/* Allocate memory in  S1  for a copy of string  S2  and copy
*  it.  Return a pointer to  S1 . */

  {
   S1 = (char *) Safe_malloc (1 + strlen (S2));
   strcpy (S1, S2);

   return  S1;
  }


void Pause(void)
{ /* pauses program so user can read output */

  printf("\nPress <enter>...");
  while (getchar() != '\n')
	;

}

#endif
#endif


