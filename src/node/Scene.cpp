#include "Scene.h"


void Scene::AddLayer(Layer *layer) {
	mLayers.push_back(layer);
}

const LayerList& Scene::GetLayers() const {
	return mLayers;
}

void Scene::LoadContent() {
	// ..
}

void Scene::Update(const DeltaTime &delta) {
	// ..
}

