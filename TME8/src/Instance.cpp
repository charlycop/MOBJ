#include <cstdlib>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Shape.h"
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
        setPosition   (p.getX(), p.getY());
    }

    void  Instance::setPosition   ( int x, int y ){
        position_.setX(x);
        position_.setY(y); 

        for(auto& termCell : getMasterCell()->getSymbol()->getShapes()){ // Pour chaque shape de la Cell de référence
            TermShape* termshape = dynamic_cast<TermShape*>(termCell);
            if (termshape){                                              // Si c'est un TermShape
                string name = termshape->getTerm()->getName();           // On prend son nom
                for(auto& termInst : getTerms()){                        // Pour chaque term de cette Instance
                    if(name == termInst->getName()){                     // Si le termshape à le même nom que le term

                        //Affichage de contrôle.
                        cout << "\n-----"<< "Instance : "                 << termInst->getInstance()->getName() 
                             <<"-----\nPosition du term_("                << name 
                             << ") : (" << termInst->getPosition().getX() << "," << termInst->getPosition().getY() 
                             << ")\nPosition TermShape de la Cell : "     << "(" << termshape->getX1() << "," << termshape->getY1()
                             << ")\nPosition de l'Instance : ("           << getPosition().getX() << "," << getPosition().getY()<< ")" <<endl;

                        int x1 = termshape->getX1() + x;                 // On additionne la position de l'instance
                        int y1 = termshape->getY1() + y;                 // et la position du termshape
                        termInst->setPosition(x1, y1);                   // et résultat dans le term concerné de l'instance
                        
                        //Affichage de contrôle.
                        cout << "Nouvelle position du term_("  << name  << ") : ("         // On affiche pour contrôler
                             << termInst->getPosition().getX() << ","   << termInst->getPosition().getY() << ")"
                             << "\n--------------------\n"     << endl;
                    }
                }
            }
        }
    }

    


} // Fin namespace NetList