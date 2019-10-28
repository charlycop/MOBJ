#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

using namespace std;

namespace Netlist {

    /*static std::string  Term::toString    ( Term::Type t){
        if (t==Internal) return "In";
        return "Out";

    }
    */

    void  Term::toXml ( std::ostream& stream){
        stream << indent <<"<term name=\"" << getName() << "\" direction=\"" << Term::toString(getDirection()) << "\"/>\n";
    }

    Term::Term ( Cell* owner , const std::string& name, Direction direction): 
    owner_(owner), name_(name),direction_(direction),type_(External),net_(NULL), node_(this, Net::noid) {
        //std::cout << "on est dans le premier constructeur de TERM" << std::endl;
        static_cast<Cell*>(owner_) -> add(this);
    }

    Term::Term ( Instance* owner, const Term* modelTerm ):
    owner_(owner), name_(modelTerm->getName()),direction_(modelTerm->getDirection()),type_(Internal),net_(modelTerm->getNet()), node_(this){
        static_cast<Instance*>(owner_) -> add(this);

    }

    Term::~Term(){
        net_->remove(&node_);
    }
  
    Cell* Term::getOwnerCell() const{
        if(isInternal()){ return (getInstance()->getCell());}
        return (Cell*)owner_;
    }

    void Term::setNet (Net* newNet){  
        net_ = newNet;   
        //On récupère l'objet node du term
        Node* n = (getNode());
        //std::cout << "on a crécupéré le node : " << n << "pour le net : "<< net_->getName() << std::endl;
        //On ajoute le nodeau vedcteur des nodes dans net
        net_->add(n);

        size_t emplacement=0;
        for(auto node : net_->getNodes()){

            if(node == n) {
              //  std::cout << "node : " << node << " - n : "<< n << "setId("<<emplacement << ")" <<std::endl;
                n->setId(emplacement);
            }
            ++emplacement;
        }

    }

    void Term::setNet (const std::string& nameToFind){
        /*Cell* cell = getOwnerCell();
        for(auto& net : cell->getNets()){
            if (net->name_ == nameToFind){
                net_ = net->name_;
                break;
                */
            }
        
    

    void  Term::setPosition  ( const Point& p){
       //node_.Node::setPosition(p);
    }

    void  Term::setPosition  ( int x, int y ){
        //node_.Node::setPosition(x,y);
    }


}
