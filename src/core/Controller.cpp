#include "Controller.h"
#include "Renderer.h"
#include "../node/Scene.h"


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
}

void Controller::SetScene(Scene *scene) {
	mScene = scene;

	// This only makes sense because mScene is 
	// a CommitPtr.
	if (!mScene) {
		mScene.Commit();
	}
}

Scene* Controller::GetScene() {
	return mScene;
}

void Controller::SceneTransition() {
	mScene.Commit();
}

void Controller::Update(const DeltaTime &delta) {
	DrawScene();
}


/***** Protected Methods *****/
Renderer* Controller::CreateRenderer() {
	return new Renderer();
}

void Controller::DrawScene() {
	if (mScene) {
		mRenderer->RenderFrame(mScene);
	}
}