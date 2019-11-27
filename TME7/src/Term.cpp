#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"
#include "XmlUtil.h"

using namespace std;

namespace Netlist {

    void  Term::toXml ( std::ostream& stream){
        stream << indent <<"<term name=\"" << getName() << "\" direction=\"" << Term::toString(getDirection()) << "\" x=\"" << getPosition().getX() << "\" y=\"" << getPosition().getY() << "\"/>\n";
    }

    Term* Term::fromXml(Cell* cell, xmlTextReaderPtr reader){

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "term"){
           
            string         name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            string    direction = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"direction"));
            string            x = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x"));
            string            y = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y"));

            if(not name.empty() && not direction.empty()){
                Term* newTerm = new Term(cell, name, toDirection(direction));
                newTerm->setPosition(atoi(x.c_str()), atoi(y.c_str()));
                return newTerm;
            }
        }

        return nullptr;
    }

    Term::Term ( Cell* owner , const std::string& name, Direction direction): 
    owner_(owner), name_(name),direction_(direction),type_(External),net_(NULL), node_(this) {
        static_cast<Cell*>(owner_) -> add(this);
    }

    Term::Term ( Instance* owner, const Term* modelTerm ):
    owner_(owner), 
    name_(modelTerm->getName()),
    direction_(modelTerm->getDirection()),
    type_(Internal),
    net_(modelTerm->getNet()),
    node_(this)
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
        Node* n = getNode();
        newNet->add(n);
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
