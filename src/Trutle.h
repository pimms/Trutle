#pragma once

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64)
#	include "GL/glew.h"
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include "SDL/SDL.h"
#	include "SDL/SDL_main.h"
#	include "SDL/SDL_image.h"
#else 	// Assume Unix
#	include <GL/glew.h>
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_image.h>
#	include <unistd.h>
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <deque>
#include <fstream>
#include <string>

/* Don't include Trutle files from other 
 * Trutle files.
 */
#ifndef TRUTLE_HEADER
#	include "core/App.h"
#	include "core/Window.h"
#	include "core/Vec2.h"
#	include "core/Renderer.h"
#endif