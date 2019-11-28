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

    /*
    *
    * FROM XML
    * 
    */

    Shape*  LineShape::fromXml        ( Symbol* owner, xmlTextReaderPtr reader){
        
        string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"line"));

        if (name == "line"){
            int x1 = -1;
            int x2 = -1;
            int y1 = -1;
            int y2 = -1;
            xmlGetIntAttribute( reader, "x1", x1 );
            xmlGetIntAttribute( reader, "x2", x2 );  
            xmlGetIntAttribute( reader, "y1", y1 );
            xmlGetIntAttribute( reader, "y2", y2 );            

            if(y1 < 0 || y2 < 0 || x1 < 0 || x2 < 0){
                cerr << "[ERROR] Coordinates not valid for on line of the symbol of the Cell : " << owner->getCell()->getName() << endl;
                return nullptr;
            }
             
            return new LineShape(owner, x1, y1, x2, y2);
        }
        cerr << "[ERROR] Coordinates not valid for on line of the symbol" << endl;
        return nullptr;
    }

    Shape*  EllipseShape::fromXml     ( Symbol* owner, xmlTextReaderPtr reader){
        Shape* s=nullptr;
        return s;
    }

    Shape*  BoxShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
        string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"box"));

        if (name == "box"){
            int x1 = -1;
            int x2 = -1;
            int y1 = -1;
            int y2 = -1;
            xmlGetIntAttribute( reader, "x1", x1 );
            xmlGetIntAttribute( reader, "x2", x2 );  
            xmlGetIntAttribute( reader, "y1", y1 );
            xmlGetIntAttribute( reader, "y2", y2 );            

            if(y1 < 0 || y2 < 0 || x1 < 0 || x2 < 0){
                cerr << "[ERROR] Coordinates not valid for on box of the symbol of the Cell : " << owner->getCell()->getName() << endl;
                return nullptr;
            }
            Box newBox(x1, y1, x2, y2);
            return new BoxShape(owner, newBox);
        }
        cerr << "[ERROR] Coordinates not valid for on line of the symbol" << endl;
        return nullptr;
    }

    Shape*  ArcShape::fromXml         ( Symbol* owner, xmlTextReaderPtr reader){
        Shape* s=nullptr;
        return s;
    }

    Shape*  TermShape::fromXml        ( Symbol* owner, xmlTextReaderPtr reader){
        string term = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"term"));

        if (term == "term"){
            int x1 = -1;
            int y1 = -1;
            TermShape::NameAlign align = toNameAlign(xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"align")));
            xmlGetIntAttribute( reader, "x1", x1 );
            xmlGetIntAttribute( reader, "y1", y1 );            

            if(y1 < 0 || x1 < 0){
                cerr << "[ERROR] Coordinates not valid for on box of the symbol of the Cell : " << owner->getCell()->getName() << endl;
                return nullptr;
            }

            string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
            if(not name.empty())
                return new TermShape(owner, name, x1, y1, align);
        }
        cerr << "[ERROR] Coordinates not valid for on line of the symbol" << endl;
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
        stream << "<line x1=\"" << getX1()
               << "\" y1=\""    << getY1()
               << "x2=\""       << getX2()
               << "\" y2=\""    << getY2()
               << "\"/>\n";
    }

    void    BoxShape::toXml ( std::ostream& stream ){
        stream << "<box x1=\"" << getBox().getX1()
               << "\" y1=\""   << getBox().getY1() 
               << "x2=\""      << getBox().getX2() 
               << "\" y2=\""   << getBox().getY2() 
               << "\"/>\n";
    }


    void    TermShape::toXml ( std::ostream& stream ){
        stream << "<term name=\"" << getTerm()->getName()
               <<"\" x1=\""       << getX1()
               << "\" y1=\""      << getY1()
               << "\" align=\""   << TermShape::toString(getAlign())
               <<"\"/>\n";
    }

}  // Netlist namespace.