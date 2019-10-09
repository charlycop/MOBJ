#include "Box.h"

int tme2::Box::count_=0;
int tme2Qf::Box::countQf_=0;

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


/////////////////////////////////////

/////////////////////////////////////

namespace tme2Qf{

    //Fonctions Classe BOX
    Box::Box(){
        makeEmpty();
        if(debug) std::cout << "Debug: Box::Box() <" << name_ << " [" << getX1() << " "<< getY1() << " " << getX2() << " " << getY2() << "]>"<< std::endl;
        ++countQf_;
    }

    Box::Box(const std::string name, long x1, long y1, long x2, long y2){
        width_ = x2-x1; 
        height_= y2-y1;
        x_     = (width_  / 2.0) + x1;
        y_     = (height_ / 2.0) + y1;
        name_  = name;
        ++countQf_;
        if(debug) std::cout << "Debug: Box::Box(std::string, ...) <" << name_ << " [" << getX1() << " "<< getY1() << " " << getX2() << " " << getY2() << "]>"<< std::endl;
    }

    Box::Box(const Box& boxacopier) {
        x_       = boxacopier.x_;
        y_       = boxacopier.y_;
        width_   = boxacopier.width_;
        height_  = boxacopier.height_;
        name_    = boxacopier.name_;
        ++countQf_;
        if(debug) std::cerr << "Debug: Box::Box(const Box&) <" << name_ << " [" << getX1() << " "<< getY1() << " " << getX2() << " " << getY2() << "]>"<< std::endl;
    }

    Box::~Box(){
        --countQf_;
        if(debug) std::cout << "Debug: Box::~Box() <" << name_ << " [" << getX1() << " "<< getY1() << " " << getX2() << " " << getY2() << "]>"<< std::endl;
    }
    
    bool Box::intersect(const Box& b) const{
        if (isEmpty() || b.isEmpty()) return false;
        if (   ((getX2() <= b.getX1()) && (getY1() <= b.getY2()))
            || ((getX1() >= b.getX2()) && (getY2() >= b.getY1())))
            return false;
        
        return true;
    }

    void Box::print(std::ostream & os) const{
         os << name_ << "<" << getX1() << " "<< getY1() << " " << getX2() << " " << getY2() << ">" << std::endl;
    } 

    void Box::makeEmpty(){
        x_ = 0;
        y_ = 0;
        height_ = 0;
        width_ = 0;
        name_ = "Unknown";
    }

    void Box::inflate(long dxy){
        width_ += (dxy*2); 
        height_+= (dxy*2);
    }

    void Box::inflate(long dx, long dy){
        width_ += (dx*2);
        height_+= (dy*2);
    }

    void Box::inflate(long dx1, long dy1, long dx2, long dy2){

        long x1 = getX1() - dx1;
        long y1 = getY1() - dy1;
        long x2 = getX2() + dx2;
        long y2 = getY2() + dy2;

        // On utilise comme le constructeur
        width_ = x2-x1; 
        height_= y2-y1;
        x_     = (width_  / 2.0) + x1;
        y_     = (height_ / 2.0) + y1;
    }

    Box Box::getIntersection(const Box& box2) const{
        
        long x1, x2, y1, y2;
        std::string name;

        if (intersect(box2)){
            name     = name_+"."+box2.name_;
            x1 = std::max( getX1(), box2.getX1() );
            y1 = std::max( getY1(), box2.getY1() );
            x2 = std::min( getX2(), box2.getX2() );
            y2 = std::min( getY2(), box2.getY2() );
        }

        Box intersection(name, x1, y1, x2, y2);

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

}//Fin namespace tme2QF