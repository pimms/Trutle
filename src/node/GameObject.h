#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "../core/Geometry.h"

class Renderer;
class GameObject;
class Texture;

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

	void 				AddChild(GameObject *object);
	void 				RemoveChild(GameObject *object);
	ChildList* 			GetChildren();

protected:
	ChildList  			mChildren;

	Vec2 				mPosition;
	Vec2 				mScale;
	float 				mRotation;

	Texture 			*mTexture;

private:
	void 				ReleaseTexture();
};


#undef TRUTLE_HEADER