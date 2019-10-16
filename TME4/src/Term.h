#ifndef  NETLIST_TERM_H   // Le define *doit* être différent dans
#define  NETLIST_TERM_H   // chaque fichier (i.e. nom de classe).

// Les includes sont mis *à l'extérieur* du namespace.
#include <string>
#include "Point.h"
#include "Node.h"


namespace Netlist {

  // Les *forward declarations* des autres objets de la
  // structure de données sont mis *à l'intérieur* du namespace.
  class Term;
  class Net;
  class Instance;
  class Cell;

  class Term {

    enum Type      { Internal=1, External=2 };
    enum Direction { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };

    void*         owner_;
    std::string   name_;
    Direction     direction_;
    Type          type_;
    Net*          net_;
    Node          node_;

    static std::string  toString    ( Type );
    static std::string  toString    ( Direction );
    static Direction    toDirection ( std::string );
    

    public:

        Term ( Cell*    , const std::string& name, Direction );
        Term ( Instance*, const Term* modelTerm );
        ~Term ();

        inline bool               isInternal   () const; //FAIT
        inline bool               isExternal   () const; //FAIT
        inline const std::string& getName      () const; //FAIT
        inline Node*              getNode      ();       //FAIT
        inline Net*               getNet       () const; //FAIT
        inline Cell*              getCell      () const; //FAIT
               Cell*              getOwnerCell () const; //FAIT
        inline Instance*          getInstance  () const; //FAIT
        inline Direction          getDirection () const; //FAIT
        inline Point              getPosition  () const; //FAIT
        inline Type               getType      () const; //FAIT

               void  setNet       ( Net* );              //FAIT
               void  setNet       ( const std::string& );//FAIT
        inline void  setDirection ( Direction );         //FAIT
               void  setPosition  ( const Point& );      //FAIT
               void  setPosition  ( int x, int y );      //FAIT



  };
    
    

    inline bool               Term::isInternal   () const{ return (type_ == 1) ;       }
    inline bool               Term::isExternal   () const{ return (type_ == 2) ;       }
    inline const std::string& Term::getName      () const{ return name_        ;       }
    inline Node*              Term::getNode      ()      { return *node_       ;       }
    inline Net*               Term::getNet       () const{ return net_         ;       }
    inline Cell*              Term::getCell      () const{ if (isExternal()) return (Cell*)owner_    ; return NULL;}
    inline Instance*          Term::getInstance  () const{ if (isInternal()) return (Instance*)owner_; return NULL;}
    inline Direction          Term::getDirection () const{ return direction_   ;       }
    inline Point              Term::getPosition  () const{ return node_.Node::getPosition(); }
    inline Type               Term::getType      () const{ return type_        ;       }
    inline void               Term::setDirection ( Direction ){ direction_ = Direction;}


}

#endif  // NETLIST_TERM_H