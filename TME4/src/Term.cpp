#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist {

    Term::Term ( Cell* owner , const std::string& name, Direction direction): 
    owner_(owner), name_(name),direction_(direction),type_(External),net_(nullptr), node_(this) {}

    Term::Term ( Instance* owner, const Term* modelTerm ):
    owner_(owner), name_(modelTerm->getName()),direction_(modelTerm->getDirection()),type_(Internal),net_(modelTerm->getNet()), node_(this){}

    Term::~Term(){
        net_->nodes_[node_.id_] = nullptr;
    }
  
    Cell* Term::getOwnerCell() const{
        if(isInternal){ return (getInstance()->owner_);}
        return (Cell*)owner_;
    }

    void Term::setNet (Net* newNet){  net_ = newNet;   }

    void Term::setNet (const std::string& nameToFind){
        Cell* cell = getOwnerCell();
        for(Net* net : cell.getNets()){
            if (net->name_ == nameToFind){
                net_ = net->name_;
                break;
            }
        }
    }

    void  Term::setPosition  ( const Point& p){
        node_.Node::setPosition(p);
    }

    void  Term::setPosition  ( int x, int y ){
        node_.Node::setPosition(x,y);
    }


}
