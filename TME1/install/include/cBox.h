
#ifndef  C_BOX_H
#define  C_BOX_H  1

#include <stddef.h> 
#include <stdio.h>

struct Box_s {
    char* name_;
    long  x1_;
    long  y1_;
    long  x2_;
    long  y2_;
}; // Aout du ";"

typedef struct Box_s Box;

size_t  boxAllocateds   ();
Box*    boxCreateEmpty  ();
Box*    boxCreate       ( const char* name, long x1, long y1, long x2, long y2 );
Box*    boxCreateCopy   ( const Box* other );
void    boxDelete       ( Box* box );
long    boxIsEmpty      ( const Box* box );
long    boxGetWidth     ( const Box* box );
long    boxGetHeight    ( const Box* box );
long    boxIntersect    ( const Box* box1, const Box* box2 );
Box*    boxIntersection ( const Box* box1, const Box* box2 );
Box*    boxInflate      ( Box* box, long dx1, long dy1, long dx2, long dy2 );
void    boxPrint        ( FILE* o, Box* box );


#endif  // C_BOX_H
