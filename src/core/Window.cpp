#include "Window.h"
#include "Geometry.h"
#include "Log.h"


Window::Window() {
	mWindow = NULL;
	mGLContext = NULL;
}

Window::~Window() {
	if (mWindow) {
		SDL_DestroyWindow(mWindow);
	}

	if (mGLContext) {
		SDL_GL_DeleteContext(mGLContext);
	}

	SDL_Quit();
}

bool Window::CreateWindow(Vec2 resolution) {
	mWindow = SDL_CreateWindow(
		"Trutle",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		resolution.x,
		resolution.y,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!mWindow) {
		Log::Error((std::string)"Failed to create window: " +
								SDL_GetError());
		return false;
	}

	mGLContext = SDL_GL_CreateContext(mWindow);
	if (!mGLContext) {
		Log::Error((std::string)"Failed to create GL context: " +
								SDL_GetError());
		return false;
	}
	
	return true;
}

void Window::FlipBuffer() {
	SDL_GL_SwapWindow(mWindow);
}

void Window::SetTitle(std::string title) {
	SDL_SetWindowTitle(mWindow, title.c_str());
}