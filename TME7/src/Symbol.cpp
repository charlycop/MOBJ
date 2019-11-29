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
      stream << indent << "<symbol>\n";

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

      for(auto& shape : shapes_){
          ArcShape* arcshape = dynamic_cast<ArcShape*>(shape);
          if (arcshape)
               arcshape->toXml(stream);
      }

      for(auto& shape : shapes_){
          EllipseShape* ellipseshape = dynamic_cast<EllipseShape*>(shape);
          if (ellipseshape)
               ellipseshape->toXml(stream);
      }

      stream << indent << "</symbol>\n" ;
  }

  Symbol*  Symbol::fromXml         ( Cell* c, xmlTextReaderPtr reader){
            cout << "Symbol::fromXml " << endl;
           // cout << xmlCharToString(xmlTextReaderLocalName(reader)) << " - "  << endl;
           // cout << c->getName() << endl;
            //cout << c->getSymbol()->getCell()->getName() << endl;
            cout << xmlCharToString(xmlTextReaderLocalName(reader)) << endl;
            cout << xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name")) << endl;
            Shape* retour;
            if (xmlCharToString(xmlTextReaderLocalName(reader)) != "symbol")
                retour = Shape::fromXml(c->getSymbol(), reader);

            return retour->getSymbol();
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