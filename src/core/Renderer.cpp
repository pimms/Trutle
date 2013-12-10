#include "Renderer.h"
#include "Vec2.h"


Renderer::~Renderer() {

}

bool Init(Vec2 coordBounds) {
	glClearColor(0.f, 0.f, 0.f ,1.f);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, coordBounds.x, 0.0, coordBounds.y);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return true;
}

void RenderFrame(Scene *scene) {
	glClear(GL_COLOR_BUFFER_BIT);
}