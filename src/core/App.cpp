#include "App.h"
#include "Renderer.h"


App::App() {
	mRenderer = NULL;
}

App::~App() {
	if (mRenderer) {
		delete mRenderer;
	}
}

int App::Run(int argc, char *argv[]) {
	if (!mWindow.CreateWindow()) {
		return -1;
	}

	if (!Init()) {
		return -2;
	}

	if (!InitApplication(argc, argv)) {
		return -3;
	}

	if (!MainLoop()) {
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

Renderer* App::CreateRenderer() {
	return new Renderer();
}


/***** Private Methods *****/
bool App::Init() {
	if (!mWindow.CreateWindow()) {
		return false;
	}
	mWindow.SetTitle(GetWindowTitle());

	if (!InitSDL()) {
		return false;
	}

	return true;
}

bool App::InitSDL() {
	if (!SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	return true;
}

bool App::MainLoop() {
	while (!mEventDispatcher.ShouldQuit()) {
		mEventDispatcher.DispatchEvents();
		mRenderer->RenderFrame(NULL);
	}

	return true;
}