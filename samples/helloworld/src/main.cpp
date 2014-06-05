#include <trutle/Trutle.h>


class TComponent : public Component {
public:
	void Update(const DeltaTime &dt)
	{
		const InputState *in = GetGameObject()->GetInputState();
		printf("Mouse pos: %g %g\n", in->GetMousePosition().x, in->GetMousePosition().y);
	}
};


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
	ob->Pivot() = Vec2(0.f, 0.f);
	layer->AddChild(ob);
	
	// The second image is not moved by position, but by 
	// Pivot-modification. 
	GameObject *ob2 = new GameObject();
	AddComponent<TComponent>(ob2);
	ob2->Position() = Vec2(0.f, 0.f);
	ob2->LoadTexture("helloworld.png");
	ob2->Pivot() = Vec2(-0.1f, 0.1f);
	ob->AddChild(ob2);

	return app.MainLoop();
}
