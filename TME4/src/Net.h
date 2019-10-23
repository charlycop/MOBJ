#ifndef  NETLIST_NET_H
#define  NETLIST_NET_H
#include <vector>

namespace Netlist{

    class Cell;
    class Node;
    class Indentation;

class Net{



    Cell*               owner_;
    std::string         name_;
    unsigned int        id_;
    Term::Type          type_;
    std::vector<Node*>  nodes_;

public:
    Net     ( Cell*, const std::string&, Term::Type );
    ~Net     ();

    inline       Cell*               getCell       () const;
    inline const std::string&        getName       () const;
    inline const std::vector<Node*>& getNodes      () const;
    inline       unsigned int        getId         () const;
    inline       Term::Type          getType       () const;
    size_t                           getFreeNodeId () const;

    void  add    ( Node* );
    bool  remove ( Node* );
};

    inline const std::vector<Node*>& Net::getNodes () const{ return nodes_; }
    inline const std::string&        Net::getName  () const{ return name_ ; }
    inline       Term::Type          Net::getType  () const{ return type_ ; }
    inline       unsigned int        Net::getId    () const{ return id_   ; }
    inline       Cell*               Net::getCell  () const{ return owner_; }
 

}  // Netlist namespace.

#endif  // NETLIST_NET_H
