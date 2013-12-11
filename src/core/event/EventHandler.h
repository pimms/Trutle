#pragma once
#define TRUTLE_HEADER

#include "../../Trutle.h"
#include "InputState.h"


class EventHandler {
public:
						EventHandler();
	void 				HandleEvents();
	bool 				ShouldQuit();

	const InputState* 	GetInputState();

private:
	bool 				mShouldQuit;

	InputState 			mInputState;
};


#undef TRUTLE_HEADER