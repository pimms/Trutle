#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"


class Resource
{
public:
	enum Type {
		UNDEFINED,
		TEXTURE,
		AUDIO,
	};

	Resource(std::string res);
	virtual 			~Resource();

	virtual bool 		Load() = 0;

	std::string 		GetResourceName();
	int 				GetReferenceCount();

	void 				Retain();
	void 				Release();

protected:
	std::string 		mResName;
	Type 				mType;

private:
	int 				mRefCount;
};

#undef TRUTLE_HEADER