
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "cBox.h"


void  swap ( long* a, long* b )
{ long tmp = *a; *a = *b; *b = tmp; }


long min ( long a, long b )
{ return (a > b) ? b : a; }


long max ( long a, long b )
{ return (a > b) ? a : b; }


static size_t  boxAllocateds_ =  0;


size_t  boxAllocateds ()
{ return boxAllocateds_; }


Box* boxCreateEmpty ()
{
  fprintf( stderr, "boxCreateEmpty()\n" );

  Box* box = (Box*)malloc( sizeof(Box));
  box->name_ = (char*)malloc( sizeof(char)*1024 );
  strcpy( box->name_, "Unknown" );
  box->x1_ =  1;
  box->y1_ =  1;
  box->x2_ = -1;
  box->y2_ = -1;
  ++boxAllocateds_;

  return box;
}


Box* boxCreate ( const char* name, long x1_, long y1_, long x2_, long y2_ )
{
 
  fprintf( stderr, "boxCreate() \"%s\" [%li %li %li %li]\n", name, x1_, y1_, x2_, y2_ );
  
  Box* box = (Box*)malloc( sizeof(Box));
  box->name_ = (char*)malloc( sizeof(char)*1024 );
  strncpy( box->name_, name, 1024 ); 
  box->x1_ = x1_;
  box->y1_ = y1_;
  box->x2_ = x2_;
  box->y2_ = y2_;

  if (x1_ > x2_) swap( &box->x1_, &box->x2_ );
  if (y1_ > y2_) swap( &box->y1_, &box->y2_ );

  ++boxAllocateds_;

  return box;
}


Box* boxCreateCopy ( const Box* other )
{
  fprintf( stderr, "boxCreateCopy() from %s", other->name_ );

  Box* box = (Box*)malloc( sizeof(Box) );
  box->name_ = (char*)malloc( sizeof(char)*1024 );
  strncpy( box->name_, other->name_, 1023 );
  strncat( box->name_, "_c", 1023 - strlen(box->name_) );
  box->x1_ = other->x1_;
  box->y1_ = other->y1_;
  box->x2_ = other->x2_;
  box->y2_ = other->y2_;

  return box;
}


void  boxDelete ( Box* box )
{
  fprintf( stderr, "boxDelete() \"%s\"\n", box->name_ );
  free( box->name_ );
  free( box );

  if (boxAllocateds_ > 0) --boxAllocateds_;
}


long  boxIsEmpty ( const Box* box )
{ return (box->x1_ > box->x2_) || (box->y1_ > box->y2_); }


long  boxGetWidth ( const Box* box )
{ return (boxIsEmpty(box)) ? 0 : (box->x2_ - box->x1_); }


long  boxGetHeight ( const Box* box )
{ return (boxIsEmpty(box)) ? 0 : (box->y2_ - box->y1_); }


long  boxIntersect ( const Box* box1, const Box* box2 )
{  // fprintf(stderr,"On rentre dans boxIntersect");
  if (boxIsEmpty(box1) || boxIsEmpty(box2)) return 0;
  if (  (   (box1->x2_ <= box2->x1_) && (box1->y1_ <= box2->y2_))
	|| ((box1->x1_ >= box2->x2_) && (box1->y2_ >= box2->y1_))  ) return 0;
  return 1;
}


Box* boxIntersection ( const Box* box1, const Box* box2 )
{
  
  if (! boxIntersect(box1,box2)) return boxCreateEmpty();
  Box* intersection = boxCreateEmpty();
  strncpy( intersection->name_, box1->name_, 1023 );
  strncat( intersection->name_, "."        , 1023 - strlen(intersection->name_) );
  strncat( intersection->name_, box2->name_, 1023 - strlen(intersection->name_) );
  intersection->x1_ = max( box1->x1_, box2->x1_ );
  intersection->y1_ = max( box1->y1_, box2->y1_ );
  intersection->x2_ = min( box1->x2_, box2->x2_ );
  intersection->y2_ = min( box1->y2_, box2->y2_ );
  return intersection;
}


Box* boxInflate ( Box* box, long dx1, long dy1, long dx2, long dy2 )
{
  box->x1_ -= dx1;
  box->y1_ -= dy1;
  box->x2_ += dx2;
  box->y2_ += dy2;

  return box;
}


void  boxPrint ( FILE* o, Box* box )
{
  fprintf( o, "<\"%s\" [%li %li %li %li]>", box->name_, box->x1_, box->y1_, box->x2_, box->y2_ );
} 
