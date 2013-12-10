#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class Vec2;
class Scene;
class GameObject;


class Renderer {
public:
	virtual 			~Renderer();
	virtual bool 		Init(Vec2 coordBounds);
	virtual void 		RenderFrame(Scene *scene);

	virtual void 		PushTransform();
	virtual void 		ApplyTransform(GameObject *object);
	virtual void 		PopTransform();

protected:

private:

};

#undef TRUTLE_HEADER