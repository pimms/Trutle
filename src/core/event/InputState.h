#pragma once
#define TRUTLE_HEADER

#include "../../Trutle.h"


class InputState
{
public:
	InputState();

	void 			HandleKeyEvent(SDL_KeyboardEvent *evt);
	void 			InvalidateFreshBits();

	bool 			IsKeyDown(SDL_Keycode keycode) const;
	bool 			IsKeyFresh(SDL_Keycode keycode) const;

private:
	void 			OnKeyDown(SDL_KeyboardEvent *keyEvt);
	void 			OnKeyUp(SDL_KeyboardEvent *keyEvt);

	// Support up to 512 keys
	unsigned 		mKeyBits[16];
	unsigned 		mFreshKeyBits[16];
};

#undef TRUTLE_HEADER