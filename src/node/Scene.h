#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class Layer;

typedef std::list<Layer*> 	LayerList;
typedef LayerList::iterator LayerIter;


class Scene {
public:
	virtual 			~Scene();
	void 				AddLayer(Layer *layer);
	LayerList& 			GetLayers();

	virtual void 		LoadContent();
	virtual void 		Update(const DeltaTime &delta);

protected:
	std::list<Layer*> 	mLayers;

private:
	
};


#undef TRUTLE_HEADER