#include <iostream>
#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"
#include "Line.h"

using namespace std;

namespace Netlist{


    const size_t  Net::noid = numeric_limits<size_t>::max();

    void  Net::toXml ( std::ostream& stream){
        
        //Le Net
        stream << indent++ << "<net name=\"" << getName() << "\" type=\"" << Term::toString(getType()) << "\">\n";
        
        // Les nodes
        for(auto& node : getNodes()) {
            if (node != nullptr)
                node->toXml(stream);
        }

        // Les Lines
        for(auto& line : getLines()) {
            if (line != nullptr)
                line->toXml(stream);
        }

        stream << --indent << "</net>\n" ;
    }

    Net* Net::fromXml(Cell* cell, xmlTextReaderPtr reader){

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "net"){ // Les Nets

            string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            string type = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"type"));
            
            if (cell->getNets().size() && cell->getNets().back()->getName() == name) 
                return cell->getNets().back();

            if(not name.empty() && not type.empty())
                return new Net(cell, name, Term::toType(type));
        }
      
        else if (xmlCharToString(xmlTextReaderLocalName(reader)) == "node"){ //Les Nodes
            Net* lastNet     = cell->getNets().back();

            if(Node::fromXml(lastNet, reader))
                return lastNet;
        }

        else if (xmlCharToString(xmlTextReaderLocalName(reader)) == "line"){ //Les Lines
            Net* lastNet     = cell->getNets().back();

            if(Line::fromXml(lastNet, reader))
                return lastNet;
        }
  
        cerr << "[ERROR] Problem inside Net::fromXml" << endl;
        return nullptr;
    }
    
    bool  Net::remove ( Line* line ){
      if (line) {
        for ( vector<Line*>::iterator il = lines_.begin()
            ; il != lines_.end() ; ++il ) {
          if (*il == line) {
            lines_.erase( il );
            return true;
          }
        }
      }
      return false;
    }

    Net::Net     ( Cell* owner, const std::string& name, Term::Type type):
    owner_(owner), name_(name), id_(owner->Cell::newNetId ()), type_(type){

        owner_ -> add(this);
    }

    Net::~Net(){}

    void Net::add (Node* n){ 

        if(not n) return;

        size_t id = n->getId();

        // SI le ID est vide (pas forcé par le fromXML par exemple)
        if(id==Node::noid){
            id = getFreeNodeId();
            n -> setId(id);
        }

        //Si il a été forcé par le fromXML
        if(id < nodes_.size()){

            if(nodes_[id] != nullptr){
                cerr << "[ERROR]" << endl;
                nodes_[id]->setId(Node::noid);
                return;
            }
            nodes_[id] = n;

        }else{
            for(size_t i = nodes_.size(); i<id; ++i){
                nodes_.push_back(nullptr);
            }
            nodes_.push_back(n);
        }
    }

    bool  Net::remove ( Node* n){
        for (auto node : nodes_){
            if (n == node) node = NULL;
            return true;
        }
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