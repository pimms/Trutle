#include "Scene.h"
#include "Layer.h"


Scene::~Scene() {
	LayerIter iter = mLayers.begin();
	while (iter != mLayers.end()) {
		delete *iter;
		iter++;
	}
}

void Scene::AddLayer(Layer *layer) {
	mLayers.push_back(layer);
}

LayerList& Scene::GetLayers() {
	return mLayers;
}

void Scene::LoadContent() {
	// ..
}

void Scene::Update(const DeltaTime &delta) {
	// ..
}

