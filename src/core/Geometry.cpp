#include "Geometry.h"


/***** Vec2 Public Methods *****/
Vec2::Vec2()
{
	x = 0.f;
	y = 0.f;
}

Vec2::Vec2(float px, float py)
{
	x = px;
	y = py;
}

float Vec2::Length() const
{
	return sqrt(x*x + y*y);
}


/***** Line Public Methods *****/
Line::Line(Vec2 p1, Vec2 p2)
{
	pt1 = p1;
	pt2 = p2;
}

Line::Line()
{

}

float Line::Length() const
{
	float dx = pt1.x - pt2.x;
	float dy = pt1.y - pt2.y;

	return sqrt(dx*dx + dy*dy);
}
