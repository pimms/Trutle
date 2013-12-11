#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Window.h"
#include "EventDispatcher.h"
#include "Stack.h"
#include "CommitPtr.h"

class Renderer;
class Controller;
using std::string;


class App {
public:
							App();
	virtual 				~App();

	void 					SetController(Controller *controller);
	Controller* 			GetController();
	Window* 				GetWindow();

	bool 					Initialize(int argc, char *argv[]);
	int 					MainLoop();

protected:
	virtual std::string 	GetWindowTitle();
	virtual bool 			InitApplication(int argc, char **argv);

private:
	bool 					InitSDL();
	void 					FinalSetup();

	Window 					mWindow;
	EventDispatcher 		mEventDispatcher;
	CommitPtr<Controller> 	mController;

	bool 					mInitialized;
};

#undef TRUTLE_HEADER