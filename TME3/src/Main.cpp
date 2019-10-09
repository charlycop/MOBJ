#include "vector.h"

using namespace std;

int main ( int argc, char* argv[] )
{
  cout << endl << endl;
  cout << "**** VECTEURS ****" << endl << endl;
  vector_bench::backInsert    ();
  vector_bench::frontInsert   ();
  vector_bench::sortEachInsert();

  cout << endl << endl;
  cout << "**** LISTES ****" << endl << endl;

  list_bench::backInsert    ();
  list_bench::frontInsert   ();
  list_bench::sortEachInsert();

  cout << endl << endl;
  cout << "**** MAP ****" << endl << endl;
  map_bench::testMap();

  return 0;
}
