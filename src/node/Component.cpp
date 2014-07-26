#include "Component.h"
#include "../core/Geometry.h"
#include "GameObject.h"


/***** Public Methods *****/
GameObject* Component::GetGameObject()
{
	return mGameObject;
}

const GameObject* Component::GetGameObject() const
{
	return mGameObject;
}

void Component::SetGameObject(GameObject *gameObject)
{
	mGameObject = gameObject;
}

Vec2& Component::Position()
{
	return GetGameObject()->Position();
}

Vec2 Component::Position() const
{
	return GetGameObject()->Position();
}

Vec2& Component::Scale()
{
	return GetGameObject()->Scale();
}

Vec2 Component::Scale() const
{
	return GetGameObject()->Scale();
}

Vec2& Component::Pivot()
{
	return GetGameObject()->Pivot();
}

Vec2 Component::Pivot() const
{
	return GetGameObject()->Pivot();
}

float& Component::Rotation()
{
	return GetGameObject()->Rotation();
}

float Component::Rotation() const
{
	return GetGameObject()->Rotation();
}
