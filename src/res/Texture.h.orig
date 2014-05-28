#pragma once
#define TRUTLE_HEADER

#include "Resource.h"
#include "../core/Geometry.h"


class Texture : public Resource {
public:
					Texture(std::string res);
	virtual 		~Texture();
	bool 			Load();

	void 			Bind();
	GLuint 			GetTextureID();
	Vec2 			GetDimensions();

protected:
	GLuint 			mTexId;
	Vec2 			mDimensions;
};


#undef TRUTLE_HEADER