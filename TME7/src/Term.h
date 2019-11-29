#ifndef  NETLIST_TERM_H   // Le define *doit* être différent dans
#define  NETLIST_TERM_H   // chaque fichier (i.e. nom de classe).

// Les includes sont mis *à l'extérieur* du namespace.
#include <string>
#include "Node.h"
#include "XmlUtil.h"


namespace Netlist {

  // Les *forward declarations* des autres objets de la
  // structure de données sont mis *à l'intérieur* du namespace.
  class Net;
  class Instance;
  class Cell;
  class Point;

  class Term {

    public:
        enum Type      { Internal=1, External=2 };
        enum Direction { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };

                                  Term ( Cell*    , const std::string& name, Direction );
                                  Term ( Instance*, const Term* modelTerm );
                                 ~Term ();

        inline bool               isInternal   () const; 
        inline bool               isExternal   () const; 
        inline const std::string& getName      () const; 
        inline NodeTerm*          getNode      ();       
        inline Net*               getNet       () const; 
        inline Cell*              getCell      () const; 
               Cell*              getOwnerCell () const; 
        inline Instance*          getInstance  () const; 
        inline Direction          getDirection () const; 
        inline Point              getPosition  () const; 
        inline Type               getType      () const; 
        static std::string        toString     ( Direction );
        static std::string        toString     ( Type );
        static Type               toType       ( std::string );
        static Direction          toDirection  ( std::string );
               void               setNet       ( Net* );              
               void               setNet       ( const std::string& );
        inline void               setDirection ( Direction );         
               void               setPosition  ( const Point& );      
               void               setPosition  ( int x, int y );    
               void               toXml        ( std::ostream& );
        static Term*              fromXml      ( Cell*, xmlTextReaderPtr );
    private:
        void*         owner_;
        std::string   name_;
        Direction     direction_;
        Type          type_;
        Net*          net_;
        NodeTerm      node_;

}; // Fin class Term

    inline bool               Term::isInternal   () const       { return (type_ == Internal) ;}
    inline bool               Term::isExternal   () const       { return (type_ == External) ;}
    inline const std::string& Term::getName      () const       { return name_        ;       }
    inline NodeTerm*          Term::getNode      ()             { return &node_       ;       }
    inline Net*               Term::getNet       () const       { return net_         ;       }
    inline Cell*              Term::getCell      () const       { if (isExternal()) return (Cell*)owner_    ; return NULL;}
    inline Instance*          Term::getInstance  () const       { if (isInternal()) return (Instance*)owner_; return NULL;}
    inline Term::Direction    Term::getDirection () const       { return direction_   ;             }
    inline Point              Term::getPosition  () const       { return node_.Node::getPosition(); }
    inline Term::Type         Term::getType      () const       { return type_        ;             }
    inline void               Term::setDirection ( Direction d ){ direction_ = d;            }

} // Fin namespace

#endif  // NETLIST_TERM_H