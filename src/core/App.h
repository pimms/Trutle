#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Window.h"
#include "EventDispatcher.h"

class Renderer;
using std::string;


class App {
public:
							App();
	virtual 				~App();

	int 					Run(int argc, char *argv[]);

protected:
	virtual std::string 	GetWindowTitle();
	virtual bool 			InitApplication(int argc, char **argv);
	virtual Renderer*		CreateRenderer();

	Renderer 				*mRenderer;

private:
	bool 					Init();
	bool 					InitSDL();

	bool 					MainLoop();

	Window 					mWindow;
	EventDispatcher 		mEventDispatcher;
};

#undef TRUTLE_HEADER