#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class Scene;
class Renderer;


class Controller {
public:
						Controller();
	virtual 			~Controller();

	virtual void 		LoadContent();

	void 				SetScene(Scene *scene);
	void 				SceneTransition();

	virtual void 		Update(const DeltaTime &delta);

protected:
	virtual Renderer*	CreateRenderer();
	virtual void 		DrawScene();

	Renderer 			*mRenderer;
	Scene 				*mScene;
	Scene 				*mNewScene;

private:

};


#undef TRUTLE_HEADER