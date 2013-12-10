#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Geometry.h"

class Vec2;

/* Window
 *
 * Opens a window, and manages SDL and GL-related handles.
 */
class Window {
public:
					Window();
					~Window();
					
	bool 			CreateWindow(Vec2 resolution);
	void			FlipBuffer();

	void 			SetTitle(std::string title);

private:
	SDL_Window 		*mWindow;
	SDL_GLContext 	mGLContext;

	Vec2 			mResolution;
	bool 			mFullscreen;
};


#undef TRUTLE_HEADER