#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist{

    Net::~Net(){}
    const std::vector<Node*>& Net::getNodes      () const{ return nodes_; }
    const std::string&        Net::getName       () const{ return name_;  }
}