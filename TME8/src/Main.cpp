// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/7>" -*-


#include  <QApplication>
#include  <QtGui>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "CellViewer.h"

using namespace Netlist;
using namespace std;


int  main (int argc , char* argv []) {


  Cell::load( "vdd" );
  Cell::load( "gnd" );
  Cell::load( "TransistorN" );
  Cell::load( "TransistorP" );
  Cell::load( "and2" );
  Cell::load( "or2" );
  Cell::load( "xor2" );
  Cell::load( "halfadder" );
  Cell::load( "inverter" );
  Cell*test = Cell::load( "fulladder" );
  
  QApplication* qa = new  QApplication(argc ,argv);
  CellViewer* viewer = new  CellViewer();


  viewer->show ();
  int  rvalue = qa ->exec ();
  delete  qa;
  return  rvalue;
}
