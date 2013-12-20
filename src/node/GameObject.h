#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "../core/Geometry.h"

class App;
class Scene;
class Layer;
class Texture;
class Renderer;
class GameObject;
class Controller;
class InputState;

typedef std::list<GameObject*> 	ChildList;
typedef ChildList::iterator 	ChildIter;


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

protected:
	ChildList  			mChildren;

	Vec2 				mPosition;
	Vec2 				mScale;
	float 				mRotation;
	Vec2 				mPivot;

	Texture 			*mTexture;

private:
	void 				ReleaseTexture();

	GameObject 			*mParent;
};


#undef TRUTLE_HEADER