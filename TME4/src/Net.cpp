#include <iostream>
#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist{

    Net::Net     ( Cell* owner, const std::string& name, Term::Type type):
    owner_(owner), name_(name), id_(owner->Cell::newNetId ()), type_(type){

        owner_ -> add(this);

    }
    Net::~Net(){}

    void Net::add (Node* n){ 
        size_t freeNode = getFreeNodeId();

        if(freeNode == nodes_.size()-1) nodes_.push_back(n);
        else                            nodes_[freeNode] = n;
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
            if (node == NULL) return freeNode;
            ++freeNode;
        }

        return freeNode;
    }


}