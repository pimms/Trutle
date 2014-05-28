#include "Layer.h"


Layer::Layer()
{
	mScene = NULL;
}

void Layer::SetScene(Scene *scene)
{
	mScene = scene;
}

Layer* Layer::GetParentLayer()
{
	return this;
}

Scene* Layer::GetScene()
{
	if (GetParent()) {
		return GetParent()->GetScene();
	}

	return mScene;
}