#ifndef  NETLIST_SHAPE_H
#define  NETLIST_SHAPE_H

#include <vector>
#include <limits>
#include "Symbol.h"

namespace Netlist{
class Symbol;
class Shape{

    public:
                    Shape                      (Symbol*);
                    ~Shape                      ();
    inline  Symbol* getSymbol       () const;
    virtual Box     getBoundingBox  () const = 0 ;
    static Shape*   fromXml         ( Symbol* owner, xmlTextReaderPtr reader);

    private:
        Symbol* symbol_;

}; // Fin class Shape

    //Fonction de Shape
    inline Symbol* Shape::getSymbol() const{ return symbol_; }


class BoxShape : public Shape{
    public:
                    BoxShape    (Symbol*, Box);
                   ~BoxShape    ();
    static Shape*  fromXml         ( Symbol* owner, xmlTextReaderPtr reader);

    private:
        Box     box_;
}; // Fin class Boxshape


class LineShape : public Shape{
    public:
                    LineShape     ( Symbol*, long x1, long y1, long x2, long y2 );
                   ~LineShape     ();
     static Shape*  fromXml         ( Symbol* owner, xmlTextReaderPtr reader);

    inline  long    getX1         ();
    inline  long    getX2         ();
    inline  long    getY1         ();
    inline  long    getY2         ();

    private:
        long x1_, x2_, y1_, y2_;

}; // Fin class Lineshape

    // Pour la classe LineShape
    inline long LineShape::getX1       () { return x1_; }
    inline long LineShape::getY1       () { return y1_; }
    inline long LineShape::getX2       () { return x2_; }
    inline long LineShape::getY2       () { return y2_; }

class TermShape : public Shape{
    enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };

    public:
                    TermShape     ( Symbol* s, std::string name, long x1, long y1);
                   ~TermShape     ();
    static Shape*  fromXml         ( Symbol* owner, xmlTextReaderPtr reader);
    
    inline  long    getX1        ();
    inline  long    getY1        ();
    inline  Term*   getTerm      ();

    private:
        Term* term_;
        long  x1_, y1_;
        NameAlign align_;

}; // Fin class Termshape

    // Pour la classe TermShape
    inline long  TermShape::getX1       () { return x1_; }
    inline long  TermShape::getY1       () { return y1_; }
    inline Term* TermShape::getTerm     () {return term_;}
    
class EllipseShape : public Shape{
    public:
                    EllipseShape     ( Symbol* s, std::string name, long x, long y);
                   ~EllipseShape     ();
    static Shape*  fromXml         ( Symbol* owner, xmlTextReaderPtr reader);


    private:
       Box     box_;
}; // Fin EllipseShape

class ArcShape : public Shape{
    public:
                    ArcShape     ( Symbol* s, long start_, long span_);
                   ~ArcShape     ();
    static Shape*  fromXml      ( Symbol* owner, xmlTextReaderPtr reader);


    private:
       Box     box_;
       long    start_, span_;
}; // Fin ArcShape


}  // Netlist namespace.

#endif  // NETLIST_SHAPE_H