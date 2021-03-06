#pragma once

#define TRUTLE_HEADER

#include "../Trutle.h"

class GameObject;
class Vec2;


class Component
{
public:
	virtual 			~Component() {}
	void 				SetGameObject(GameObject*);

	virtual void 		OnCreate() {}
	virtual void 		OnStart() {}
	virtual void 		OnPause() {}
	virtual void 		OnDestroy() {}
	virtual void 		Update(const DeltaTime&) {}

	GameObject* 		GetGameObject();
	const GameObject*	GetGameObject() const;


	// These methods return the attributes of the owning GameObject.
	// Obviously, Components have no geometrical attributes.
	Vec2& 				Position();
	Vec2 				Position() const;
	Vec2& 				Scale();
	Vec2 				Scale() const;
	Vec2& 				Pivot();
	Vec2 				Pivot() const;
	float& 				Rotation();
	float 				Rotation() const;

private:
	// GameObject creates and deletes components.
	GameObject 			*mGameObject;
};


#undef TRUTLE_HEADER
