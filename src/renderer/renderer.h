#pragma once

#ifdef OPENGL
#include <glad/glad.h>
#elif VULKAN
#include <vulkan/vulkan.hpp>
#endif

#include "object_list.h"

#include "render_object.h"

namespace alice {
    class Renderer {
        ObjectList<RenderObject> render_object_list_;
    public:
#ifdef OPENGL
        explicit Renderer(GLADloadproc load);
#endif

        void Update();

        inline ObjectList<RenderObject> &GetRenderObjectList() { return render_object_list_; }
    };
}