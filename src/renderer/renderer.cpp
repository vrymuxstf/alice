#include "renderer.h"

namespace alice {
    void Renderer::Update() {
#ifdef OPENGL
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0, 0.5f, 1.0f);
#endif
        for (auto *renderer_object: render_object_list_) {
            renderer_object->Draw();
        }
    }

#ifdef OPENGL
    Renderer::Renderer(GLADloadproc load) {
        gladLoadGLLoader(load);
    }
#endif
}