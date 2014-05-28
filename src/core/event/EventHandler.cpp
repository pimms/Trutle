#include "EventHandler.h"


EventHandler::EventHandler()
{
	mShouldQuit = false;
}

void EventHandler::HandleEvents()
{
	SDL_Event evt;

	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			mShouldQuit = true;
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			mInputState.HandleKeyEvent(&evt.key);
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

bool EventHandler::ShouldQuit()
{
	return mShouldQuit;
}

const InputState* EventHandler::GetInputState()
{
	return &mInputState;
}

void EventHandler::ClearFreshFlags()
{
	mInputState.InvalidateFreshBits();
}