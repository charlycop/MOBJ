#pragma once

#include <iostream>
#include <string>
#include <algorithm>    // std::max

extern bool debug;

namespace tme2{

class Box{
    
    private :
           std::string     name_;
           long            x1_, x2_, y1_, y2_;
    static int             count_;


    public :
    // Constructeurs
    Box         ();                                                           // constructeur par défaut.
    Box         (const std::string name, long x1, long y1, long x2, long y2); // constructeur ordinaire.
    Box         (const  Box&);                                                // par copie;
    
    //Destructeur
    ~Box        ();                                                       

    //Accesseurs
    inline        std::string getName             () const;
    inline        long        getX1               () const;
    inline        long        getY1               () const;
    inline        long        getX2               () const;
    inline        long        getY2               () const;
    inline        bool        isEmpty             () const;
    inline        long        getWidth            () const;
    inline        long        getHeight           () const;
    inline static int         getAllocateds       ();
                  void        print               (std::ostream&) const;


    //Modificateurs
    void        makeEmpty           ();
    void        inflate             (long dxy);
    void        inflate             (long dx, long dy);
    void        inflate             (long dx1, long dy1, long dx2, long dy2);
    bool        intersect           (const Box&) const;
    Box         getIntersection     (const Box&) const;

    //Surcharges
    friend std::ostream& operator<<(std::ostream& flux, Box const &box);
    Box operator&&(const Box&);
};

    //Fonctions inline
    inline int Box::getAllocateds()        { return count_; }
    inline std::string Box::getName() const{ return name_;  }
    inline long Box::getX1()          const{ return x1_;    }
    inline long Box::getY1()          const{ return y1_;    }
    inline long Box::getX2()          const{ return x2_;    }
    inline long Box::getY2()          const{ return y2_;    }
    inline bool Box::isEmpty()        const{ return ((x1_ > x2_) || (y1_ > y2_)); }
    inline long Box::getWidth()       const{ return isEmpty() ? 0 : (x2_-x1_);    }
    inline long Box::getHeight()      const{ return isEmpty() ? 0 : (y2_-y1_);    }
    
}

namespace tme2Qf{

class Box{
    
    private :
           std::string     name_;
           long            x_, y_, width_, height_;
    static int             countQf_;


    public :
    // Constructeurs
    Box         ();                                                           // constructeur par défaut.
    Box         (const std::string name, long x1, long y1, long x2, long y2); // constructeur ordinaire.
    Box         (const  Box&);                                                // par copie;
    
    //Destructeur
    ~Box        ();                                                       

    //Accesseurs
    inline        std::string getName             () const;
    inline        long        getX1               () const;
    inline        long        getY1               () const;
    inline        long        getX2               () const;
    inline        long        getY2               () const;
    inline        bool        isEmpty             () const;
    inline        long        getWidth            () const;
    inline        long        getHeight           () const;
    inline static int         getAllocateds       ();
                  void        print               (std::ostream&) const;


    //Modificateurs
    void        makeEmpty           ();
    void        inflate             (long dxy);
    void        inflate             (long dx, long dy);
    void        inflate             (long dx1, long dy1, long dx2, long dy2);
    bool        intersect           (const Box&) const;
    Box         getIntersection     (const Box&) const;

    //Surcharges
    friend std::ostream& operator<<(std::ostream& flux, Box const &box);
    Box operator&&(const Box&);
};

    //Fonctions inline
    inline int Box::getAllocateds()        { return countQf_; }
    inline std::string Box::getName() const{ return name_;  }
    inline long Box::getX1()          const{ return x_ - (width_ /2 );     }
    inline long Box::getY1()          const{ return y_ - (height_/2 );     }
    inline long Box::getX2()          const{ return x_ + (width_ /2.0 );   }
    inline long Box::getY2()          const{ return y_ + (height_/2 );     }
    inline bool Box::isEmpty()        const{ return (width_ <= 0 || height_ <= 0);  }
    inline long Box::getWidth()       const{ return width_;     }
    inline long Box::getHeight()      const{ return height_;    }

}
