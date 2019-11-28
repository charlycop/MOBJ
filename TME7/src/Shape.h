#ifndef  NETLIST_SHAPE_H
#define  NETLIST_SHAPE_H

#include <vector>
#include <limits>
#include "Symbol.h"
#include "Box.h"

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
            Box     getBoundingBox  () const;
            void    toXml        ( std::ostream& stream );

    static Shape*   fromXml     ( Symbol* owner, xmlTextReaderPtr reader);

    inline Box      getBox      ();

    private:
        Box    box_;
}; // Fin class Boxshape

    //Fonction BoxShape
    inline Box     BoxShape::getBox      () { return box_; };

class LineShape : public Shape{
    public:
                    LineShape     ( Symbol*, long x1, long y1, long x2, long y2 );
                   ~LineShape     ();
            Box     getBoundingBox() const;
            void    toXml         ( std::ostream& stream );
     static Shape*  fromXml       ( Symbol* owner, xmlTextReaderPtr reader);

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
    

    public:
        enum NameAlign { TopLeft=1, TopRight=2, BottomLeft=3, BottomRight=4 };

                      TermShape     ( Symbol* s, std::string name, long x1, long y1, NameAlign align);
                     ~TermShape     ();
            Box       getBoundingBox() const;
    static  Shape*    fromXml       ( Symbol* owner, xmlTextReaderPtr reader);
            void      toXml         ( std::ostream& stream );

    static  std::string  toString    ( NameAlign name ){
           switch(name){
              case TopLeft      : return "TopLeft";
              case TopRight     : return "TopRight";
              case BottomLeft   : return "BottomLeft";
              case BottomRight  : return "BottomRight";
              default           : return "Unknown";
            }
    }

    static NameAlign    toNameAlign ( std::string align){
            if      (align == "TopLeft")       return TopLeft;
            else if (align == "TopRight")      return TopRight;
            else if (align == "BottomLeft")    return BottomLeft;
            else if (align == "BottomRight")   return BottomRight;
        }

    inline  long      getX1        ();
    inline  long      getY1        ();
    inline  Term*     getTerm      ();
    inline  NameAlign getAlign     ();

    private:
        Term* term_;
        long  x1_, y1_;
        NameAlign align_;

}; // Fin class Termshape

    // Pour la classe TermShape
    inline long      TermShape::getX1       () { return x1_;   }
    inline long      TermShape::getY1       () { return y1_;   }
    inline Term*     TermShape::getTerm     () { return term_; }
    inline TermShape::NameAlign TermShape::getAlign    () { return align_;}
    
class EllipseShape : public Shape{
    public:
                    EllipseShape     ( Symbol* s, std::string name, long x, long y);
                   ~EllipseShape     ();
    static Shape*   fromXml         ( Symbol* owner, xmlTextReaderPtr reader);


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