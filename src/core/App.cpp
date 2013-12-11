#include "App.h"
#include "Renderer.h"
#include "Controller.h"
#include "../res/ResourceManager.h"


/***** Public Methods *****/
App::App() {
	mController = NULL;
	mInitialized = false;
}

App::~App() {

}

void App::SetController(Controller *controller) {
	mController = controller;

	if (!mController) {
		mController.Commit();
	}
}

Controller* App::GetController() {
	if (!mController) {
		mController = new Controller();
		mController.Commit();
	}

	return mController;
}

Window* App::GetWindow() {
	return &mWindow;
}

bool App::Initialize(int argc, char *argv[]) {
	if (!InitSDL()) {
		printf("SDL Initialization failed\n");
		return false;
	}
	
	if (!mWindow.CreateWindow(Vec2(640, 480))) {
		printf("Failed to create window\n");
		return false;
	}
	mWindow.SetTitle(GetWindowTitle());

	if (!InitApplication(argc, argv)) {
		printf("Custom initialization failed\n");
		return false;
	}

	mInitialized = true;
	return true;
}

int App::MainLoop() {
	if (!mInitialized) {
		printf("[ERROR]: App not initialized\n");
		return 1;
	}

	FinalSetup();

	DeltaTime deltaTime = { 0.0016f };

	while (!mEventDispatcher.ShouldQuit()) {
		mEventDispatcher.DispatchEvents();
		mController->Update(deltaTime);
		mWindow.FlipBuffer();

		if (mController.Commit()) {
			mController->LoadContent();
		}

		mController->SceneTransition();
		Renderer::PrintOpenGLErrors("Post-frame");
	}

	return 0;
}


/***** Protected Methods *****/
string App::GetWindowTitle() {
	return "Trutle Application";
}

bool App::InitApplication(int argc, char *argv[]) {
	return true;
}


/***** Private Methods *****/
bool App::InitSDL() {
	if (!SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init() error: \n%s\n", SDL_GetError());

		/* Like I give a fuck */
		if (strcmp(SDL_GetError(), "Unknown touch device") != 0) {
			return false;
		}
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	return true;
}

void App::FinalSetup() {
	if (!mController) {
		mController = new Controller();
		mController.Commit();
	}

	mController->LoadContent();
	mController->SceneTransition();
}