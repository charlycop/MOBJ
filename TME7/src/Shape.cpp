#include <iostream>
#include <string>
#include "Node.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "Indentation.h"
#include "Shape.h"
#include "XmlUtil.h"

using namespace std;

namespace Netlist{

Shape::Shape (Symbol* s) : symbol_(s)
{ symbol_->add(this); }

Shape::~Shape(){}

BoxShape::BoxShape (Symbol* s, Box b): Shape(s), box_(b)
{}

LineShape::LineShape  (Symbol* s, long x1, long y1, long x2, long y2 ):
Shape(s), x1_(x1), x2_(x2), y1_(y1), y2_(y2)
{}

Shape*  LineShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
    Shape* s=nullptr;
    return s;
}

void   LineShape::toXml        ( std::ostream& stream ){
    stream << "<line x1=\"" << getX1()
           << "\" y1=\"" << getY1()
           << "x2=\"" << getX2()
           << "\" y2=\""<< getY2()
           << "\"/>\n";
}

Shape*  EllipseShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
    Shape* s=nullptr;
    return s;
}

Shape*  BoxShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
    Shape* s=nullptr;
    return s;
}

void    BoxShape::toXml ( std::ostream& stream ){
    stream << "<box x1=\"" << getBox().getX1()
           << "\" y1=\"" << getBox().getY1() 
           << "x2=\"" << getBox().getX2() 
           << "\" y2=\""<< getBox().getY2() 
           << "\"/>\n";
}

Shape*  ArcShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
    Shape* s=nullptr;
    return s;
}

Shape*  TermShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
    Shape* s=nullptr;
    return s;
}

TermShape::TermShape  (Symbol* s, string name, long x, long y):
Shape(s), term_(NULL), x1_(x), y1_(y)
{
    Cell* cell = getSymbol()->getCell();
    term_      = cell->getTerm(name);
}

Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader ) {
// Factory-like method.
  const xmlChar* boxTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
  const xmlChar* ellipseTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
  const xmlChar* arcTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
  const xmlChar* lineTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
  const xmlChar* termTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
  const xmlChar* nodeName
      = xmlTextReaderConstLocalName( reader );

  Shape* shape = NULL;
  if (boxTag == nodeName)
    shape = BoxShape::fromXml( owner, reader );
  if (ellipseTag == nodeName)
    shape = EllipseShape::fromXml( owner, reader );
  if (arcTag == nodeName)
    shape = ArcShape::fromXml( owner, reader );
  if (lineTag == nodeName)
    shape = LineShape::fromXml( owner, reader );
  if (termTag == nodeName)
    shape = TermShape::fromXml( owner, reader );

  if (shape == NULL)
    cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
         << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;

  return shape;
}



}  // Netlist namespace.


