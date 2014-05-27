#pragma once

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64)
#	include "GL/glew.h"
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include "SDL/SDL.h"
#	include "SDL/SDL_main.h"
#	include "SDL/SDL_image.h"
#else 	// Some UNIX variant probably
#	include <GL/glew.h>
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
#include <list>
#include <fstream>
#include <string>



/* Struct used when updating
 * GameObjects.
 */
struct DeltaTime {
	/* The time since the last Update-call
	 * in seconds.
	 */
	float dt;
};



//Don't include Trutle files from other 
//Trutle files.
#ifndef TRUTLE_HEADER
#	include "core/App.h"
#	include "core/CommitPtr.h"
#	include "core/Controller.h"
#	include "core/Renderer.h"
#	include "core/Stack.h"
#	include "core/Geometry.h"
#	include "core/Window.h"
#	include "node/GameObject.h"
#	include "node/Layer.h"
#	include "node/Scene.h"
#	include "node/Component.h"
#endif
