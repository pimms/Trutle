#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

/* CommitPtr
 *
 * ANY (!!) NON-NIL VALUE ASSIGNED TO A COMMITPTR WILL
 * BE DELETED BY THE OBJECT AUTOMATICALLY. BE CAREFUL!
 *
 *
 * Wrapper class around a single pointer, whose
 * value must change under controller circumstances.
 *
 * If a secondary value has been set, if will replace
 * the primary value after a call to Commit().
 *
 * In order to clear and delete the contents of a 
 * CommitPtr, assign it to NULL and commit it.
 *
 * CommitPtr<Foo> foo;
 * foo = new Foo();
 * foo.Commit();
 * 
 * // This will delete foo
 * foo = NULL;
 * foo.Commit();
 */
template<typename T>
class CommitPtr {
public:
	CommitPtr() {
		mPrimary = NULL;
		mSecondary = NULL;
		mSecondarySet = false;
	}

	~CommitPtr() {
		if (mPrimary) {
			delete mPrimary;
		}

		if (mSecondary) {
			delete mSecondary;
		}
	}

	bool Commit() {
		if (mSecondarySet) {
			mSecondarySet = false;

			if (mPrimary) {
				delete mPrimary;
			}

			mPrimary = mSecondary;
			return true;
		}
		return false;
	}

	void Set(T *t) {
		if (mSecondarySet && mSecondary) {
			delete mSecondary;
		}

		mSecondary = t;
		mSecondarySet = true;
	}

	T& operator* () {
        return *mPrimary;
    }

    T* operator-> () {    
        return mPrimary;
    }

    void operator=(T* t) {
    	Set(t);
    }

    explicit operator bool() const {
    	return mPrimary;
    }

    operator T*() {
    	return mPrimary;
    }

    operator T*() const {
    	return mPrimary;
    }

private:
	T* 	mPrimary;
	T*	mSecondary;
	bool mSecondarySet;
};


#undef TRUTLE_HEADER