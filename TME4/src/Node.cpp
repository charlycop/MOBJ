// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"

namespace Netlist {

  using namespace std;


  const size_t  Node::noid = numeric_limits<size_t>::max();

  void  Node::toXml ( std::ostream& stream){
     stream << indent << "ID DU NODE : "<< getId() << "\n";
  }

  Node::Node ( Term* term, size_t id )
    : id_      (id)
    , term_    (term)
    , position_()
  { }


  Node::~Node ()
  {
    //if (getNet()) getNet()->remove( this );
  }


  inline Net* Node::getNet () const { return term_->getNet(); }


// Node::toXml() à écrire ici.


}  // Netlist namespace.
