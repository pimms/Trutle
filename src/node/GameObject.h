#pragma once
#define TRUTLE_HEADER

#include "../core/Log.h"
#include "../Trutle.h"
#include "../core/Geometry.h"
#include "Component.h"

#include <unordered_map>
#include <typeinfo>


class App;
class Scene;
class Layer;
class Texture;
class Renderer;
class GameObject;
class Controller;
class InputState;
class __ComponentManager;

typedef std::list<GameObject*> 	ChildList;
typedef ChildList::iterator 	ChildIter;

using std::type_info;
using std::unordered_map;



class GameObject {
private: 
	friend class __ComponentManager;

public:	
						GameObject();
	virtual 			~GameObject();

	void 				LoadTexture(std::string texfile);

	void 				UpdateSelfAndChildren(const DeltaTime &);
	virtual void		Update(const DeltaTime &delta);
	virtual void   		Render(Renderer *renderer);

	Vec2& 				Position();
	float&		 		Rotation();
	Vec2& 				Scale();
	Vec2& 				Pivot();

	void 				AddChild(GameObject *object);
	void 				RemoveChild(GameObject *object);
	ChildList* 			GetChildren();

	void 				SetParent(GameObject *parent);
	GameObject* 		GetParent();
	virtual Layer*		GetParentLayer();
	virtual Scene* 		GetScene();
	Controller* 		GetController();
	App* 				GetApp();
	const InputState*	GetInputState();

	Texture* 			GetTexture();

	void 				SetVisible(bool visible);
	bool 				GetVisible();

protected:

	ChildList  			mChildren;

	Vec2 				mPosition;
	Vec2 				mScale;
	float 				mRotation;
	Vec2 				mPivot;

	Texture 			*mTexture;

	bool 				mVisible;


private:
	void 				ReleaseTexture();
	
	GameObject 			*mParent;

	// Components are identified by their type, and only
	// one component per type can be attached to a game object
	// at any given time.
	unordered_map<const type_info*, Component*>
						mComponents;
};


// The global functions GetComponent(), AddComponent() and
// RemoveComponent() use templates to find and create
// components. The addition or removal of the component
// does then not occur until the start of the next frame.
class __ComponentManager {
public:
						__ComponentManager(GameObject*);

	void 				AddComponent(Component*, const type_info*);
	void 				RemoveComponent(const type_info*);

	unordered_map<const type_info*, Component*>* 
						GetComponentList();

	// Execute all commands in sCommands. Commands are executed in
	// the following order:
	//  - Removal of components, FIFO
	//  - Addition of components, FIFO
	static void 		ExecuteCommands();

	// Static methods to check if a component of a certain type_info
	// has been added or removed from a game object, but the 
	// action has not yet been executed.
	static bool 		HasBeenAdded(GameObject*, const type_info*);
	static bool 		HasBeenRemoved(GameObject*, const type_info*);

private:
	GameObject 			*mGameObject;

	struct Command {
		virtual void Execute() = 0;

		GameObject *gameObject;
		Component *component;
		const type_info *type;
		char typeID;
	};

	// NewComponentCmd adds the command  to the component 
	// list of the GameObject and calls OnStart() on it.
	#define _CMP_MGR_NEW_COMPONENT_ID 1
	struct NewComponentCmd : Command {
		NewComponentCmd() 
			{ typeID = _CMP_MGR_NEW_COMPONENT_ID; };
		void Execute();
	};

	// RemoveComponentCmd calls OnDestroy() on the 
	// component, and removes it from the GameObject-list.
	#define _CMP_MGR_REMOVE_COMPONENT_ID 2
	struct RemoveComponentCmd : Command {
		RemoveComponentCmd() 
			{ typeID = _CMP_MGR_REMOVE_COMPONENT_ID; };
		void Execute();
	};

	static std::list<Command*> sCommands;
};



// Components are retrieved from this function. The 
// component of type _CompT is returned if it is 
// attached to the GameObject.
template<class _CompT> 
_CompT* GetComponent(GameObject *gameObject) {
	__ComponentManager mgr(gameObject);

	unordered_map<const type_info*, Component*>* comps;
	comps = mgr.GetComponentList();

	if (comps->count(&typeid(_CompT)) != 0) {
        return static_cast<_CompT*>((*comps)[&typeid(_CompT)]);
    } 

    return NULL;
}

// The Component is created inside the template-function,
// but is given to a __ComponentManager for initialization
// and attachment to the game object.
template<class _CompT> 
_CompT* AddComponent(GameObject *gameObject) {
	__ComponentManager mgr(gameObject);

	unordered_map<const type_info*, Component*>* comps;
	comps = mgr.GetComponentList();

	const type_info *type = &typeid(_CompT);

	if (comps->count(type) != 0 &&
		!__ComponentManager::HasBeenAdded(gameObject, type)) {
		std::string err = 	(std::string)
							"Component already exists on GameObject!"
						  	" component: " + typeid(_CompT).name();
		Log::Debug(err);
		return NULL;
	}

	_CompT *component = new _CompT();
	component->SetGameObject(gameObject);
	
	mgr.AddComponent(component, &typeid(_CompT));

	return component;
}

// The component is only located from within this function.
// The component is given to a __ComponentManager, who
// will handle the destruction process further.
template<class _CompT>
bool RemoveComponent(GameObject *gameObject) {
	__ComponentManager mgr(gameObject);

	unordered_map<const type_info*, Component*> *comps;
	comps = mgr.GetComponentList();

	const type_info *type = &typeid(_CompT);

	if (comps->count(type) != 0 &&
		!__ComponentManager::HasBeenRemoved(gameObject, type)) 
	{
		mgr.RemoveComponent(&typeid(_CompT));
		return true;
	}

	return false;
}

#undef TRUTLE_HEADER