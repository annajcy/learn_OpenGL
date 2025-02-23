#include "frame_buffer.h"

void Frame_buffer::attach() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Frame_buffer::detach() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Frame_buffer::set_to_screen() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

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

void Frame_buffer::destroy() {
    glDeleteFramebuffers(1, &m_fbo);
}

Frame_buffer::~Frame_buffer() {
    destroy();
}
