#include "Controller.h"
#include "Renderer.h"
#include "../node/Scene.h"


Controller::Controller() {
	mScene = NULL;
	mRenderer = NULL;
}

Controller::~Controller() {
	if (mScene) {
		delete mScene;
	}

	if (mRenderer) {
		delete mRenderer;
	}
}

void Controller::LoadContent() {
	mRenderer = CreateRenderer();
}

void Controller::SetScene(Scene *scene) {
	if (mNewScene) {
		delete mNewScene;
	}

	mNewScene = scene;
}

void Controller::SceneTransition() {
	if (mNewScene) {
		if (mScene) {
			delete mScene;
		}

		mScene = mNewScene;
		mNewScene = NULL;
	}
}

void Controller::Update(const DeltaTime &delta) {
	DrawScene();
}


/***** Protected Methods *****/
Renderer* Controller::CreateRenderer() {
	return new Renderer();
}

void Controller::DrawScene() {
	mRenderer->RenderFrame(mScene);
}