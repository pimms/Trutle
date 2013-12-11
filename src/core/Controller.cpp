#include "Controller.h"
#include "Renderer.h"
#include "Geometry.h"
#include "../node/Scene.h"
#include "../node/Layer.h"


Controller::Controller() {
	mScene = NULL;
	mRenderer = NULL;
}

Controller::~Controller() {
	if (mRenderer) {
		delete mRenderer;
	}
}

void Controller::LoadContent() {
	mRenderer = CreateRenderer();
	if (!mRenderer->Init(Vec2(640, 480))) {
		printf("Failed to initialize Renderer\n");
	}

	if (!mScene) {
		printf("[WARNING]: Controller has no Scene\n");
	}
}

void Controller::SetScene(Scene *scene) {
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



