#include "timer.h"
#include "vector.h"
#include <iostream>
#include <vector>


using namespace vector_bench;
using namespace std;

int main ( int argc, char* argv[] )
{
  backInsert    ();
  frontInsert   ();
  sortEachInsert();

  return 0;
}
