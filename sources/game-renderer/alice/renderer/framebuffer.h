#pragma once

#include <glad/glad.h>

namespace alice::renderer {
    class Framebuffer {
        unsigned int fbo_ = 0;
        unsigned int texture_ = 0;
        unsigned int rbo_ = 0;

    public:
        Framebuffer() {
            glGenFramebuffers(1, &fbo_);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

            glGenTextures(1, &texture_);
            glBindTexture(GL_TEXTURE_2D, texture_);

            glGenRenderbuffers(1, &rbo_);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
        }

        ~Framebuffer() {
            glDeleteFramebuffers(1, &fbo_);
            glDeleteTextures(1, &texture_);
            glDeleteRenderbuffers(1, &texture_);
        }

        void Texture(const int width, const int height) const {
            glBindTexture(GL_TEXTURE_2D, texture_);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);
        }

        void Bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
        }

        static void UnBind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        [[nodiscard]] unsigned int GetTexture() const { return texture_; }
    };
}
