#include "EventDispatcher.h"


EventDispatcher::EventDispatcher() {
	mShouldQuit = false;
}

void EventDispatcher::DispatchEvents() {
	SDL_Event evt;

	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
			case SDL_QUIT:
				mShouldQuit = true;
				break;

			case SDL_KEYDOWN:	
				break;
			case SDL_KEYUP:
				break;

			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
		}
	}
}

bool EventDispatcher::ShouldQuit() {
	return mShouldQuit;
}