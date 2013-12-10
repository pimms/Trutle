#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"


class EventDispatcher {
public:
						EventDispatcher();
	void 				DispatchEvents();
	bool 				ShouldQuit();

private:
	bool 				mShouldQuit;
};


#undef TRUTLE_HEADER