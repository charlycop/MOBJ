#include <cstdlib>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

using namespace std;

namespace Netlist{

    void  Instance::toXml ( std::ostream& stream){
        stream << indent << "<instance name=\"" << getName() << "\" mastercell=\"" << getMasterCell()->getName() << "\" x=\"" << getPosition().getX() << "\" y=\"" << getPosition().getY() << "\"/>\n";
    }

    Instance* Instance::fromXml(Cell* cell, xmlTextReaderPtr reader){

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "instance"){

            string         name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            string    mastercell= xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"mastercell"));
            int x, y;
            xmlGetIntAttribute( reader, "x"   , x );
            xmlGetIntAttribute( reader, "y"   , y );

            Cell* masterCell = Cell::find(mastercell);

            if(masterCell->getName() == mastercell && not name.empty()){
                Instance* newInstance = new Instance(cell, masterCell , name);
                newInstance->setPosition(x, y);
                return newInstance;
            }
        }
        cerr << "[ERROR] Problem inside Instance::fromXml" << endl;
        return nullptr;
    }

    Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):
    owner_(owner), masterCell_(model), name_(name){
        (owner_) -> add(this);

        for(const auto t : masterCell_->getTerms()) {
            new Term(this, t);
        }
    }
    
    Instance::~Instance      (){
        for (auto& term : terms_) term->~Term();
    }
    
    Term* Instance::getTerm       ( const std::string& name) const{
        for(auto term : terms_){
            if (term->getName() == name)
                return term;
        }
        return NULL;
    }

    bool  Instance::connect       ( const std::string& name, Net* n){
        Term* term = getTerm( name );
        if (term == NULL)
            return false;
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

        // On va chercher les terms du symbol associé
        for(auto& termCell : getMasterCell()->getSymbol()->getShapes()){
            TermShape* termshape = dynamic_cast<TermShape*>(termCell);
            if (termshape){      
                string name = termshape->getTerm()->getName();
                for(auto& termInst : getTerms()){
                    if(name == termInst->getName()){
                        int x1 = termshape->getX1() + x;
                        int y1 = termshape->getY1() + y;
                        termInst->setPosition(x1, y1);
                        cout << "Nouvelle coordonnées term : " 
                             << termInst->getName() << "("
                             << x1 << "," << y1 
                             << ") - Instance : " << getName() <<endl;
                    }
                }
            }
        }
    }


}