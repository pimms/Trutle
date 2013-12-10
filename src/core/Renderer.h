#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class Vec2;
class Scene;


class Renderer {
public:
	virtual 			~Renderer();
	virtual bool 		Init(Vec2 coordBounds);
	virtual void 		RenderFrame(Scene *scene);

protected:

private:

};

#undef TRUTLE_HEADER