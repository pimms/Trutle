#include "EventHandler.h"
#include "../Window.h"
#include "../App.h"


EventHandler::EventHandler(App *app)
	:	mApp(app)
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
			mInputState.HandleMouseEvent(&evt.motion);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			mInputState.HandleMouseEvent(&evt.button);
			break;

		case SDL_WINDOWEVENT:
			switch (evt.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				ResizeWindow(evt.window.data1, evt.window.data2);
				break;
			}
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


void EventHandler::ResizeWindow(int x, int y)
{
	Window *window = mApp->GetWindow();
	window->ResizeContext(Vec2(x, y));
}
