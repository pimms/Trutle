#include "Scene.h"
#include "Layer.h"
#include "../core/Controller.h"
#include "../core/App.h"


Scene::~Scene() {
	LayerIter iter = mLayers.begin();
	while (iter != mLayers.end()) {
		delete *iter;
		iter++;
	}

	mController = NULL;
}

void Scene::AddLayer(Layer *layer) {
	layer->SetScene(this);
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

void Scene::SetController(Controller *controller) {
	mController = controller;
}

Controller* Scene::GetController() {
	return mController;
}

App* Scene::GetApp() {
	return GetController()->GetApp();
}