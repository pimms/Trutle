#include "Resource.h"



Resource::Resource(std::string res)
{
	mType = UNDEFINED;
	mRefCount = 0;
	mResName = res;
}

Resource::~Resource()
{

}

std::string Resource::GetResourceName()
{
	return mResName;
}

int Resource::GetReferenceCount()
{
	return mRefCount;
}

void Resource::Retain()
{
	mRefCount++;
}

void Resource::Release()
{
	mRefCount--;
}