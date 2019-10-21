#ifndef  NETLIST_NET_H
#define  NETLIST_NET_H

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

    Cell*                     getCell       () const;
    const std::string&        getName       () const;
    unsigned int              getId         () const;
    Term::Type                getType       () const;
    const std::vector<Node*>& getNodes      () const;
    size_t                    getFreeNodeId () const;

    void  add    ( Node* );
    bool  remove ( Node* );
};

}  // Netlist namespace.

#endif  // NETLIST_CELL_H
