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
	mPivot = {0.5f, 0.5f};

	mTexture = NULL;
	mParent = NULL;
	mVisible = true;
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

	if (mTexture && mVisible) {
		renderer->RenderTexture(
			mTexture, 
			Rect(Vec2(0,0), mTexture->GetDimensions()),
			Pivot()
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

Vec2& GameObject::Pivot() {
	return mPivot;
}

void GameObject::AddChild(GameObject *object) {
	mChildren.push_back(object);
	object->SetParent(this);
}

void GameObject::RemoveChild(GameObject *object) {
	mChildren.remove(object);
	object->SetParent(NULL);
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

const InputState* GameObject::GetInputState() {
	App *app = GetApp();
	if (app) {
		return app->GetInputState();
	}

	return NULL;
}

Texture* GameObject::GetTexture() {
	return mTexture;
}

void GameObject::SetVisible(bool visible) {
	mVisible = visible;
}

bool GameObject::GetVisible() {
	return mVisible;
}


/***** Private Methods *****/
void GameObject::ReleaseTexture() {
	if (mTexture) {
		mTexture->Release();
		mTexture = NULL;
	}
}



/*
=====================================
= __ComponentManager implementation =
=====================================
*/
std::list<__ComponentManager::Command*> __ComponentManager::sCommands;

__ComponentManager::__ComponentManager(GameObject *gameObject) 
			: mGameObject(gameObject) {

}

void __ComponentManager::AddComponent(	Component *component, 
										const type_info *type) {
	component->OnCreate();

	NewComponentCmd *ncomp = new NewComponentCmd();
	ncomp->component = component;
	ncomp->gameObject = mGameObject;
	ncomp->type = type;

	sCommands.push_back(ncomp);
}

void __ComponentManager::RemoveComponent(const type_info *type) {
	Component *component = mGameObject->mComponents[type];
	
	RemoveComponentCmd *rcomp = new RemoveComponentCmd();
	rcomp->component = component;
	rcomp->gameObject = mGameObject;
	rcomp->type = type;

	sCommands.push_front(rcomp);
}

unordered_map<const type_info*, Component*>*
					__ComponentManager::GetComponentList() {
	return &mGameObject->mComponents;
}


/***** Static Methods *****/
void __ComponentManager::ExecuteCommands() {
	while (sCommands.size()) {
		sCommands.front()->Execute();
		sCommands.erase(sCommands.begin());
	}
}

bool __ComponentManager::HasBeenAdded(	GameObject *gameObject, 
										const std::type_info *type ) {
	for (auto it = sCommands.begin(); it != sCommands.end(); it++) {
		if ((*it)->typeID == _CMP_MGR_NEW_COMPONENT_ID &&
			(*it)->type == type && 
			(*it)->gameObject == gameObject) {
			return true;
		}
	}

	return false;
}

bool __ComponentManager::HasBeenRemoved(GameObject *gameObject, 
										const std::type_info * type) {
	for (auto it = sCommands.begin(); it != sCommands.end(); it++) {
		if ((*it)->typeID == _CMP_MGR_REMOVE_COMPONENT_ID &&
			(*it)->type == type && 
			(*it)->gameObject == gameObject) {
			return true;
		}
	}

	return false;
}


/***** __ComponentManager commands *****/
void __ComponentManager::NewComponentCmd::Execute() {
	gameObject->mComponents[type] = component;
	component->OnStart();
}

void __ComponentManager::RemoveComponentCmd::Execute() {
	component->OnDestroy();
	gameObject->mComponents.erase(type);
}