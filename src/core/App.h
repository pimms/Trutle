#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Window.h"
#include "EventDispatcher.h"

class Renderer;
class Controller;
using std::string;


class App {
public:
							App();
	virtual 				~App();

	void 					SetController(Controller *controller);
	Controller* 			GetController();

	int 					Run(int argc, char *argv[]);

protected:
	virtual std::string 	GetWindowTitle();
	virtual bool 			InitApplication(int argc, char **argv);

private:
	bool 					Init();
	bool 					InitSDL();

	bool 					MainLoop();

	Window 					mWindow;
	EventDispatcher 		mEventDispatcher;
	Controller 				*mController;
};

#undef TRUTLE_HEADER