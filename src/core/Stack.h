#pragma once

#include <deque>
#include <stdexcept>

using namespace std;


/* Stack
 *
 * Simple stack implementation. 
 */
template<typename T>
class Stack {
public:
	void Push(T object) {
		mObjects.push_back(object);
	}

	void Pop() {
		if (mObjects.size() == 0) {
			throw runtime_error("Stack underflow");
		}

		T object = mObjects.back();
		mObjects.pop_back();
	}


	virtual T& Peek() {
		if (mObjects.size() == 0) {
			throw runtime_error("Stack underflow");
		}

		return mObjects.back();
	}

	int Size() {
		return mObjects.size();
	}

private:
	deque<T> mObjects;
};


/* CommitStack
 *
 * The Peek() method is overriden, and only returns
 * the last object when Commit() has been called.
 * 
 * 
 */
template<typename T>
class CommitStack : public Stack<T> {
public:
	void Commit() {
		mSafeElem = Stack<T>::Peek();
	}

	virtual T& Peek() {
		return mSafeElem;
	}

private:
	T *mSafeElem;
};