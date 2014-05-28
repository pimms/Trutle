#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Window.h"
#include "event/EventHandler.h"
#include "Stack.h"
#include "CommitPtr.h"

class Renderer;
class Controller;
using std::string;


class App
{
public:
	App();
	virtual 				~App();

	void 					SetController(Controller *controller);
	Controller* 			GetController();
	Window* 				GetWindow();
	const InputState* 		GetInputState();

	bool 					Initialize(int argc, char *argv[]);
	int 					MainLoop();

protected:
	virtual std::string 	GetWindowTitle();
	virtual bool 			InitApplication(int argc, char **argv);
	virtual Controller* 	CreateDefaultController();

private:
	bool 					InitSDL();
	void 					InitController();

	Window 					mWindow;
	EventHandler 			mEventHandler;
	CommitPtr<Controller> 	mController;

	bool 					mInitialized;
};

#undef TRUTLE_HEADER
