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


	T& Peek() {
		if (mObjects.size() == 0) {
			throw runtime_error("Stack underflow");
		}

		return mObjects.back();
	}

private:
	deque<T> mObjects;
};