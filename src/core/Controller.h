#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "CommitPtr.h"

class Scene;
class Renderer;


class Controller {
public:
						Controller();
	virtual 			~Controller();

	virtual void 		LoadContent();

	void 				SetScene(Scene *scene);
	Scene* 				GetScene();
	virtual void 		SceneTransition();

	virtual void 		Update(const DeltaTime &delta);

protected:
	virtual Renderer*	CreateRenderer();
	virtual void 		DrawScene();

	Renderer 			*mRenderer;
	CommitPtr<Scene> 	mScene;

private:

};


#undef TRUTLE_HEADER