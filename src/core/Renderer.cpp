#include "Renderer.h"
#include "../node/GameObject.h"
#include "../node/Scene.h"
#include "../node/Layer.h"
#include "../res/Texture.h"


/***** Static Public Methods *****/
bool Renderer::PrintOpenGLErrors(std::string context) {
	GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL error (context='%s'): ", context.c_str());

        switch (error) {
            case GL_INVALID_ENUM:
                    printf("GL_INVALID_ENUM");
                    break;
            case GL_INVALID_VALUE:
                    printf("GL_INVALID_VALUE");
					break;
            case GL_INVALID_OPERATION:
                    printf("GL_INVALID_OPERATION");
                    break;
            case GL_OUT_OF_MEMORY:
                    printf("GL_OUT_OF_MEMORY");
                    break;
            case GL_STACK_UNDERFLOW:
                    printf("GL_STACK_UNDERFLOW");
                    break;
            case GL_STACK_OVERFLOW:
                    printf("GL_STACK_OVERFLOW");
                    break;
            default:
                    printf("UNDEFINED GL ERROR");
        }

        printf(" (%x)\n", error);
		return false;
    }

	return true;
}


/***** Public Methods *****/
Renderer::~Renderer() {

}

bool Renderer::Init(Vec2 coordBounds) {
	glClearColor(0.1f, 0.1f, 0.1f ,1.f);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, coordBounds.x, 0.0, coordBounds.y);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glewInit();
	if (error != GL_NO_ERROR) {
		return false;
	}

	printf("[Renderer Intialized]\n");
	return true;
}

void Renderer::RenderFrame(Scene *scene) {
	glClear(GL_COLOR_BUFFER_BIT);

	LayerIter iter = scene->GetLayers().begin();
	while (iter != scene->GetLayers().end()) {
		(*iter)->Render(this);
		iter++;
	}
}

void Renderer::PushTransform() {
	glPushMatrix();
}

void Renderer::ApplyTransform(GameObject *object) {
	Vec2 v = object->Position();
	Vec2 s = object->Scale();

	glTranslatef(v.x, v.y, 0.f);
	glRotatef(object->Rotation(), 0.f, 0.f, 1.f);
	glScalef(s.x, s.y, 1.f);
}

void Renderer::PopTransform() {
	glPopMatrix();
}

void Renderer::RenderTexture(Texture *tex, Rect clip) {
	Rect fClip;

	fClip.x = clip.x / tex->GetDimensions().x;
	fClip.y = clip.y / tex->GetDimensions().y;
	fClip.w = clip.w / tex->GetDimensions().x;
	fClip.h = clip.h / tex->GetDimensions().y;

	float vertices[8] = {
		clip.x, 			clip.y,
		clip.x + clip.w,	clip.y,
		clip.x + clip.w, 	clip.y + clip.h,
		clip.x, 			clip.y + clip.h,
	};

	float texcoord[8] = {
		fClip.x, 			fClip.y + fClip.h,
		fClip.x + fClip.w,	fClip.y + fClip.h,
		fClip.x + fClip.w, 	fClip.y,
		fClip.x, 			fClip.y,
	};


	printf("\n---------------->\n");
	for (int i=0; i<8; i++) printf("%0.2f  ", vertices[i]);	printf("\n");
	for (int i=0; i<8; i++) printf("%0.2f  ", texcoord[i]);	printf("\n");

	glEnable(GL_TEXTURE_2D);
	tex->Bind();

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}