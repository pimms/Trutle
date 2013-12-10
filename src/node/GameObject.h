#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "../core/Vec2.h"

class Renderer;
class GameObject;

typedef std::list<GameObject*> 	ChildList;
typedef ChildList::iterator 	ChildIter;


class GameObject {
public:	
						GameObject();
	virtual 			~GameObject();

	virtual void		Update(const DeltaTime &delta);
	virtual void 		Render(Renderer *renderer);

	virtual Vec2& 		Position();
	virtual float& 		Rotation();

protected:
	Vec2 				mPosition;
	float 				mRotation;
	ChildList  			mChildren;

private:

};


#undef TRUTLE_HEADER