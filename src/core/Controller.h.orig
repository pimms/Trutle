#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "CommitPtr.h"

class App;
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

	void 				SetApp(App *app);
	App* 				GetApp();

	virtual void 		Update(DeltaTime &delta);

protected:
	virtual Renderer*	CreateRenderer();
	virtual Scene* 		CreateDefaultScene();
	virtual void 		DrawScene();
	virtual void 		DispatchUpdate(DeltaTime &delta);

	Renderer 			*mRenderer;
	CommitPtr<Scene> 	mScene;

private:
	App 				*mApp;
};


#undef TRUTLE_HEADER