#include <iostream>
#include  <limits>
#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

namespace Netlist{
    using namespace std;

    const size_t  Net::noid = numeric_limits<size_t>::max();

    void  Net::toXml ( std::ostream& stream){
        stream << indent++ << "<net name=\"" << getName() << "\" type=\"" << Term::toString(getType()) << "\"/>\n";
        for(auto node : getNodes()) 
            node->toXml(stream);
        --indent;
    }

    Net* Net::fromXml(Cell* cell, xmlTextReaderPtr reader){
        Net* newNet  = nullptr;
        Net* newNode = nullptr;

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "net"){ // Si j'ai bien une instance

            string         name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            string         type = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"type"));
            
            newNet = new Net(cell, name, Term::toType(type));          
        }

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "node"){
            string         name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            string         type = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"instance"));
            string         id   = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"id"));

            Node ( cell->getTerm(), atoi(id.c_str()));
        }

        return newNet;
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