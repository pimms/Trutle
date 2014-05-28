#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class App;
class Layer;
class Controller;

typedef std::list<Layer*> 	LayerList;
typedef LayerList::iterator LayerIter;


class Scene
{
public:
	virtual 			~Scene();
	void 				AddLayer(Layer *layer);
	LayerList& 			GetLayers();

	virtual void 		LoadContent();
	virtual void 		Update(const DeltaTime &delta);

	void 				SetController(Controller *controller);
	Controller* 		GetController();
	App* 				GetApp();

protected:
	std::list<Layer*> 	mLayers;

private:
	Controller 			*mController;
};


#undef TRUTLE_HEADER