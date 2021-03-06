#include "Texture.h"
#include "../core/Renderer.h"
#include "../core/Log.h"


Texture::Texture(std::string res) : Resource(res)
{
	mTexId = 0;
}

Texture::~Texture()
{
	if (mTexId != 0) {
		glDeleteTextures(1, &mTexId);
	}
}

bool Texture::Load()
{
	if (mResName.length() == 0) {
		return false;
	}

	SDL_Surface *surface = IMG_Load(mResName.c_str());
	if (!surface) {
		Log::Error("Failed to load texture:" +  mResName
		           + " - SDL Error: " + SDL_GetError());
		return false;
	}

	mDimensions.x = surface->w;
	mDimensions.y = surface->h;

	/* Figure out the format of the data.
	 * It is assumed that RGB[A] is the only valid order of colors,
	 * and that only 3 or 4 bytes per pixel (RGB or RGBA) are allowed.
	 */
	int elemCount = surface->format->BytesPerPixel;
	GLenum colorFormat = (elemCount == 3) ? GL_RGB : GL_RGBA;

	glEnable(GL_TEXTURE_2D);

	// Generate the texture
	glGenTextures(1, &mTexId);
	if (mTexId == 0) {
		Renderer::PrintOpenGLErrors("texture load failed");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, mTexId);

	// Pass it our data
	glTexImage2D(GL_TEXTURE_2D, 0, elemCount, surface->w, surface->h, 0,
	             colorFormat, GL_UNSIGNED_BYTE, surface->pixels);

	// LINEAR filtering, repeating
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
	SDL_FreeSurface(surface);
	return true;
}

void Texture::Bind()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexId);
}

GLuint Texture::GetTextureID()
{
	return mTexId;
}

Vec2 Texture::GetDimensions()
{
	return mDimensions;
}
