#include "Renderer.h"
#include "Log.h"
#include "../node/GameObject.h"
#include "../node/Scene.h"
#include "../node/Layer.h"
#include "../res/Texture.h"


/***** Static Public Methods *****/
bool Renderer::PrintOpenGLErrors(std::string context) {
	GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

    	std::string errStr = "OpenGL error (context='";
    	errStr += context + "'): ";

        switch (error) {
            case GL_INVALID_ENUM:
                    errStr += ("GL_INVALID_ENUM");
                    break;
            case GL_INVALID_VALUE:
                    errStr += ("GL_INVALID_VALUE");
					break;
            case GL_INVALID_OPERATION:
                    errStr += "GL_INVALID_OPERATION";
                    break;
            case GL_OUT_OF_MEMORY:
                    errStr += "GL_OUT_OF_MEMORY";
                    break;
            case GL_STACK_UNDERFLOW:
                    errStr += "GL_STACK_UNDERFLOW";
                    break;
            case GL_STACK_OVERFLOW:
                    errStr += "GL_STACK_OVERFLOW";
                    break;
            default:
                    errStr += "UNDEFINED GL ERROR";
        }

        Log::Error(errStr);

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

	Log::Info("Renderer initialized");
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

void Renderer::RenderTexture(Texture *tex, Rect clip, Vec2 pivot) {
	Rect fClip;

	fClip.x = clip.x / tex->GetDimensions().x;
	fClip.y = clip.y / tex->GetDimensions().y;
	fClip.w = clip.w / tex->GetDimensions().x;
	fClip.h = clip.h / tex->GetDimensions().y;

	// Adjust the clip rectangle based on the pivot point.
	// pivot={0.5,0.5} centers the texture on the clip position.
	Vec2 dim = tex->GetDimensions();
	clip.x -= dim.x * pivot.x;
	clip.y -= dim.y * pivot.y;


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