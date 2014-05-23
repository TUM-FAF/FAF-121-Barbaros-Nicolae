#ifndef OBJECTS_H
#define OBJECTS_H

#include <iostream>
#include <windows.h>
#include <cmath>
#include <mmsystem.h>
#include <time.h>
//Define the timer ID
#define ID_TIMER 333

using namespace std;

class Objects {

protected:
    COLORREF clr;
public:
    POINT center;
    int xSpeed,ySpeed;

    Objects(POINT center,const int &speed);
    bool Accelerate(const int& deltaSpeedX,const int& deltaSpeedY);
    bool Color(const COLORREF &clr);
    bool Collision(const RECT &rect);
    virtual bool Move(const HDC &hdc,const RECT& rect,HBRUSH &hBrush)=0;
};

class Circle : public Objects {
public:
    Circle(POINT center,const int &speed): Objects(center,speed)
    {
    }
    bool Move(const HDC &hdc,const RECT& rect,HBRUSH &hBrush);
};

bool Interaction(Objects &alfa,Objects &beta);
#endif // _Objects
