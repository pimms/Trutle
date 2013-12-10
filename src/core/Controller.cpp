#include "Controller.h"
#include "Renderer.h"
#include "../node/Scene.h"
#include "Vec2.h"


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
		mScene = CreateDefaultScene();
		mScene.Commit();
	}
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

Scene* Controller::CreateDefaultScene() {
	return new Scene();
}

void Controller::DrawScene() {
	if (mScene) {
		mRenderer->RenderFrame(mScene);
	} else {
		printf("Controller has no Scene\n");
	}
}