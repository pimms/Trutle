#pragma once

#define TRUTLE_HEADER

#ifdef _WIN32
	#include <Trutle.h>
#else
	#include "../Trutle.h"
#endif

#include "Geometry.h"

class RenderTexture {
public:
	RenderTexture(Vec2 resolution);
	~RenderTexture();

	void BindFBO() const;
	void UnbindFBO() const;
	void BindTex() const;
	void UnbindTex() const;
	GLuint GetTex() const;
	Vec2 GetResolution() const;

private:
	Vec2 _res;
	GLuint _fbo;
	GLuint _rbo;
	GLuint _tex;
};


#undef TRUTLE_HEADER
