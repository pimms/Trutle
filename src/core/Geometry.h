#pragma once
#define TRUTLE_HEADER


class Vec2 {
public:
	float 			x;
	float 			y;

					Vec2();
					Vec2(float x, float y);
};


template<typename T>
class t_Rect {
public:
	T 	x;
	T 	y;
	T 	w;
	T 	h;

	t_Rect() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}

	t_Rect(T px, T py, T pw, T ph) {
		x = px;
		y = py;
		w = pw;
		h = ph;
	}
};

typedef t_Rect<int>   RectI;
typedef t_Rect<float> Rect;

#undef TRUTLE_HEADER