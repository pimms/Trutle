#include <trutle/Trutle.h>
#include <trutle/node/Component.h>


class TestComp : public Component {
public:
	float t;
	
	TestComp() {
		t = 0.f;
	}

	void Update(const DeltaTime &dt) {
		t += dt.dt;
		
		GameObject *parent = GetGameObject();
		parent->Position().x += dt.dt * 100.f;
		parent->Position().y = 100 + 60 * sinf(t);

		if (parent->Position().x >= 400.f)
			parent->Position().x = 100.f;
	}
};


int main(int argc, char *argv[]) 
{
	App app;
	app.Initialize(argc, argv);

	Controller *controller = new Controller();
	app.SetController(controller);

	Scene *scene = new Scene();
	controller->SetScene(scene);

	Layer *layer = new Layer();
	scene->AddLayer(layer);

	GameObject *go = new GameObject();
	go->LoadTexture("../helloworld/helloworld.png");
	AddComponent<TestComp>(go);

	layer->AddChild(go);
	
	return app.MainLoop();
}
