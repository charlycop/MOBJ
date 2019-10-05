
#include "cBox.h"


Box* testFunction ( Box* ab )
{
  fprintf( stderr, "  + testFunction() called.\n" );

  Box* area = boxCreate( "area", 0, 0, 15, 50 );
  fprintf( stderr, "  | Intersection between:\n" );
  fprintf( stderr, "  |   " ); boxPrint( stderr, area ); fprintf( stderr, "\n" );
  fprintf( stderr, "  |   " ); boxPrint( stderr, ab   ); fprintf( stderr, "\n" );
  fprintf( stderr, "  | Gives:\n" );

  if (boxIntersect(area,ab)) {
    Box* intersection = boxIntersection( area, ab );
    fprintf( stderr, "  |   " ); boxPrint( stderr, intersection ); fprintf( stderr, "\n" );
    boxDelete( intersection );
  } else {
    fprintf( stderr, "  |   No intersection.\n" );}
    boxDelete( area );	
  return ab;
}


int  main ( int argc, char* argv[] )
{
  Box* b0 = boxCreateEmpty();
  Box* b1 = boxCreate( "b1", 15, 10, 30, 20 );

  fprintf( stderr, "Allocated boxes: %lu\n", boxAllocateds() );

  fprintf( stderr, "\nTest 1\n" );
  boxPrint( stderr, b1 ); fprintf( stderr, "\n" );
  testFunction( b1 );


  fprintf( stderr, "\nTest 2\n" );
  boxInflate( b1, 5, 5, 5, 5 );
  boxPrint( stderr, b1 ); fprintf( stderr, "\n" );
  testFunction( b1 );

  fprintf( stderr, "\nTest 3\n" );
  fprintf( stderr, "+ Box \"%s\" empty:  %li\n", b1->name_, boxIsEmpty  (b1) );
  fprintf( stderr, "| Box \"%s\" width:  %li\n", b1->name_, boxGetWidth (b1) );
  fprintf( stderr, "| Box \"%s\" height: %li\n", b1->name_, boxGetHeight(b1) );
  boxInflate( b1, -11, -11, -11, -11 );
  fprintf( stderr, "+ Box \"%s\" empty:  %li (inflated -11)\n", b1->name_, boxIsEmpty(b1) );
  fprintf( stderr, "| Box \"%s\" width:  %li\n", b1->name_, boxGetWidth (b1) );
  fprintf( stderr, "| Box \"%s\" height: %li\n", b1->name_, boxGetHeight(b1) );

  fprintf( stderr, "\n" );


  boxDelete( b1 );
  boxDelete( b0 );

  fprintf( stderr, "Allocated boxes: %lu\n", boxAllocateds() );
  return 0;
}
