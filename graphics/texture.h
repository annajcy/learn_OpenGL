#pragma once

#include "global/core.h"
#include "application/image.h"
#include <memory>

class Texture {
public:

    enum class Wrap_type {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };

    enum class Filter_type {
        LINEAR,
        NEAREST,
        LINEAR_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        NEAREST_MIPMAP_NEAREST,
    };

    enum class Filter {
        MIN, MAG
    };

    enum class Warp {
        S, T
    };

    constexpr GLenum warp_to_gl_enum(Warp type);
    constexpr GLenum filter_to_gl_enum(Filter type);
    constexpr GLenum wrap_type_to_gl_enum(Wrap_type wrap);
    constexpr GLenum filter_type_to_gl_enum(Filter_type filter);

private:
    GLuint m_texture_id{};
    std::shared_ptr<Image> m_image{};
    unsigned int m_unit{};
public:
    Texture(const std::shared_ptr<Image> &image, unsigned int unit = 0, bool set_default_warp_filter = true);
    ~Texture();

    void init(const std::shared_ptr<Image> &image, unsigned int unit = 0, bool set_default_warp_filter = true);
    void destroy();
    void set_wrap(Warp warp, Wrap_type wrap_type);
    void set_filter(Filter filter, Filter_type filter_type);
    
    void attach_texture();
    void detach_texture();

    [[nodiscard]] GLuint id() const;
    [[nodiscard]] unsigned int unit() const;
};