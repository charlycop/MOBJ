#include  <cstdlib>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist{

    Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):
    owner_(owner), masterCell_(model), name_(name){}
    
    Instance::~Instance      (){
        for (auto& term : terms_) term->~Term();
    }
    
    Term* Instance::getTerm       ( const std::string& ) const{
        for(auto& term : getTerms()){
            if (term->getName() == name_) return term;
        }
        return NULL;
    }



    //bool  Instance::connect       ( const std::string& name, Net* ){}
    //void  Instance::add           ( Term* ){}
    //void  Instance::remove        ( Term* ){}
    //void  Instance::setPosition   ( const Point& ){}
    //void  Instance::setPosition   ( int x, int y ){}


}