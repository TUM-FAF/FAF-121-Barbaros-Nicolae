#include "Bezier.h"

MyBezier::~MyBezier()
{

}

MyBezier::MyBezier()
{

}

void MyBezier::DrawBezier(HDC hdc, POINT apt[])
{
	PolyBezier(hdc, apt, 4);

	 MoveToEx (hdc, apt[0].x, apt[0].y, NULL) ;
     LineTo   (hdc, apt[1].x, apt[1].y) ;
     
     MoveToEx (hdc, apt[2].x, apt[2].y, NULL) ;
     LineTo   (hdc, apt[3].x, apt[3].y) ;
}
