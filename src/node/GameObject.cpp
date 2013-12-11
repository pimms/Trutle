#include "GameObject.h"
#include "Layer.h"
#include "Scene.h"
#include "../core/Renderer.h"
#include "../core/Controller.h"
#include "../core/App.h"
#include "../res/ResourceManager.h"
#include "../res/Texture.h"


GameObject::GameObject() {
	mRotation = 0.f;
	mScale = {1.f, 1.f};
	mTexture = NULL;
	mParent = NULL;
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

void GameObject::SetParent(GameObject *parent) {
	mParent = parent;
}

GameObject* GameObject::GetParent() {
	return mParent;
}

Layer* GameObject::GetParentLayer() {
	if (mParent) {
		return mParent->GetParentLayer();
	}

	return NULL;
}

Scene* GameObject::GetScene() {
	if (GetParent()) {
		return GetParent()->GetScene();
	}

	return NULL;
}

Controller* GameObject::GetController() {
	Scene *scene = GetScene();
	if (scene) {
		return scene->GetController();
	}

	return NULL;
}

App* GameObject::GetApp() {
	Controller *ctrl = GetController();
	if (ctrl) {
		return ctrl->GetApp();
	}

	return NULL;
}


/***** Private Methods *****/
void GameObject::ReleaseTexture() {
	if (mTexture) {
		mTexture->Release();
		mTexture = NULL;
	}
}