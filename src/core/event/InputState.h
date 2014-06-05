#pragma once
#define TRUTLE_HEADER

#include "../../Trutle.h"
#include "../Geometry.h"


class InputState
{
public:
	InputState();

	void 			HandleKeyEvent(SDL_KeyboardEvent *evt);
	void 			HandleMouseEvent(SDL_MouseButtonEvent *evt);
	void 			HandleMouseEvent(SDL_MouseMotionEvent *evt);
	void 			InvalidateFreshBits();

	bool 			IsKeyDown(SDL_Keycode keycode) const;
	bool 			IsKeyFresh(SDL_Keycode keycode) const;

	bool 			IsMouseKeyDown(Uint8 key) const;
	bool 			IsMouseKeyFresh(Uint8 key) const;
	
	Vec2 			GetMousePosition() const;

private:
	void 			OnKeyDown(SDL_KeyboardEvent *keyEvt);
	void 			OnKeyUp(SDL_KeyboardEvent *keyEvt);

	// Support up to 512 keys
	unsigned 		mKeyBits[16];
	unsigned 		mFreshKeyBits[16];

	unsigned 		mMouseBits[2];
	unsigned 		mFreshMouseBits[2];

	Vec2 			mMousePos;
};

#undef TRUTLE_HEADER
