#ifndef  NETLIST_NET_H
#define  NETLIST_NET_H

#include <vector>
#include <limits>
#include "Term.h"

namespace Netlist{

class Cell;
class Node;
class Line;
class Term;

class Net{
    
    Cell*               owner_;
    std::string         name_;
    unsigned int        id_;
    Term::Type          type_;
    std::vector<Node*>  nodes_;
    std::vector<Line*>  lines_;
    
public:
    static const size_t  noid;

    Net     ( Cell*, const std::string&, Term::Type );
    ~Net     ();

    inline       Cell*               getCell       () const;
    inline const std::string&        getName       () const;
    inline const std::vector<Node*>& getNodes      () const;
    inline       Node*               getNode       (size_t) const;
    inline       unsigned int        getId         () const;
    inline       Term::Type          getType       () const;
    inline const std::vector<Line*>& getLines      () const;
    inline       void                add           ( Line* line );

    size_t                           getFreeNodeId () const;
    void  add     ( Node* );
    bool  remove  ( Line* line );
    bool  remove  ( Node* );
    void  toXml   ( std::ostream& stream);
    static Net*  fromXml (Cell*, xmlTextReaderPtr);
};

    inline const std::vector<Node*>& Net::getNodes ()          const{ return nodes_;    }
    inline       Node*               Net::getNode  (size_t id) const{ return nodes_[id];}
    inline const std::string&        Net::getName  ()          const{ return name_ ;    }
    inline       Term::Type          Net::getType  ()          const{ return type_ ;    }
    inline       unsigned int        Net::getId    ()          const{ return id_   ;    }
    inline       Cell*               Net::getCell  ()          const{ return owner_;    }
    inline const std::vector<Line*>& Net::getLines ()          const{ return lines_;    }
    inline       void                Net::add      ( Line* line )   { if (line) lines_.push_back( line ); }
 

}  // Netlist namespace.

#endif  // NETLIST_NET_H
