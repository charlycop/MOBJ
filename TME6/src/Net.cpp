#include <iostream>
#include  <limits>
#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"
#include <ctime>

namespace Netlist{
    using namespace std;

    const size_t  Net::noid = numeric_limits<size_t>::max();

    void  Net::toXml ( std::ostream& stream){
        stream << indent++ << "<net name=\"" << getName() << "\" type=\"" << Term::toString(getType()) << "\"/>\n";
        for(auto node : getNodes()) 
            node->toXml(stream);
        stream << --indent << "</net>\n" ;
    }

    Net* Net::fromXml(Cell* cell, xmlTextReaderPtr reader){

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "net"){

            string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            string type = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"type"));
            
            if (cell->getNets().size() && cell->getNets().back()->getName() == name) 
                return cell->getNets().back();

            if(not name.empty() && not type.empty())
                return new Net(cell, name, Term::toType(type));
        }
      
        else if (xmlCharToString(xmlTextReaderLocalName(reader)) == "node"){
            Net* lastNet     = cell->getNets().back();

            if(Node::fromXml(lastNet, reader))
                return lastNet;

            /*string  term     = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"term"));
            string  instance = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"instance"));
            string  id       = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"id"));
            Net* lastNet     = cell->getNets().back();
            
            if (not instance.empty()){
                Instance* instancePtr = cell->getInstance(instance);
                instancePtr->connect(term, lastNet);
            }
            else
                cell->connect(term, lastNet);

            return lastNet;
            */
        }
  
        return nullptr;
    }

    Net::Net     ( Cell* owner, const std::string& name, Term::Type type):
    owner_(owner), name_(name), id_(owner->Cell::newNetId ()), type_(type){

        owner_ -> add(this);
    }

    Net::~Net(){}

    void Net::add (Node* n){ 
        size_t freeNode = getFreeNodeId();

        if(freeNode >= nodes_.size())
            nodes_.push_back(n);
        else
            nodes_[freeNode] = n;
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
            if (node == NULL)
                return freeNode;
            ++freeNode;
        }

        return freeNode;
    }


}