#include  <cstdlib>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist{

    class Term;

    Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):
    owner_(owner), masterCell_(model), name_(name){
        owner_ -> add(this);
    }
    
    Instance::~Instance      (){
        for (auto& term : terms_) term->~Term();
    }
    
    Term* Instance::getTerm       ( const std::string& name) const{
        for(auto term : terms_){
            std::cout << "on rentre ici" << std::endl;
            if (term->getName() == name) return term;
        }

        std::cout << "Attention, Term non trouvé dans la fonction getTerm() de la classe Instance!" << std::endl;
        return NULL;
    }

    bool  Instance::connect       ( const std::string& name, Net* n){
        Term* term = getTerm(name);
        if (term == NULL){
            return false;
        }

        term->setNet(n); 
        return true;
    }



    void  Instance::remove        ( Term* t){
        for (std::vector<Term* > ::iterator it = terms_.begin() ; it != terms_.end() ; ++it){
            if (*it == t) terms_.erase(it);
            break;
        }
        std::cout << "Attention, Term non trouvé dans la fonction remove() de la classe Instance!" << std::endl;
    }
    

    void  Instance::setPosition   ( const Point& p){
        position_.setX(p.getX());
        position_.setY(p.getY()); 
    }

    void  Instance::setPosition   ( int x, int y ){
        position_.setX(x);
        position_.setY(y); 
    }


}