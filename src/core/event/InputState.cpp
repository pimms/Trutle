#include "InputState.h"
#include "../Log.h"


InputState::InputState() {
	for (int i=0; i<16; i++) {
		mKeyBits[i] = 0;
		mFreshKeyBits[i] = 0;
	}
}

void InputState::HandleKeyEvent(SDL_KeyboardEvent *evt) {
	if (evt->type == SDL_KEYDOWN) {
		OnKeyDown(evt);
	} else if (evt->type == SDL_KEYUP) {
		OnKeyUp(evt);
	}
}

void InputState::InvalidateFreshBits() {
	for (int i=0; i<16; i++) {
		mFreshKeyBits[i] = 0;
	}
}

bool InputState::IsKeyDown(SDL_Keycode key) const {
	if (key < 512) {
		int index = key / 32;
		int bit = key % 32;

		return mKeyBits[index] & (1<<bit);
	}

	Log::Verbose("InputState::IsKeyDown(): Invalid param");
	return false;
}

bool InputState::IsKeyFresh(SDL_Keycode key) const {
	if (key < 512) {
		int index = key / 32;
		int bit = key % 32;

		return mFreshKeyBits[index] & (1<<bit);	
	}

	Log::Verbose("InputState::IsKeyFresh(): Invalid param");
	return false;
}


/***** Private Methods *****/
void InputState::OnKeyUp(SDL_KeyboardEvent *keyEvt) {
	if (keyEvt->keysym.sym < 512) {
		int index = keyEvt->keysym.sym / 32;
		int bit = keyEvt->keysym.sym % 32;

		// Unflag the key
		mKeyBits[index] &= ~(1<<bit);
	} else {
		Log::Verbose("InputState::OnKeyUp(): Invalid param");
	}
}

void InputState::OnKeyDown(SDL_KeyboardEvent *keyEvt) {
	if (keyEvt->keysym.sym < 512) {
		int index = keyEvt->keysym.sym / 32;
		int bit = keyEvt->keysym.sym % 32;

		// The key is fresh if it was not already being
		// pressed.
		if ((mKeyBits[index] & (1<<bit)) == 0) {
			mFreshKeyBits[index] |= (1<<bit);
		}

		// Flag the key
		mKeyBits[index] |= (1<<bit);	
	} else {
		Log::Verbose("InputState::OnKeyDown(): Invalid param");
	}
}