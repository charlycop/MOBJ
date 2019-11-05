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
    //<node term="a" id="0" x="0" y="0"/>
    //<node term="i1" instance="xor2_1" id="1" x="0" y="0"/>
     if (getTerm()->isExternal())
          stream << indent << "<node term=\"" << getTerm()->getName() <<"\" id=\""<< getId() << "\" x=\"" <<getPosition().getX() << "\" y=\"" << getPosition().getY() << "\"/>\n";
     else stream << indent << "<node term=\"" << getTerm()->getName() << "\" instance=\"" << getTerm()->getInstance()->getName() <<"\" id=\""<< getId() << "\" x=\"" << getPosition().getX() << "\" y=\"" << getPosition().getY() << "\"/>\n";

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

}  // Netlist namespace.
