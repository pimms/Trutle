#pragma once

#define TRUTLE_HEADER

#include "../Trutle.h"

class GameObject;
class Vec2;


class Component {
public:
	 					Component(GameObject*);
	virtual 			~Component() {}

	virtual void 		OnCreate() {}
	virtual void 		OnStart() {}
	virtual void 		OnPause() {}
	virtual void 		OnDestroy() {}
	virtual void 		Update(const DeltaTime&) {}

	GameObject* 		GetGameObject();
	Vec2& 				Position();
	Vec2& 				Scale();
	Vec2& 				Pivot();
	float& 				Rotation();

private:
	// GameObject creates and deletes components.
	GameObject 			*mGameObject;
};


#undef TRUTLE_HEADER