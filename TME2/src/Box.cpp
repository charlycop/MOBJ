#include "Box.h"

int tme2::Box::count_=0;

namespace tme2{

    //Fonctions Classe BOX
    Box::Box(){
        makeEmpty();
        if(debug) std::cout << "Debug: Box::Box() <" << name_ << " [" << x1_ << " " << y1_ << " " << x2_ << " " << y2_ << "]>"<< std::endl;
        ++count_;
    }

    Box::Box(const std::string name, long x1, long y1, long x2, long y2){
        x1_   = x1;
        x2_   = x2;
        y1_   = y1;
        y2_   = y2;
        name_ = name;
        ++count_;
        if(debug) std::cout << "Debug: Box::Box(std::string, ...) <" << name_ << " [" << x1_ << " " << y1_ << " " << x2_ << " " << y2_ << "]>"<< std::endl;
    }

    Box::Box(const Box& boxacopier) {
        x1_   = boxacopier.x1_;
        x2_   = boxacopier.x2_;
        y1_   = boxacopier.y1_;
        y2_   = boxacopier.y2_;
        name_ = boxacopier.name_;
        ++count_;
        if(debug) std::cerr << "Debug: Box::Box(const Box&) <" << name_ << " [" << x1_ << " " << y1_ << " " << x2_ << " " << y2_ << "]>"<< std::endl;
    }

    Box::~Box(){
        --count_;
        if(debug) std::cout << "Debug: Box::~Box() <" << name_ << " [" << x1_ << " " << y1_ << " " << x2_ << " " << y2_ << "]>"<< std::endl;
    }
    
    bool Box::intersect(const Box& b) const{
        if (isEmpty() || b.isEmpty()) return false;
        if (   ((x2_ <= b.x1_) && (y1_ <= b.y2_))
            || ((x1_ >= b.x2_) && (y2_ >= b.y1_)))
            return false;
        
        return true;
    }

    void Box::print(std::ostream & os) const{
         os << name_ << "<" << x1_ << " "<< y1_ << " " << x2_ << " " << y2_ << ">" << std::endl;
    } 

    void Box::makeEmpty(){
        x1_ = 1;
        x2_ = -1;
        y1_ = 1;
        y2_ = -1;
        name_ = "Unknown";
    }

    void Box::inflate(long dxy){
        x1_ -= dxy;
        y1_ -= dxy;
        x2_ += dxy;
        y2_ += dxy;
    }

    void Box::inflate(long dx, long dy){
        x1_ -= dx;
        y1_ -= dy;
        x2_ += dx;
        y2_ += dy;        
    }

    void Box::inflate(long dx1, long dy1, long dx2, long dy2){
        x1_ -= dx1;
        y1_ -= dy1;
        x2_ += dx2;
        y2_ += dy2;
    }

    Box Box::getIntersection(const Box& box2) const{
        Box intersection;

        if (intersect(box2)){
            intersection.name_ = name_+"."+box2.name_;
            intersection.x1_ = std::max( x1_, box2.x1_ );
            intersection.y1_ = std::max( y1_, box2.y1_ );
            intersection.x2_ = std::min( x2_, box2.x2_ );
            intersection.y2_ = std::min( y2_, box2.y2_ );
        }

        return intersection;
    }

    //Surcharges
    std::ostream& operator<<(std::ostream &flux, Box const& box){
        box.print(flux);
        return flux;
    }

    Box Box::operator&&(const Box& box){
        return getIntersection(box);
    }

}// Fin namespace tme2