#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "../core/Geometry.h"

#include <unordered_map>

class App;
class Scene;
class Layer;
class Texture;
class Renderer;
class GameObject;
class Controller;
class InputState;
class Component;

typedef std::list<GameObject*> 	ChildList;
typedef ChildList::iterator 	ChildIter;

using std::type_info;
using std::unordered_map;

class GameObject {
public:	
						GameObject();
	virtual 			~GameObject();

	void 				LoadTexture(std::string texfile);

	void 				UpdateSelfAndChildren(const DeltaTime &);
	virtual void		Update(const DeltaTime &delta);
	virtual void 		Render(Renderer *renderer);

	virtual Vec2& 		Position();
	virtual float& 		Rotation();
	virtual Vec2& 		Scale();
	virtual Vec2& 		Pivot();

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


	// ONLY PUBLIC FOR ACCESS FROM GetComponent(GameObject*)!!!
	// Do not use!
	unordered_map<const type_info*, Component*>*__GetComponents();

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

	unordered_map<const type_info*, Component*> 
						mComponents;
};


// Components are retrieved from this function. The 
// component of type _CompT is returned if it is 
// attached to the GameObject.
template<class _CompT> 
_CompT* GetComponent(GameObject *gameObject) {
	unordered_map<const type_info*, Component*>* comps;
	comps = gameObject->__GetComponents();

	if (comps->count(&typeid(_CompT)) != 0) {
        return static_cast<_CompT*>((*comps)[&typeid(_CompT)]);
    } 

    return NULL;
}


#undef TRUTLE_HEADER