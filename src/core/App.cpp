#include "App.h"
#include "Renderer.h"
#include "Controller.h"
#include "Log.h"
#include "../res/ResourceManager.h"
#include "../node/GameObject.h"


/***** Public Methods *****/
App::App() {
	mController = NULL;
	mInitialized = false;

	mController.Commit();
}

App::~App() {

}

void App::SetController(Controller *controller) {
	if (controller) {
		controller->SetApp(this);
	}

	mController = controller;

	if (!mController) {
		mController.Commit();
	}
}

Controller* App::GetController() {
	if (!mController) {
		SetController(CreateDefaultController());
	}

	return mController;
}

Window* App::GetWindow() {
	return &mWindow;
}

const InputState* App::GetInputState() {
	return mEventHandler.GetInputState();
}

bool App::Initialize(int argc, char *argv[]) {
	if (!InitSDL()) {
		Log::Error("SDL Initialization failed");
		return false;
	}
	
	if (!mWindow.CreateWindow(Vec2(640, 480))) {
		printf("Failed to create window\n");
		return false;
	}
	mWindow.SetTitle(GetWindowTitle());

	if (!InitApplication(argc, argv)) {
		Log::Error("Custom initialization failed");
		return false;
	}

	mInitialized = true;
	return true;
}

int App::MainLoop() {
	if (!mInitialized) {
		Log::Error("App not initialized");
		return 1;
	}

	FinalSetup();

	DeltaTime deltaTime = { 1.f / 60.f };

	while (!mEventHandler.ShouldQuit()) {
		__ComponentManager::ExecuteCommands();
		mEventHandler.ClearFreshFlags();

		mEventHandler.HandleEvents();
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

Controller* App::CreateDefaultController() {
	return new Controller();
}


/***** Private Methods *****/
bool App::InitSDL() {
	if (!SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		if (strcmp(SDL_GetError(), "Unknown touch device") != 0) {
			Log::Error((std::string)"SDL_Init() error: "
									+SDL_GetError());
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