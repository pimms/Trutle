#include "ResourceManager.h"
#include "Texture.h"


/***** Static Member Declaration *****/
std::map<std::string, Resource*> ResourceManager::sResources;


/***** Public Static Methods *****/
void ResourceManager::Purge()
{
	auto iter = sResources.begin();
	while (iter != sResources.end()) {
		if (iter->second->GetReferenceCount() != 0) {
			printf(	"[WARNING]: Resource '%s' purged "
			        "with %i active references\n",
			        iter->second->GetResourceName().c_str(),
			        iter->second->GetReferenceCount());
		}

		delete iter->second;
		iter++;
	}

	sResources.clear();
}

void ResourceManager::Clean()
{
	auto iter = sResources.begin();
	while (iter != sResources.end()) {
		if (iter->second->GetReferenceCount() <= 0) {
			delete iter->second;
			iter = sResources.erase(iter);
		} else {
			iter++;
		}
	}
}

Resource* ResourceManager::GetResource(	std::string file,
                                        Resource::Type type)
{
	Resource *resource = NULL;

	if (sResources.count(file)) {
		resource = sResources[file];
	} else {
		switch (type) {
		case Resource::TEXTURE:
			resource = CreateTexture(file);
			break;

		default:
			resource = NULL;
			break;
		}

		sResources[file] = resource;
	}

	return resource;
}


/***** Private Static Methods *****/
Texture* ResourceManager::CreateTexture(std::string file)
{
	Texture *tex = new Texture(file);

	if (!tex->Load()) {
		delete tex;
		return NULL;
	}

	printf("Texture '%s' loaded with ID %i\n",
	       file.c_str(), tex->GetTextureID());

	return tex;
}
