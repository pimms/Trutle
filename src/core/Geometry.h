#pragma once
#define TRUTLE_HEADER

#define _USE_MATH_DEFINES
#include <math.h>


struct Vec2 {
public:
	float 	x;
	float 	y;

	Vec2();
	Vec2(float x, float y);
	float 	Length() const;
};


struct Line {
public:
	Line();
	Line(Vec2 p1, Vec2 p2);

	float Length() const;

	Vec2 	pt1;
	Vec2 	pt2;
};


// Not geometry but YOLO, it's similar to the other types in here
template<typename T>
struct t_Color {
public:
	t_Color() {};
	t_Color(T r, T g, T b, T a) 
		:	r(r), g(g), b(b), a(a)
	{ }

	T 	r;
	T	g;
	T	b;
	T	a;
};

typedef t_Color<float> Color;
typedef t_Color<unsigned char> ColorUB;


template<typename T>
struct t_Rect {
public:
	T 	x;
	T 	y;
	T 	w;
	T 	h;

	t_Rect()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}

	t_Rect(T px, T py, T pw, T ph)
	{
		x = px;
		y = py;
		w = pw;
		h = ph;
	}

	t_Rect(Vec2 pos, Vec2 dim)
	{
		x = pos.x;
		y = pos.y;
		w = dim.x;
		h = dim.y;
	}

	bool Overlaps(t_Rect<T> t) 
	{
		return !(x >= t.x + t.w && 
				x + w <= t.x 	&&
				y >= t.y + t.h 	&&
				y + h <= t.y);
	}
};

typedef t_Rect<int>   RectI;
typedef t_Rect<float> Rect;

#undef TRUTLE_HEADER
