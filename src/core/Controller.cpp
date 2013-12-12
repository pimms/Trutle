#include "Controller.h"
#include "Renderer.h"
#include "Geometry.h"
#include "Log.h"
#include "../node/Scene.h"
#include "../node/Layer.h"


Controller::Controller() {
	mScene = NULL;
	mRenderer = NULL;
	mApp = NULL;

	mScene.Commit();
}

Controller::~Controller() {
	if (mRenderer) {
		delete mRenderer;
	}
}

void Controller::LoadContent() {
	mRenderer = CreateRenderer();
	if (!mRenderer->Init(Vec2(640, 480))) {
		Log::Error("Failed to initialize Renderer");
	}

	if (!mScene) {
		Log::Verbose("Controller has no Scene");
	}
}

void Controller::SetScene(Scene *scene) {
	scene->SetController(this);
	mScene = scene;
}

Scene* Controller::GetScene() {
	return mScene;
}

void Controller::SceneTransition() {
	if (mScene.Commit()) {
		mScene->LoadContent();
	}
}

void Controller::SetApp(App *app) {
	mApp = app;
}

App* Controller::GetApp() {
	return mApp;
}

void Controller::Update(DeltaTime &delta) {
	DispatchUpdate(delta);
	DrawScene();
}


/***** Protected Methods *****/
Renderer* Controller::CreateRenderer() {
	return new Renderer();
}

Scene* Controller::CreateDefaultScene() {
	return new Scene();
}

void Controller::DrawScene() {
	if (mScene) {
		mRenderer->RenderFrame(mScene);
	}
}

void Controller::DispatchUpdate(DeltaTime &delta) {
	if (!mScene) {
		return;
	}

	LayerList *layers = &mScene->GetLayers();
	LayerIter liter = layers->begin();

	mScene->Update(delta);
	
	while (liter != layers->end()) {
		(*liter)->UpdateSelfAndChildren(delta);
		liter++;
	}
}



