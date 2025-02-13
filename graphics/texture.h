#pragma once

#include "global/core.h"
#include "application/image.h"
#include <memory>

class Texture {
public:
    static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache;

    static std::shared_ptr<Texture> create_texture_from_path(const std::string& id, const std::string& image_path, unsigned int unit = 0, bool set_default_warp_filter = true) {
        if (texture_cache.contains(id)) return texture_cache.at(id);
        auto image = std::make_shared<Image>(image_path);
        auto texture = std::make_shared<Texture>(image, unit, set_default_warp_filter);
        texture_cache.insert({id, texture});
        return texture;
    }

    static std::shared_ptr<Texture> create_texture_from_memory(const std::string& id, unsigned char* data, int data_size, unsigned int unit = 0, bool set_default_warp_filter = true) {
        if (texture_cache.contains(id)) return texture_cache.at(id);
        auto image = std::make_shared<Image>(data, data_size);
        auto texture = std::make_shared<Texture>(image, unit, set_default_warp_filter);
        texture_cache.insert({id, texture});
        return texture;
    }

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