#include <trutle/Trutle.h>


int main(int argc, char *argv[]) {
	App app;
	app.Initialize(argc, argv);

	
	Scene *scene = new Scene();
	app.GetController()->SetScene(scene);


	Layer *layer = new Layer();
	scene->AddLayer(layer);


	GameObject *ob = new GameObject();
	ob->Position() = Vec2(100.f, 100.f);
	ob->LoadTexture("helloworld.png");
	layer->AddChild(ob);

	GameObject *ob2 = new GameObject();
	ob2->Position() = Vec2(25.f, -30.f);
	ob2->LoadTexture("helloworld.png");
	ob->AddChild(ob2);

	return app.MainLoop();
}