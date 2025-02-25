#include "texture.h"

std::string Texture::default_texture_path = "assets/image/default_texture.jpg";
std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::texture_cache{};

std::shared_ptr<Texture> Texture::create_default_texture(unsigned int unit) {
    return create_texture_from_path(default_texture_path, unit, default_texture_path);
}

//paths:右左上下后前(+x -x +y -y +z -z)
std::shared_ptr<Texture> Texture::create_cube_map(const std::vector<std::string>& image_paths, unsigned int unit) {
    if (image_paths.size() != 6) {
        std::cout << "invalid image paths, create empty texture" << std::endl;
        return nullptr;
    }

    auto texture = std::make_shared<Texture>(0, 0, unit, Texture_type::TEXTURE_CUBE_MAP);
    
    const std::array<Texture_type, 6> targets{
        Texture_type::TEXTURE_CUBE_MAP_POSITIVE_X,
        Texture_type::TEXTURE_CUBE_MAP_NEGATIVE_X,
        Texture_type::TEXTURE_CUBE_MAP_POSITIVE_Y,
        Texture_type::TEXTURE_CUBE_MAP_NEGATIVE_Y,
        Texture_type::TEXTURE_CUBE_MAP_POSITIVE_Z,
        Texture_type::TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };

    for (int i = 0; i < 6; i++) {
        auto image = std::make_shared<Image>(image_paths[i], false);
        
        if (image->data() == nullptr) {
            std::cout << "invalid image path: " << image_paths[i] << ", create empty texture" << std::endl;
            return nullptr;
        }

        texture->set_data(image->width(), image->height(), image->data(), 
            targets[i], 
            Texture_format::RGBA, 
            Texture_format::RGBA, 
            Buffer_format::UNSIGNED_BYTE
        );
    }

    texture->set_default_warp_filter();
    texture->set_wrap(Warp::R, Wrap_type::REPEAT);

    return texture;
    
}

std::shared_ptr<Texture> Texture::create_texture_from_path(const std::string& image_path, unsigned int unit, const std::string& key) {
    
    if (key.empty()) {
        auto image = std::make_shared<Image>(image_path);
        return std::make_shared<Texture>(image->width(), image->height(), unit, image->data(), 
            Texture_type::TEXTURE_2D,
            Texture_format::RGBA,
            Texture_format::RGBA,
            Buffer_format::UNSIGNED_BYTE
        );
    }

    if (texture_cache.contains(key)) {
        texture_cache[key]->unit() = unit;
        return texture_cache.at(key);
    }
    auto image = std::make_shared<Image>(image_path);
    auto texture = std::make_shared<Texture>(image->width(), image->height(), unit, image->data(),
            Texture_type::TEXTURE_2D,
            Texture_format::RGBA,
            Texture_format::RGBA,
            Buffer_format::UNSIGNED_BYTE
        );

    texture->set_default_warp_filter();
    texture->m_key = key;
    texture_cache.insert({key, texture});
    return texture;
}

std::shared_ptr<Texture> Texture::create_texture_from_memory(unsigned char* data, int data_size, unsigned int unit, const std::string& key) {
    
    if (key.empty()) {
        auto image = std::make_shared<Image>(data, data_size);
        return std::make_shared<Texture>(image->width(), image->height(), unit, image->data(), 
            Texture_type::TEXTURE_2D,
            Texture_format::RGBA,
            Texture_format::RGBA,
            Buffer_format::UNSIGNED_BYTE
        );
    }
    
    if (texture_cache.contains(key)) {
        texture_cache[key]->unit() = unit;
        return texture_cache.at(key);
    }
    auto image = std::make_shared<Image>(data, data_size);
    auto texture = std::make_shared<Texture>(image->width(), image->height(), unit, image->data(), 
        Texture_type::TEXTURE_2D,
        Texture_format::RGBA,
        Texture_format::RGBA,
        Buffer_format::UNSIGNED_BYTE
    );

    texture->set_default_warp_filter();
    texture->m_key = key;
    texture_cache.insert({key, texture});
    return texture;
}

std::shared_ptr<Texture> Texture::create_color_attachment(int width, int height, unsigned int unit) {
    auto texture = std::make_shared<Texture>(width, height, unit, nullptr, 
        Texture_type::TEXTURE_2D, 
        Texture_format::RGBA, 
        Texture_format::RGBA, 
        Buffer_format::UNSIGNED_BYTE);

    texture->set_default_warp_filter();
    return texture;
}

std::shared_ptr<Texture> Texture::create_depth_stencil_attachment(int width, int height, unsigned int unit) {
    auto texture = std::make_shared<Texture>(width, height, unit, nullptr, 
        Texture_type::TEXTURE_2D, 
        Texture_format::DEPTH_STENCIL, 
        Texture_format::DEPTH_STENCIL_24_8, 
        Buffer_format::UNSIGNED_INT_24_8
    );

    texture->set_default_warp_filter();
    return texture;
}

Texture::Texture(
    int width, 
    int height, 
    unsigned int unit, 
    unsigned char* data,
    Texture_type texture_type,
    Texture_format external_format, 
    Texture_format internal_format, 
    Buffer_format buffer_format
) {

    m_unit = unit;
    m_width = width;
    m_height = height;
    m_texture_type = texture_type;

    generate_texture(m_texture_id);
    set_data(width, height, data, texture_type, external_format, internal_format, buffer_format);

}

int Texture::width() const {
    return m_width;
}

int Texture::height() const {
    return m_height;
}

Texture::~Texture() {
    destroy();
}

void Texture::destroy() {
    if (m_texture_id == 0) return;
    attach_texture();
    glDeleteTextures(1, &m_texture_id);
    if (is_registered_to_cache()) texture_cache.erase(m_key);
    detach_texture();
}

void Texture::set_wrap(Warp warp, Wrap_type wrap_type) {
    attach_texture();
    glTexParameteri(texture_type_to_gl_enum(m_texture_type), warp_to_gl_enum(warp), wrap_type_to_gl_enum(wrap_type));
    detach_texture();
}

void Texture::set_filter(Filter filter, Filter_type filter_type) {
    attach_texture();
    glTexParameteri(texture_type_to_gl_enum(m_texture_type), filter_to_gl_enum(filter), filter_type_to_gl_enum(filter_type));
    detach_texture();
}

[[nodiscard]] GLuint Texture::id() const {
    return m_texture_id;
}

[[nodiscard]] unsigned int Texture::unit() const {
    return m_unit;
}

unsigned int& Texture::unit() {
    return m_unit;
}

void Texture::attach_texture() {
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glBindTexture(texture_type_to_gl_enum(m_texture_type), m_texture_id);
}

void Texture::detach_texture() {
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glBindTexture(texture_type_to_gl_enum(m_texture_type), 0);
}

constexpr GLenum Texture::warp_to_gl_enum(Warp type) {
    switch (type) {
        case Warp::S:
            return GL_TEXTURE_WRAP_S;
        case Warp::T:
            return GL_TEXTURE_WRAP_T;
        case Warp::R:
            return GL_TEXTURE_WRAP_R;
    }
}

constexpr GLenum Texture::filter_to_gl_enum(Filter type) {
    switch (type) {
        case Filter::MIN:
            return GL_TEXTURE_MIN_FILTER;
        case Filter::MAG:
            return GL_TEXTURE_MAG_FILTER;
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