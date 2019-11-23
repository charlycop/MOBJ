// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"
#include "XmlUtil.h"

namespace Netlist {

  using namespace std;


  const size_t  Node::noid = numeric_limits<size_t>::max();

  void  Node::toXml ( std::ostream& stream){
     if (getTerm()->isExternal())
          stream << indent << "<node term=\"" << getTerm()->getName() <<"\" id=\""<< getId() << "\" x=\"" <<getPosition().getX() << "\" y=\"" << getPosition().getY() << "\"/>\n";
     else stream << indent << "<node term=\"" << getTerm()->getName() << "\" instance=\"" << getTerm()->getInstance()->getName() <<"\" id=\""<< getId() << "\" x=\"" << getPosition().getX() << "\" y=\"" << getPosition().getY() << "\"/>\n";
  }

  bool  Node::fromXml(Net* net, xmlTextReaderPtr reader){
      string  term     = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"term"));
      string  instance = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"instance"));
      string  id       = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"id"));

      if(not term.empty() && not id.empty()){
          if (not instance.empty()){
              Instance* instancePtr = net->getCell()->getInstance(instance);
              instancePtr->connect(term, net);
          }
          else
            net->getCell()->connect(term, net);
      }else
        return false;

      return true;
  }

  Node::Node ( Term* term, size_t id ): id_(id), term_(term), position_(){}


  Node::~Node ()
  {
    //if (getNet()) getNet()->remove( this );
  }

  inline Net* Node::getNet () const { return term_->getNet(); }

}  // Netlist namespace.
