#pragma once

#include "global/core.h"
#include "graphics/texture.h"

class Frame_buffer
{
private:

    unsigned int m_fbo{};
    int m_width{};
    int m_height{};

    std::shared_ptr<Texture> m_color_attachment{};
    std::shared_ptr<Texture> m_depth_stencil_attachment{};

public:

    Frame_buffer(int width, int height);
    ~Frame_buffer();

    static void set_to_screen();

    void attach();
    void detach();
    void destroy();

    std::shared_ptr<Texture>& color_attachment() {
        return m_color_attachment;
    }

    std::shared_ptr<Texture>& depth_stencil_attachment() {
        return m_depth_stencil_attachment;
    }

    [[nodiscard]] int width() const {
        return m_width;
    }

    [[nodiscard]] int height() const {
        return m_height;
    }

    [[nodiscard]] unsigned int fbo() const {
        return m_fbo;
    }
    
};
