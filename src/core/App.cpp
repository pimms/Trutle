#include "App.h"
#include "Renderer.h"
#include "Controller.h"


/***** Public Methods *****/
App::App() {
	mController = NULL;
}

App::~App() {

}

void App::SetController(Controller *controller) {
	mController = controller;
}

Controller* App::GetController() {
	if (!mController) {
		mController = new Controller();
		mController.Commit();
	}

	return mController;
}

int App::Run(int argc, char *argv[]) {
	if (!Init()) {
		printf("Stock initalization failed\n");
		return -2;
	}

	if (!InitApplication(argc, argv)) {
		printf("Custom initialization failed\n");
		return -3;
	}

	if (!mController) {
		mController = new Controller();
		mController.Commit();
	}

	if (!MainLoop()) {
		printf("Game loop terminated\n");
		return -4;
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
bool App::Init() {
	if (!InitSDL()) {
		printf("SDL Initialization failed\n");
		return false;
	}
	
	if (!mWindow.CreateWindow(Vec2(640, 480))) {
		printf("Failed to create window\n");
		return false;
	}

	mWindow.SetTitle(GetWindowTitle());

	return true;
}

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

bool App::MainLoop() {
	DeltaTime deltaTime = { 0.0016f };

	while (!mEventDispatcher.ShouldQuit()) {
		mEventDispatcher.DispatchEvents();
		mController->Update(deltaTime);
		mWindow.FlipBuffer();

		if (mController.Commit()) {
			mController->LoadContent();
		}
	}

	return true;
}
