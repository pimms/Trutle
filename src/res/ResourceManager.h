#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"
#include "Resource.h"

class Texture;


class ResourceManager
{
public:
	/* Remove all Resources */
	static void 		Purge();

	/* Remove unreferenced Resources */
	static void 		Clean();

	/* Get a resource of a specific type. DOES NOT
	 * RETAIN THE RESOURCE.
	 */
	static Resource*	GetResource(std::string, Resource::Type t);


private:
	static Texture* 	CreateTexture(std::string file);

	static std::map<std::string, Resource*> sResources;
};

#undef TRUTLE_HEADER