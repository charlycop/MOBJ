#include  <cstdlib>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

namespace Netlist{

    class Term;

    void  Instance::toXml ( std::ostream& stream){
        stream << indent << "<instance name=\"" << getName() << "\" mastercell=\"" << getMasterCell()->getName() << "\" x=" << getPosition().getX() <<" y=" << getPosition().getY() << "\"/>\n";
    }

    Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):
    owner_(owner), masterCell_(model), name_(name){
        owner_ -> add(this);

        for(auto& t : masterCell_->getTerms()) {
            terms_.push_back(t);
        }

        for(auto& t : terms_){
            t->setType(Term::Internal);
        }
    }
    
    Instance::~Instance      (){
        for (auto& term : terms_) term->~Term();
    }
    
    Term* Instance::getTerm       ( const std::string& name) const{
        for(auto term : terms_){
            //std::cout << "on rentre ici" << std::endl;
            if (term->getName() == name) return term;
        }

        //std::cout << "Attention, Term non trouvé dans la fonction getTerm() de la classe Instance!" << std::endl;
        return NULL;
    }

    bool  Instance::connect       ( const std::string& name, Net* n){
       /* std::cout << "On rentre dans Instance::connect() avec name=" << name << std::endl;
        Term* term = getTerm(name);
        std::cout << "On a recupere le pointeur *term = " << term << std::endl;
        if (term == NULL) return false;

        
        return true;
*/
        Term* term = getTerm( name );
        //std::cout << "Instance::connect()" << name << std::endl;
        if (term == NULL) return false;
        term->setNet( n );
        

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