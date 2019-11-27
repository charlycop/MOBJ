// -*- explicit-buffer-name: "Symbol.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_SYMBOL_H
#define NETLIST_SYMBOL_H

#include  <libxml/xmlreader.h>
#include  <string>
#include  <vector>
#include  "Box.h"
#include "Point.h"
#include "Term.h"
#include "Shape.h"

namespace Netlist {

  class Term;
  class Cell;
  class Shape;
  class TermShape;


  class Symbol {
    public:
                                        Symbol          ( Cell* );
                                       ~Symbol          ();
      inline Cell*                      getCell         () const;
             Box                        getBoundingBox  () const;
             Point                      getTermPosition ( Term* ) const;
             TermShape*                 getTermShape    ( Term* ) const;
      inline const std::vector<Shape*>  getShapes       () const;
      inline void                       add             ( Shape* );
             void                       remove          ( Shape* );
             void                       toXml           (  std::ostream& ) const;
             static Symbol*             fromXml         ( Cell*, xmlTextReaderPtr );
    private:                                            
                                        Symbol          ( const Symbol& );
             Symbol&                    operator=       ( const Symbol& );
    private:
      Cell*                owner_;
      std::vector<Shape*>  shapes_;
  };

  inline       Cell*                Symbol::getCell        () const   { return owner_ ;         }
  inline const std::vector<Shape*>  Symbol::getShapes      () const   { return shapes_;         }
  inline       Point                Symbol::getTermPosition( Term* t ) const { return t->getPosition();}
  inline       void                 Symbol::add            ( Shape* s){ shapes_.push_back(s);   }


  }// Netlist namespace.

#endif  // NETLIST_SYMBOL_H
