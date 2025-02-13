#include "texture.h"

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::texture_cache{};

Texture::Texture(const std::shared_ptr<Image> &image, unsigned int unit, bool set_default_warp_filter) {
    init(image, unit, set_default_warp_filter);
}

Texture::~Texture() {
    destroy();
}

void Texture::init(const std::shared_ptr<Image> &image, unsigned int unit, bool set_default_warp_filter) {
    m_unit = unit;

    glGenTextures(1, &m_texture_id);

    attach_texture();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width(), image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data());
    glGenerateMipmap(GL_TEXTURE_2D);

    if (!set_default_warp_filter) {
        set_wrap(Warp::S, Wrap_type::REPEAT);
        set_wrap(Warp::T, Wrap_type::REPEAT);
        set_filter(Filter::MIN, Filter_type::LINEAR_MIPMAP_LINEAR);
        set_filter(Filter::MAG, Filter_type::LINEAR);
    }
   
    detach_texture();

}

void Texture::destroy() {
    if (m_texture_id == 0) return;
    attach_texture();
    glDeleteTextures(1, &m_texture_id);
    // After deletion, the texture unit that was bound to textureID is now bound to 0
}

void Texture::set_wrap(Warp warp, Wrap_type wrap_type) {
    glTexParameteri(GL_TEXTURE_2D, warp_to_gl_enum(warp), wrap_type_to_gl_enum(wrap_type));
}

void Texture::set_filter(Filter filter, Filter_type filter_type) {
    glTexParameteri(GL_TEXTURE_2D, filter_to_gl_enum(filter), filter_type_to_gl_enum(filter_type));
}

[[nodiscard]] GLuint Texture::id() const {
    return m_texture_id;
}

[[nodiscard]] unsigned int Texture::unit() const {
    return m_unit;
}

void Texture::attach_texture() {
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::detach_texture() {
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

constexpr GLenum Texture::warp_to_gl_enum(Warp type) {
    switch (type) {
        case Warp::S:
            return GL_TEXTURE_WRAP_S;
        case Warp::T:
            return GL_TEXTURE_WRAP_T;
        default:
            return GL_TEXTURE_WRAP_S;
    }
}

constexpr GLenum Texture::filter_to_gl_enum(Filter type) {
    switch (type) {
        case Filter::MIN:
            return GL_TEXTURE_MIN_FILTER;
        case Filter::MAG:
            return GL_TEXTURE_MAG_FILTER;
        default:
            return GL_TEXTURE_MIN_FILTER;
    }
}

constexpr GLenum Texture::wrap_type_to_gl_enum(Wrap_type wrap) {
    switch (wrap) {
        case Wrap_type::REPEAT:
            return GL_REPEAT;
        case Wrap_type::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case Wrap_type::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case Wrap_type::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        default:
            return GL_REPEAT;
    }
}

constexpr GLenum Texture::filter_type_to_gl_enum(Filter_type filter) {
    switch (filter) {
        case Filter_type::LINEAR:
            return GL_LINEAR;
        case Filter_type::NEAREST:
            return GL_NEAREST;
        case Filter_type::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        case Filter_type::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case Filter_type::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case Filter_type::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        default:
            return GL_LINEAR;
    }
}