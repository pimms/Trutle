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
	renderer->ApplyTransform(this);

	glPointSize(10.f);
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(0.f, 0.f);
	glVertex2f(10.f, 0.f);
	glVertex2f(10.f, 10.f);
	glVertex2f(0.f, 10.f);
	glEnd();

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

void GameObject::AddChild(GameObject *object) {
	mChildren.push_back(object);
}

void GameObject::RemoveChild(GameObject *object) {
	mChildren.remove(object);
}
