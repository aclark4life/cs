//
//  pqueue.h
//
//  A. L. Delcher
//  7 Feb 98
//
//  Class definitions for a binary heap min-priority queue.
//  Uses typedef instead of templates.
//


#ifndef  PQUEUE_H_INCLUDED
#define  PQUEUE_H_INCLUDED


#include  "delcher.h"

const int  DEFAULT_HEAP_SIZE = 100;

typedef  int  KEY_TYPE;

struct  PQ_Entry
  {
   KEY_TYPE  Key;
   // Other Data here

   //  Define how to compare entries.
   int  operator <  (const PQ_Entry & P)  const
     {
      return  (Key < P . Key);
     }
   int  operator <=  (const PQ_Entry & P)  const
     {
      return  (Key <= P . Key);
     }
  };


class  Priority_Q
  {
  protected:
   PQ_Entry  * Data;
   int  Entry_Ct;
   int  Size;

   void  Sift_Down  (int i);

  public:
   Priority_Q  (int = DEFAULT_HEAP_SIZE);       // Constructor
   Priority_Q  (const Priority_Q &);            // Copy constructor
   ~ Priority_Q  ();                            // Destructor
   PQ_Entry  Extract_Min  ();
   void  Insert  (const PQ_Entry &);
  };


#endif
