#include "Box.h"
#include <iostream>
#include <string>

Box testFunction ( Box ab )
{
    cerr << "   + testFunction() called." << endl;
    Box area ( "area", 0, 0, 15, 50 );
    if ( area.intersect(ab)){
        cerr << "   | Intersection between:"  << endl;
        cerr << "   |   " << area << endl;
        cerr << "   |   " << ab   << endl;
        cerr << "   | Gives:" << endl;
        cerr << "   |   " << area.getIntersection(ab) << endl;
    } else
        cout << " No Intersection" << endl;
    return ab;
}


int main (int argc, char* argv[])
{
    {   Box b0;
        Box b1 (  "b1", 15, 10, 30, 20);
    //  cerr << "Allocated boxes: " << Box::getAllocateds() << endl;

        cerr << "\nTest 1: "; b1.print(cerr); cerr << endl;
        testFunction ( b1 );

        b1.inflate ( 5, 5, 5, 5 );
        cerr << "\nTest 2: "; b1.print(cerr); cerr << endl;
        testFunction ( b1 );

        cerr << "\nTest 3: "<< endl;
        cerr << "+ Box \"" << b1.getName() << "\" empty:  " << boolalpha << b1.isEmpty   () << endl;
        cerr << "+ Box \"" << b1.getName() << "\" width:  " << b1.getWidth () << endl;
        cerr << "+ Box \"" << b1.getName() << "\" height  " << b1.getGeight() << endl;
        b1.inflate ( -11 );
        cerr << "+ Box \"" << b1.getName() << "\" empty:  " << boolalpha << b1.isEmpty   () << " (inflated -11)" << endl;
        cerr << "+ Box \"" << b1.getName() << "\" width:  " << b1.getWidth () << endl;
        cerr << "+ Box \"" << b1.getName() << "\" height: " << b1.getGeight() << endl;

    }
//  cerr << "Allocated boxes: " << Box::getAllocateds() << endl;

    return 0;

}