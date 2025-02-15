#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

using namespace std;

namespace Netlist {

    void  Term::toXml ( std::ostream& stream){
        stream << indent <<"<term name=\"" << getName() << "\" direction=\"" << Term::toString(getDirection()) << "\"/>\n";
    }

    Term::Term ( Cell* owner , const std::string& name, Direction direction): 
    owner_(owner), name_(name),direction_(direction),type_(External),net_(NULL), node_(this, Net::noid) {
        static_cast<Cell*>(owner_) -> add(this);
    }

    Term::Term ( Instance* owner, const Term* modelTerm ):
    owner_(owner), 
    name_(modelTerm->getName()),
    direction_(modelTerm->getDirection()),
    type_(Internal),
    net_(modelTerm->getNet()),
    node_(this, Net::noid)
    {
        static_cast<Instance*>(owner_) -> add(this);
    }
    
    Term::~Term(){
        net_->remove(&node_);
    }
  
    Cell* Term::getOwnerCell() const{
        if(isInternal()){ return static_cast<Cell*>(getInstance()->getCell());}
        return static_cast<Cell*>(owner_);
    }

    void Term::setNet (Net* newNet){  
        net_ = newNet;   
        //On récupère l'objet node du term
        Node* n = (getNode());
        //On ajoute le node au vecteur des nodes dans net
        net_->add(n);

        size_t emplacement=0;
        for(auto node : net_->getNodes()){
            if(node == n)
                n->setId(emplacement);
            ++emplacement;
        }
    }

    void Term::setNet (const std::string& nameToFind){
        Cell* cell = getOwnerCell();
        for(auto& net : cell->getNets()){
            if (net->getName() == nameToFind){
                setNet (net);
                break;
            }
        }
    }

    void  Term::setPosition  ( const Point& p){
       node_.setPosition(p);
    }

    void  Term::setPosition  ( int x, int y ){
        node_.setPosition(x,y);
    }

}
