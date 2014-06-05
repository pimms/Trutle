#pragma once
#define TRUTLE_HEADER

#include "../../Trutle.h"
#include "InputState.h"

class App;

class EventHandler
{
public:
	EventHandler(App *app);
	void 				HandleEvents();
	bool 				ShouldQuit();

	const InputState* 	GetInputState();
	void 				ClearFreshFlags();

private:
	bool 				mShouldQuit;
	InputState 			mInputState;
	App 				*mApp;

	void ResizeWindow(int x, int y);
};


#undef TRUTLE_HEADER
