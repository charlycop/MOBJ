// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/4-5>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>

// Librairies "maison"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

using namespace std;
using namespace Netlist;



int main ( int argc, char* argv[] )
{
  cout << "Chargement des modeles:" << endl;
  cout << "- <and2> ..." << endl;
  Cell* and2 = Cell::load( "and2" );

  cout << "- <or2> ..." << endl;
  Cell* or2 = Cell::load( "or2" );

  cout << "- <xor2> ..." << endl;
  Cell* xor2 = Cell::load( "xor2" );

  cout << "- <halfadder> ..." << endl;
  Cell* halfadder = Cell::load( "halfadder" );
and2->toXml(cout);
or2 ->toXml(cout);
xor2->toXml(cout);
  cout << "\nContenu du <halfadder>:" << endl;
  halfadder->toXml( cout );


  return 0;

}
