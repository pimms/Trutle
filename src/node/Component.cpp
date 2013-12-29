#include "Component.h"
#include "../core/Geometry.h"
#include "GameObject.h"


/***** Public Methods *****/
GameObject* Component::GetGameObject() {
	return mGameObject;	
}

Vec2& Component::Position() {
	return GetGameObject()->Position();
}

Vec2& Component::Scale() {
	return GetGameObject()->Scale();
}

Vec2& Component::Pivot() {
	return GetGameObject()->Pivot();
}

float& Component::Rotation() {
	return GetGameObject()->Rotation();
}