#include "frame_buffer.h"

Frame_buffer::Frame_buffer(int width, int height) : m_width(width), m_height(height) {
    m_color_attachment = Texture::create_color_attachment(width, height);
    m_depth_stencil_attachment = Texture::create_depth_stencil_attachment(width, height);
    glGenFramebuffers(1, &m_fbo);
    
    attach();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_attachment->id(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil_attachment->id(), 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Frame buffer is not complete" << std::endl;
    }

    detach();
}

Frame_buffer::~Frame_buffer() {
    destroy();
}

void Frame_buffer::set_to_screen() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Frame_buffer::attach() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Frame_buffer::detach() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Frame_buffer::destroy() {
    glDeleteFramebuffers(1, &m_fbo);
}

std::shared_ptr<Texture>& Frame_buffer::color_attachment() {
    return m_color_attachment;
}

std::shared_ptr<Texture>& Frame_buffer::depth_stencil_attachment() {
    return m_depth_stencil_attachment;
}

int Frame_buffer::width() const {
    return m_width;
}

int Frame_buffer::height() const {
    return m_height;
}

unsigned int Frame_buffer::fbo() const {
    return m_fbo;
}
