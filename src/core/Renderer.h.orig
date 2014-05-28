#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Geometry.h"

class Vec2;
class Scene;
class Texture;
class GameObject;


class Renderer {
public:
	static bool 		PrintOpenGLErrors(std::string ctx);

	virtual 			~Renderer();
	virtual bool 		Init(Vec2 coordBounds);
	virtual void 		RenderFrame(Scene *scene);

	virtual void 		PushTransform();
	virtual void 		ApplyTransform(GameObject *object);
	virtual void 		PopTransform();

	virtual void 		RenderTexture(Texture *tex, Rect pixelClip, Vec2 pivot);

protected:

private:

};

#undef TRUTLE_HEADER