#include "GameObject.h"
#include "../core/Renderer.h"


GameObject::GameObject() {
	mRotation = 0.f;
}

GameObject::~GameObject() {

}

void GameObject::Update(const DeltaTime &delta) {
	// ...
}

void GameObject::Render(Renderer *renderer) {
	renderer->PushTransform();

	ChildIter iter = mChildren.begin();
	while (iter != mChildren.end()) {
		(*iter)->Render(renderer);
		iter++;
	}

	renderer->PopTransform();
}

Vec2& GameObject::Position() {
	return mPosition;
}

float& GameObject::Rotation() {
	return mRotation;
}

