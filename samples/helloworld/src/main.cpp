#include <trutle/Trutle.h>


class Fuck : public GameObject {
public:
	void Update(const DeltaTime &dt) {
		//mRotation += 1.f;
	}
};


int main(int argc, char *argv[]) {
	App app;
	app.Initialize(argc, argv);

	
	Scene *scene = new Scene();
	app.GetController()->SetScene(scene);


	Layer *layer = new Layer();
	scene->AddLayer(layer);


	GameObject *ob = new Fuck();
	ob->Position() = Vec2(100.f, 100.f);
	ob->LoadTexture("helloworld.png");
	layer->AddChild(ob);

	GameObject *ob2 = new Fuck();
	ob2->Position() = Vec2(25.f, -30.f);
	ob2->LoadTexture("helloworld.png");
	ob->AddChild(ob2);

	return app.MainLoop();
}