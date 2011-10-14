//
//  pqueue.h
//
//  A. L. Delcher
//  7 Feb 98
//
//  Class definitions for a binary heap min-priority queue.
//  Uses typedef instead of templates.
//


#include  "pq.h"



Priority_Q :: Priority_Q  (int S)

//  Construct a  Priority_Q  that can hold  S  entries.

  {
   assert  (S >= 0);
   Data = new PQ_Entry [S + 1];
   assert (Data != NULL);
   Size = S;
   Entry_Ct = 0;
  }



Priority_Q :: Priority_Q  (const Priority_Q & H)

//  Construct a copy of Priority_Q  H .

  {
   int  i;

   Size = H . Size;
   Entry_Ct = H . Entry_Ct;
   Data = new PQ_Entry [Size + 1];
   assert (Data != NULL);

   for  (i = 1;  i <= Entry_Ct;  i ++)
     Data [i] = H . Data [i];
  }



Priority_Q :: ~ Priority_Q  ()

//  Destroy this Priority_Q.

  {
   delete [] Data;
  }



PQ_Entry  Priority_Q :: Extract_Min  ()

//  Remove and return the root element of this Priority_Q.

  {
   PQ_Entry  Result;

   assert (Entry_Ct > 0);

   Result = Data [1];
   Data [1] = Data [Entry_Ct --];
   Sift_Down (1);

   return  Result;
  }



void  Priority_Q :: Insert  (const PQ_Entry & D)

//  Insert  D  into this Priority_Q.

  {
   PQ_Entry  * New_Data;
   int  i, j;

   if  (Entry_Ct == Size)
       {
        New_Data = new PQ_Entry [2 * Size];
        assert (New_Data != NULL);
        for  (i = 1;  i <= Size;  i ++)
          New_Data [i] = Data [i];
        delete [] Data;
        Data = New_Data;
        Size *= 2;
       }

   i = ++ Entry_Ct;
   j = i / 2;
   while  (i > 1 && D < Data [j])
     {
      Data [i] = Data [j];
      i = j;
      j /= 2;
     }

   Data [i] = D;

   return;
  }



void  Priority_Q :: Sift_Down  (int i)

//  Rearrange this Priority_Q in the subtree rooted at item  i
//  to move  Data [i]  to its proper position.  All entrees
//  below  i  must already have the Priority_Q property.

  {
   PQ_Entry  D;
   int  j;

   assert  (i > 0);
   
   if  (i > Entry_Ct / 2)
       return;

   D = Data [i];

   j = 2 * i;
   while  (j <= Entry_Ct)
     {
      if  (j < Entry_Ct && Data [j + 1] <  Data [j])
          j ++;
      if  (D <= Data [j])
          break;
      Data [i] = Data [j];
      i = j;
      j = 2 * i;
     }

   Data [i] = D;

   return;
  }



