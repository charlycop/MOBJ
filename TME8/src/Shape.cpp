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

    /*
    *
    * CTOR et DTOR
    * 
    */

    Shape::Shape (Symbol* s) : symbol_(s)
    { symbol_->add(this); }

    Shape::~Shape(){}

    BoxShape::BoxShape (Symbol* s, Box b): Shape(s), box_(b)
    {}

    LineShape::LineShape  (Symbol* s, long x1, long y1, long x2, long y2 ):
    Shape(s), x1_(x1), x2_(x2), y1_(y1), y2_(y2)
    {}

    TermShape::TermShape  (Symbol* s, string name, long x, long y, NameAlign align):
    Shape(s), term_(NULL), x1_(x), y1_(y), align_(align)
    {
        Cell* cell = getSymbol()->getCell();
        term_      = cell->getTerm(name);
    }
    /*
     TermShape::TermShape  (Symbol* s, string name, NameAlign align):
    Shape(s), term_(NULL), align_(align)
    {
        Cell* cell = getSymbol()->getCell();
        term_      = cell->getTerm(name);
        x1_        = term_->getPosition().getX();
        y1_        = term_->getPosition().getY();
    }*/

    ArcShape::ArcShape( Symbol* s, long start, long span, long x1, long y1, long x2, long y2):
    Shape(s), box_(Box(x1,y1,x2,y2)), start_(start), span_(span)
    {}

    EllipseShape::EllipseShape ( Symbol* s, long x1, long y1, long x2, long y2):
    Shape(s), box_(Box(x1,y1,x2,y2))
    {}

    /*
    *
    * GETBOUNDING BOX
    * 
    */

    Box     BoxShape::getBoundingBox() const{
        Box t;
        return t;
    }

    Box     LineShape::getBoundingBox() const{
        Box t;
        return t;
    }

    Box     TermShape::getBoundingBox() const{
        Box t;
        return t;
    }

    Box     ArcShape::getBoundingBox() const{
        Box t;
        return t;
    }

    Box     EllipseShape::getBoundingBox() const{
        Box t;
        return t;
    }


    /*
    *
    * FROM XML
    * 
    */

    Shape*  LineShape::fromXml        ( Symbol* owner, xmlTextReaderPtr reader){
        
        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "line"){
            int x1, x2, y1, y2;
            xmlGetIntAttribute( reader, "x1", x1 );
            xmlGetIntAttribute( reader, "x2", x2 );  
            xmlGetIntAttribute( reader, "y1", y1 );
            xmlGetIntAttribute( reader, "y2", y2 );         

            return new LineShape(owner, x1, y1, x2, y2);
        }
        cerr << "[ERROR] Problem inside LineShape::fromXml" << endl;
        return nullptr;
    }

    Shape*  EllipseShape::fromXml     ( Symbol* owner, xmlTextReaderPtr reader){

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "ellipse"){
            int x1, x2, y1, y2;
            xmlGetIntAttribute( reader, "x1"   , x1 );
            xmlGetIntAttribute( reader, "y1"   , y1 ); 
            xmlGetIntAttribute( reader, "x2"   , x2 );
            xmlGetIntAttribute( reader, "y2"   , y2 );

            return new EllipseShape(owner, x1, y1, x2, y2);
        }
        cerr << "[ERROR] Problem inside EllipseShape::fromXml" << endl;
        return nullptr;
    }

    Shape*  ArcShape::fromXml ( Symbol* owner, xmlTextReaderPtr reader){
       
        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "arc"){
            int x1, x2, y1, y2, span, start;
            xmlGetIntAttribute( reader, "x1"   , x1 );
            xmlGetIntAttribute( reader, "y1"   , y1 ); 
            xmlGetIntAttribute( reader, "x2"   , x2 );
            xmlGetIntAttribute( reader, "y2"   , y2 );
            xmlGetIntAttribute( reader, "span" , span );
            xmlGetIntAttribute( reader, "start", start );

            return new ArcShape(owner, start, span, x1, y1, x2, y2);
        }
        cerr << "[ERROR] Problem inside ArcShape::fromXml" << endl;
        return nullptr;
    }

    Shape*  BoxShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){

        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "box"){

            int x1, x2, y1, y2;
            xmlGetIntAttribute( reader, "x1", x1 );
            xmlGetIntAttribute( reader, "x2", x2 );  
            xmlGetIntAttribute( reader, "y1", y1 );
            xmlGetIntAttribute( reader, "y2", y2 );            

            return new BoxShape(owner, Box(x1, y1, x2, y2));
        }
        cerr << "[ERROR] Problem inside BoxShape::fromXml" << endl;
        return nullptr;
    }

    Shape*  TermShape::fromXml        ( Symbol* owner, xmlTextReaderPtr reader){
        if (xmlCharToString(xmlTextReaderLocalName(reader)) == "term"){
        
            string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));

            if (not name.empty()){
                int x1, y1;
                NameAlign align = toNameAlign(xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"align")));
                xmlGetIntAttribute( reader, "x1", x1 );
                xmlGetIntAttribute( reader, "y1", y1 );            

                return new TermShape(owner, name,x1, y1, align);
            }
        }    
        cerr << "[ERROR] Problem inside TermShape::fromXml" << endl;
        return nullptr;
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

    /*
    *
    * TO XML
    * 
    */

    void   LineShape::toXml        ( std::ostream& stream ){
        stream << ++indent 
               << "<line x1=\"" << getX1()
               << "\" y1=\""    << getY1()
               << "\" x2=\""    << getX2()
               << "\" y2=\""    << getY2()
               << "\"/>\n";
        --indent;
    }

    void    BoxShape::toXml ( std::ostream& stream ){
        stream << ++indent
               << "<box x1=\"" << getBox().getX1()
               << "\" y1=\""   << getBox().getY1() 
               << "x2=\""      << getBox().getX2() 
               << "\" y2=\""   << getBox().getY2() 
               << "\"/>\n";
        --indent;
    }


    void    TermShape::toXml ( std::ostream& stream ){
        stream << ++indent
               <<"<term name=\""  << getTerm()->getName()
               <<"\" x1=\""       << getX1()
               << "\" y1=\""      << getY1()
               << "\" align=\""   << TermShape::toString(getAlign())
               <<"\"/>\n";
        --indent;
    }

    void    ArcShape::toXml ( std::ostream& stream ){
        stream << ++indent 
               << "<arc x1=\"" << getBox().getX1()
               << "\" y1=\""   << getBox().getY1() 
               << " x2=\""     << getBox().getX2() 
               << "\" y2=\""   << getBox().getY2() 
               << "\" start=\""<< getStart()
               << "\" span=\"" << getSpan()
               <<"\"/>\n";
        --indent;
    }

    void    EllipseShape::toXml ( std::ostream& stream ){
        stream << ++indent
               << "<ellipse x1=\"" << getBox().getX1()
               << "\" y1=\""       << getBox().getY1() 
               << "x2=\""          << getBox().getX2() 
               << "\" y2=\""       << getBox().getY2() 
               << "\"/>\n";
        --indent;
    }

    std::string  TermShape::toString   ( NameAlign name ){
       switch(name){
          case top_left      : return "top_left";
          case top_right     : return "top_right";
          case bottom_left   : return "bottom_left";
          case bottom_right  : return "bottom_right";
          default            : return "Unknown";
        }
    }

    TermShape::NameAlign    TermShape::toNameAlign ( std::string align ){
        if      (align == "top_left")       return top_left;
        else if (align == "top_right")      return top_right;
        else if (align == "bottom_left")    return bottom_left;
        
        return bottom_right;
    }

}  // Netlist namespace.