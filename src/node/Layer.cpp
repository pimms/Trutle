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

Vec2 Layer::WorldPosition()
{
	// Don't take the layers position into account
	return Vec2(0.f, 0.f);
}

float Layer::WorldRotation()
{
	return 0.f;
}

Scene* Layer::GetScene()
{
	if (GetParent()) {
		return GetParent()->GetScene();
	}

	return mScene;
}
