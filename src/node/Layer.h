#pragma once
#define TRUTLE_HEADER

#include "GameObject.h"

class Scene;


class Layer : public GameObject
{
public:
	Layer();

	void 				SetScene(Scene *scene);

	virtual Layer* 		GetParentLayer();
	virtual Scene* 		GetScene();
	Vec2 				WorldPosition();
	float 				WorldRotation();

protected:

private:
	Scene 				*mScene;
};


#undef TRUTLE_HEADER
