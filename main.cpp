#include <iostream>


#include "Polyline.h"
int main() {

    //myPolyline myPoly1(5);
    //myPoly1.polyPrint();

    //myTrack track0;

    //myTrack track1(3);
   //track1.trackDisplay();

    //track1.addTrackPoint(10, 20, 6.0);
    //track1.trackDisplay();


    //myPoly1.removePoint(3);
    //myPoly1.polyPrint();



//    myPoly1.addPoint(3.0, 3.0);  // will improve this by asking the user to enter data
//    myPoly1.polyPrint();
//
//    myPoly1.setX(3, 4.0);
//    myPoly1.setY(3, 5.0);
//    myPoly1.polyPrint();

    // myPolyline myPoly2(2);
    // myPoly2.polyPrint();
    // myPolyline myPoly3;
    // myPoly3.polyPrint();


    //Read from file
    const myPolyline &polyline = myPolyline("polyline.txt");



    return 0;

}
