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
#include "Box.h"



namespace Netlist {

  using namespace std;

  Symbol::Symbol ( Cell* c ): owner_(c)
  {}

  Symbol::~Symbol(){}

  
  void     Symbol::toXml           ( std::ostream& stream) const{
      stream << indent++ << "<symbol>\n";
      
      for(auto& shape : shapes_){
          BoxShape* boxshape = dynamic_cast<BoxShape*>(shape);
          if (boxshape)
               boxshape->toXml(stream);
      }

      for(auto& shape : shapes_){
          LineShape* lineshape = dynamic_cast<LineShape*>(shape);
          if (lineshape)
               lineshape->toXml(stream);
      }

      for(auto& shape : shapes_){
          TermShape* termshape = dynamic_cast<TermShape*>(shape);
          if (termshape)
                termshape->toXml(stream);
      }

      stream << --indent << "</symbol>\n" ;
  }

  Symbol*  Symbol::fromXml         ( Cell* c, xmlTextReaderPtr reader){
        return nullptr;
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