#include "GameObject.h"
#include "../core/Renderer.h"
#include "../res/ResourceManager.h"
#include "../res/Texture.h"


GameObject::GameObject() {
	mRotation = 0.f;
	mScale = {1.f, 1.f};
	mTexture = NULL;
}

GameObject::~GameObject() {
	ReleaseTexture();

	ChildIter iter = mChildren.begin();
	while (iter != mChildren.end()) {
		delete *iter;
		iter++;
	}
}

void GameObject::LoadTexture(std::string texfile) {
	ReleaseTexture();

	mTexture = (Texture*)ResourceManager::
						GetResource(texfile, Resource::TEXTURE);
}

void GameObject::UpdateSelfAndChildren(const DeltaTime &delta) {
	Update(delta);

	ChildIter iter = mChildren.begin();
	while (iter != mChildren.end()) {
		(*iter)->UpdateSelfAndChildren(delta);
		iter++;
	}
}

void GameObject::Update(const DeltaTime &delta) {
	// ...
}

void GameObject::Render(Renderer *renderer) {
	renderer->PushTransform();
	renderer->ApplyTransform(this);

	if (mTexture) {
		renderer->RenderTexture(
			mTexture, 
			Rect(Vec2(0,0), mTexture->GetDimensions())
		);
	}

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

Vec2& GameObject::Scale() {
	return mScale;
}

void GameObject::AddChild(GameObject *object) {
	mChildren.push_back(object);
}

void GameObject::RemoveChild(GameObject *object) {
	mChildren.remove(object);
}

ChildList* GameObject::GetChildren() {
	return &mChildren;
}


/***** Private Methods *****/
void GameObject::ReleaseTexture() {
	if (mTexture) {
		mTexture->Release();
		mTexture = NULL;
	}
}