#include  <cstdlib>
#include  <fstream>
#include <vector>
#include <iostream>
#include  "XmlUtil.h"
#include  "Cell.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include "Shape.h"



namespace Netlist {

  using namespace std;

  Symbol::Symbol ( Cell* c ): owner_(c)
  {}

  Symbol::~Symbol(){}

  
  void     Symbol::toXml           ( std::ostream& stream) const{}
  Symbol*  Symbol::fromXml         ( Cell* c, xmlTextReaderPtr reader){
        Symbol * s;
        return s;
  }
  Box Symbol::getBoundingBox () const {
    Box bb;

    for (size_t i=0 ; i < shapes_.size() ; ++i)
        bb.merge(shapes_[i]->getBoundingBox());

    return bb;
  }

  TermShape* Symbol::getTermShape  ( Term* t) const{
    for (size_t i=0 ; i < shapes_.size() ; ++i){
        TermShape* termshape = dynamic_cast<TermShape*>(shapes_[i]);
        if (termshape && termshape->getTerm() == t)
            return termshape;
    }
    return 0;
  }

 void Symbol::remove ( Shape* shape){
    if (shape) {
        for ( std::vector<Shape*>::iterator is = shapes_.begin(); is != shapes_.end() ; ++is ) {
            if (*is == shape) {
            shapes_.erase( is );
            }
        }
    }
}







} // Fin namespace