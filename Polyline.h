//
// Created by Charidimos Koudoumas on 29/5/20.
//

#ifndef SET2_POLYLINE_H
#define SET2_POLYLINE_H

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int maxPoints = 100;


class myPolyline {

public:
    myPolyline(int);        // the number of points passes as parameter
    myPolyline();           // N = 0, need to manually points as you use an object

    myPolyline(string);     //constructor, with input param file name, if file is empty or rows are>=Max points, exit

    // --- getters ---
    float getX(int);        // x-coord
    float getY(int);        // y-coord
    int getN();             // number of points (N <= Nmax)

    float getL();             // number of points (N <= Nmax)

    // --- setters ---
    void setX(int, float);

    void setY(int, float);

    // --- behaviour ---
    void addPoint(float, float);

    void movePoint(int, float, float);

    void removePoint(int);

    void polyPrint();

    void addAtEndOfPolyline(int, int);

    void writePolylineToFile(string);

    //Overload operator + to add 2 polylines
    myPolyline operator+(const myPolyline &p) {
        int aggregatedPointsNumber = this->getN() + p.N;
        myPolyline polyline(aggregatedPointsNumber);
        for (int i = 1; i < this->getN(); i++) {
            polyline.points_x[i] = this->points_x[i];
            polyline.points_y[i] = this->points_y[i];
        }
        for (int j = 1; j < p.N; j++) {
            polyline.points_x[j] = this->points_x[j];
            polyline.points_y[j] = this->points_y[j];
        }
        return polyline;
    }

    float calculateLengthCustomStart(int);


protected:
    // 2-DO: make all fields private, create setters + getters
    float points_x[maxPoints];
    float points_y[maxPoints];
    float Len;
    int N;        // SHOULD be <= maxPoints
    void calcLen();

    void movePolyline(int);

    int getXByPosition(int);

    int getYByPosition(int);

    // 2-DO: add method movePoint(int p, float new_x, float new_y) to move point p to (new_x, new_y) [DONE!]

    // 2-DO: add method removePoint(int p) to remove point p from the polyline                      [DONE!]
    //       IMPORTANT:	when removing a point, those to the right will need to shift to the left
    //					K--, calc new len, etc
private:
    int distance2Points(int, int, int, int);

};

//
// Created by Charidimos Koudoumas on 29/5/20.
//

#ifndef UNTITLED2_TRACK_H
#define UNTITLED2_TRACK_H


class myTrack : public myPolyline {
public:

    myTrack();      // default constructor
    myTrack(int);

    myTrack(string);

    void trackDisplay();

    void addTrackPoint(int, int, float);

    void addAtEndOfTrack(int, int, float);

    void removeTrack(int p);

    void moveTrack(int);

    float getTrackLength();

    float getTrackTime();

    float getAverageSpeed();

    void writeTrackToFile(string);

    //Overload operator + to add 2 tracks
    myTrack operator+(const myTrack &p) {
        int aggregatedPointsNumber = this->getN() + p.N;
        myTrack myTrack(aggregatedPointsNumber);
        for (int i = 1; i < this->getN(); i++) {
            myTrack.points_x[i] = this->points_x[i];
            myTrack.points_y[i] = this->points_y[i];
            myTrack.segmentTime[i] = this->segmentTime[i];
        }
        for (int j = 1; j < p.N; j++) {
            myTrack.points_x[j] = this->points_x[j];
            myTrack.points_y[j] = this->points_y[j];
            myTrack.segmentTime[j] = this->segmentTime[j];
        }
        return myTrack;
    }

protected:
    float segmentTime[maxPoints];
    float totalTime;
};

void myTrack::addTrackPoint(int px, int py, float pt) {
    if (N < maxPoints) {
        points_x[N] = px;
        points_y[N] = py;
        segmentTime[N] = pt;

        totalTime += pt;
        N++;

        calcLen();
    }
}

myTrack::myTrack() {
    //---> calls the default constructor of the parent class <---
    totalTime = 0;
}

// ----------------------------------------------------
myTrack::myTrack(int P) : myPolyline(P) {

    // ---> the specified parent constructor myPolyline(P) is executed first

    segmentTime[0] = 0;

    totalTime = 0;
    for (int i = 1; i < N; i++) {
        cout << "Enter segment time for " << i - 1 << " -> " << i << ": ";
        cin >> segmentTime[i];
        totalTime += segmentTime[i];
    }
}

myTrack::myTrack(string fileName) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream infile(fileName);

    while (std::getline(infile, line))
        ++number_of_lines;

    infile.clear();
    infile.seekg(0, ios::beg);
    if (number_of_lines > 0 && number_of_lines <= maxPoints) {
        myPolyline(number_of_lines);
        int a, b, t;
        while (infile >> a >> b >> t) {
            addTrackPoint(a, b, t);
        }
    } else if (number_of_lines == 0) {
        cout << "File is empty";
    } else {
        cout << "File contains more points that max number of points: " << maxPoints;
    }
}

void myTrack::addAtEndOfTrack(int x, int y, float t) {
    if (getN() < maxPoints) {
        addTrackPoint(x, y, t);
    }
}

void myTrack::removeTrack(int p) {
    if (getN() < maxPoints) {
        removePoint(p);
        segmentTime[p] = 0;
    }
}

void myTrack::moveTrack(int d) {
    moveTrack(d);
}

float myTrack::getTrackLength() {
    return getL();
}

float myTrack::getTrackTime() {
    for (int i = 0; i < N; i++) {
        totalTime += segmentTime[i];
    }
    return totalTime;
}

float myTrack::getAverageSpeed() {
    return getTrackLength() / getTrackTime();
}

void myTrack::trackDisplay() {
    cout << "\nTrack data:\n";
    for (int i = 1; i < N; i++) {
        cout << " " << i - 1 << " -> " << i << " : (" << points_x[i - 1] << ", " << points_y[i - 1] <<
             ") -> (" << points_x[i] << ", " << points_y[i] << ") at " << segmentTime[i] << " sec\n";
    }
    cout << " Track len  = " << Len << endl;
    cout << " Total time = " << totalTime << endl;

}

void myTrack::writeTrackToFile(string filename) {
    ofstream myfile(filename);
    if (myfile.is_open()) {
        for (int i = 0; i < N; i++) {
            myfile << points_x[i] << " " << points_y[i] << segmentTime[i];
        }
    }
    cout << "Track was extracted to file: " << filename;
}

#endif //UNTITLED2_TRACK_H


// -------------------------------------------------------------

void myPolyline::movePoint(int where, float newX, float newY) {

    if (where < N) {
        points_x[where] = newX;
        points_y[where] = newY;
        calcLen();
    }
    // --------------- Discussion: is the following a more "elegant" choice?----
    // setX(where, newX);
    // setY(where, newY);
    // -------------------------------------------------------------------------
}


// -------------------------------------------------------------

void myPolyline::removePoint(int k) {
    if (k < N) {
        for (int i = k; i < N - 1; i++) {
            points_x[i] = points_x[i + 1];
            points_y[i] = points_y[i + 1];
        }
        N = N - 1;
        calcLen();
    }
}

// -------------------------------------------------------------
void myPolyline::setX(int where, float what) {
    if (where < N) {
        points_x[where] = what;
        calcLen();
    }
}

// -------------------------------------------------------------

void myPolyline::setY(int where, float what) {
    if (where < N) {
        points_y[where] = what;
        calcLen();
    }
}

// -------------------------------------------------------------

float myPolyline::getX(int where) {
    if (where < N) {
        return points_x[where];
    }
    return 0;
}

// -------------------------------------------------------------

float myPolyline::getY(int where) {
    if (where < N) {
        return points_y[where];
    }
    return 0;
}

// -------------------------------------------------------------

void myPolyline::addPoint(float newX, float newY) {

    if (N < maxPoints) {
        points_x[N] = newX;
        points_y[N] = newY;
        N++;
        calcLen();
    }
}

// -------------------------------------------------------------

void myPolyline::calcLen() {

    Len = 0;

    float segmentLength;

    if (N == 1) return;

    for (int i = 0; i < N - 1; i++) {
        segmentLength = sqrt((points_x[i] - points_x[i + 1]) * (points_x[i] - points_x[i + 1]) +
                             (points_y[i] - points_y[i + 1]) * (points_y[i] - points_y[i + 1]));
        // debugging info...
        // cout<<"i= "<<i<<", now adding "<<segmentLength<<" from "<<i<<" to "<< i+1<<" to len\n";
        Len = Len + segmentLength;
    }

}

// -------------------------------------------------------------

myPolyline::myPolyline(int koryfes) {
    // ---> need to verify that koryfes <= maxPoints

    N = koryfes;

    for (int i = 0; i < N; i++) {
        cout << "enter x " << i << ": ";
        cin >> points_x[i];
        cout << "enter y " << i << ": ";
        cin >> points_y[i];

    }

    calcLen();
}

// -------------------------------------------------------------

myPolyline::myPolyline() {

    N = 0;
    Len = 0;
}

// -------------------------------------------------------------

myPolyline::myPolyline(string fileName) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream infile(fileName);

    while (std::getline(infile, line))
        ++number_of_lines;

    infile.clear();
    infile.seekg(0, ios::beg);
    if (number_of_lines > 0 && number_of_lines <= maxPoints) {
        myPolyline(number_of_lines);
        int a, b;
        while (infile >> a >> b) {
            addPoint(a, b);
        }
    } else if (number_of_lines == 0) {
        cout << "File is empty";
    } else {
        cout << "File contains more points that max number of points: " << maxPoints;
    }

}

void myPolyline::addAtEndOfPolyline(int x, int y) {
    if (N < maxPoints) {
        points_x[N + 1] = x;
        points_y[N + 1] = y;
        N = N + 1;
        calcLen();
    }
}

// -------------------------------------------------------------

void myPolyline::polyPrint() {
    cout << "\nPolyline data:\n";
    for (int i = 0; i < N; i++) {
        cout << " " << i << " : (" << points_x[i] << ", " << points_y[i] << ")\n";
    }
    cout << " Len = " << Len << endl << endl;


}

// -------------------------------------------------------------

int myPolyline::getN() {
    return N;
}

// -------------------------------------------------------------

void myPolyline::movePolyline(int d) {
    for (int i = 0; i < N; i++) {
        points_x[i] = points_x[i] + d;
    }
    calcLen();
}

// -------------------------------------------------------------

int myPolyline::getXByPosition(int p) {
    return points_y[p];
}

// -------------------------------------------------------------

int myPolyline::getYByPosition(int p) {
    return points_x[p];
}

int myPolyline::distance2Points(int x, int x1, int y, int y1) {
    return sqrt(pow(x1 - x, 2) - pow(y1 - y, 2));
}

float myPolyline::getL() {
    calcLen();
    return Len;
}

void myPolyline::writePolylineToFile(string filename) {
    ofstream myfile(filename);
    if (myfile.is_open()) {
        for (int i = 0; i < N; i++) {
            myfile << points_x[i] << " " << points_y[i];
        }
    }
    cout << "Polyline was extracted to file: " << filename;
}

float myPolyline::calculateLengthCustomStart(int startingPosition) {
    int customLength = 0;
    if (N - 1 == startingPosition) {
        return 0;
    }
    for (int i = startingPosition; i < N - 1; i++) {
        customLength += customLength + distance2Points(points_x[i], points_x[i + 1], points_y[i], points_y[i + 1]);
    }
    return customLength;
}

#endif //SET2_POLYLINE_H
