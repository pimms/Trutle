#include "App.h"
#include "Renderer.h"
#include "Controller.h"
#include "Log.h"
#include "../res/ResourceManager.h"
#include "../node/GameObject.h"
#include <sstream>

using std::stringstream;


/***** Public Methods *****/
App::App()
{
	mController = NULL;
	mNextController = NULL;
	mInitialized = false;
	mQuit = false;
}

App::~App()
{
	if (mController)
		delete mController;
	if (mNextController)
		delete mNextController;
}

void App::SetController(Controller *controller)
{
	if (!controller) {
		Log::Debug("Attempted to set a NULL-Controller");
		return;
	}

	controller->SetApp(this);

	if (!mController) {
		mController = controller;
	} else {
		mNextController = controller;
	}
}

Controller* App::GetController()
{
	if (!mController) {
		SetController(CreateDefaultController());
	}

	return mController;
}

Window* App::GetWindow()
{
	return &mWindow;
}

const InputState* App::GetInputState()
{
	return mEventHandler.GetInputState();
}

bool App::Initialize(int argc, char *argv[])
{
	if (!InitSDL()) {
		Log::Error("SDL Initialization failed");
		return false;
	}

	if (!mWindow.CreateWindow(Vec2(1280.f, 720.f))) {
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

int App::MainLoop()
{
	if (!mInitialized) {
		Log::Error("App not initialized");
		return 1;
	}

	InitController();

	DeltaTime deltaTime = { 1.f / 60.f };

	while (!mQuit && !mEventHandler.ShouldQuit()) {
		__ComponentManager::ExecuteCommands();
		mEventHandler.ClearFreshFlags();

		mEventHandler.HandleEvents();
		mController->Update(deltaTime);
		mWindow.FlipBuffer();

		if (mNextController) {
			delete mController;
			mController = mNextController;
			mNextController = NULL;
			mController->LoadContent();
		}

		mController->SceneTransition();
		Renderer::PrintOpenGLErrors("Post-frame");
	}

	return 0;
}

void App::Quit()
{
	mQuit = true;
}


/***** Protected Methods *****/
string App::GetWindowTitle()
{
	return "Trutle Application";
}

bool App::InitApplication(int argc, char *argv[])
{
	return true;
}

Controller* App::CreateDefaultController()
{
	return new Controller();
}


/***** Private Methods *****/
bool App::InitSDL()
{
	int status = 0;

	status = SDL_Init(SDL_INIT_EVERYTHING);
	if (status != 0) {
		stringstream ss;
		ss << "SDL_Init() returned error code: " << status;
		Log::Warning(ss.str());

		if (strcmp(SDL_GetError(), "Unknown touch device") != 0) {
			Log::Error((std::string)"SDL_Init() error: "
			           +SDL_GetError());
			return false;
		} else {
			Log::Info("This error is trivial and occurs frequently. Ignoring.");
		}
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	return true;
}

void App::InitController()
{
	if (!mController) {
		mController = new Controller();
	}

	mController->LoadContent();
	mController->SceneTransition();
}
