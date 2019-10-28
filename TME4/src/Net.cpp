#include <iostream>
#include  <limits>
#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

namespace Netlist{
    using namespace std;

    const size_t  Net::noid = numeric_limits<size_t>::max();

    void  Net::toXml ( std::ostream& stream){
        stream << indent++ << "<net name=\"" << getName() << "\" type=\"" << Term::toString(getType()) << "\"/>\n";
        for(auto node : getNodes()) node->toXml(stream);
        --indent;
    }

    Net::Net     ( Cell* owner, const std::string& name, Term::Type type):
    owner_(owner), name_(name), id_(owner->Cell::newNetId ()), type_(type){

        owner_ -> add(this);

        //On récupère le term concerné
        //Term* term = (owner_ -> getTerm(name));
        //std::cout << "Term recupere : " << term->getName()<<std::endl;
        //On met a jour le pointeur du term ver sle net
       // std::cout << "term->net avant : " << term->getNet() << std::endl;
        //term->setNet(this);
        //std::cout << "term->net apres : " << term->getNet() << std::endl;
        /*//On récupère l'objet node du term
        Node* n = (term->getNode());
        //On met à jour son id 
        n->setId(getFreeNodeId());
        //On ajoute le nodeau vedcteur des nodes dans net
        add(n);
        
        toXml(std::cout);*/

    }
    Net::~Net(){}

    void Net::add (Node* n){ 
        size_t freeNode = getFreeNodeId();
        //std::cout << "freeNode =" << freeNode << std::endl;
        //std::cout << "node.size() avant = " << nodes_.size() << std::endl;
        if(freeNode >= nodes_.size())   nodes_.push_back(n);
        else                            nodes_[freeNode] = n;
        //std::cout << "node.size() apres = " << nodes_.size() << std::endl;

    }

    bool  Net::remove ( Node* n){
        for (auto node : nodes_){
            if (n == node) node = NULL;
            return true;
        }
        std::cout << "attention, destruction du pointeur de node dans Net::remove() échouée" << std::endl;
        return false;
    }

    size_t Net::getFreeNodeId() const {
        size_t freeNode=0;
        
        for (auto node : nodes_){
            if (node == NULL) return freeNode;
            ++freeNode;
        }

        return freeNode;
    }


}