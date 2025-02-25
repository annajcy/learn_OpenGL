#pragma once

#include "global/core.h"

#include "application/image.h"

class Texture {
public:

    static std::string default_texture_path;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache;

    static std::shared_ptr<Texture> create_default_texture(unsigned int unit = 0);
    static std::shared_ptr<Texture> create_texture_from_path(const std::string& image_path, unsigned int unit = 0, const std::string& key = "");
    static std::shared_ptr<Texture> create_texture_from_memory(unsigned char* data, int data_size, unsigned int unit = 0, const std::string& key = "");
    
    static std::shared_ptr<Texture> create_color_attachment(int width, int height, unsigned int unit = 0);
    static std::shared_ptr<Texture> create_depth_stencil_attachment(int width, int height, unsigned int unit = 0);
    static std::shared_ptr<Texture> create_cube_map(const std::vector<std::string>& image_paths, unsigned int unit = 0);

    static void generate_texture(unsigned int& texture_id) {
        glGenTextures(1, &texture_id);
    }

    enum class Buffer_format {
        UNSIGNED_BYTE,
        UNSIGNED_INT,
        UNSIGNED_SHORT,
        FLOAT,
        UNSIGNED_INT_24_8,
    };

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

    enum class Texture_type {
        TEXTURE_2D,
        TEXTURE_CUBE_MAP,
        TEXTURE_CUBE_MAP_POSITIVE_X,
        TEXTURE_CUBE_MAP_NEGATIVE_X,
        TEXTURE_CUBE_MAP_POSITIVE_Y,
        TEXTURE_CUBE_MAP_NEGATIVE_Y,
        TEXTURE_CUBE_MAP_POSITIVE_Z,
        TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };

    enum class Texture_format {
        RGB,
        RGBA,
        DEPTH_STENCIL,
        DEPTH_STENCIL_24_8,
    };

    enum class Filter {
        MIN, MAG
    };

    enum class Warp {
        S, T, R
    };

    constexpr static GLenum warp_to_gl_enum(Warp type);
    constexpr static GLenum filter_to_gl_enum(Filter type);
    constexpr static GLenum wrap_type_to_gl_enum(Wrap_type wrap);
    constexpr static GLenum filter_type_to_gl_enum(Filter_type filter);

    constexpr static GLenum texture_format_to_gl_enum(Texture_format format) {
        switch (format) {
            case Texture_format::RGB:
                return GL_RGB;
            case Texture_format::RGBA:
                return GL_RGBA;
            case Texture_format::DEPTH_STENCIL:
                return GL_DEPTH_STENCIL;
            case Texture_format::DEPTH_STENCIL_24_8:
                return GL_DEPTH24_STENCIL8;
        }
    }

    constexpr static GLenum texture_type_to_gl_enum(Texture_type type) {
        switch (type) {
            case Texture_type::TEXTURE_2D:
                return GL_TEXTURE_2D;
            case Texture_type::TEXTURE_CUBE_MAP:
                return GL_TEXTURE_CUBE_MAP;
            case Texture_type::TEXTURE_CUBE_MAP_POSITIVE_X:
                return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
            case Texture_type::TEXTURE_CUBE_MAP_NEGATIVE_X:
                return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
            case Texture_type::TEXTURE_CUBE_MAP_POSITIVE_Y:
                return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
            case Texture_type::TEXTURE_CUBE_MAP_NEGATIVE_Y:
                return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
            case Texture_type::TEXTURE_CUBE_MAP_POSITIVE_Z:
                return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
            case Texture_type::TEXTURE_CUBE_MAP_NEGATIVE_Z:
                return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
        }
    }

    constexpr static GLenum buffer_format_to_gl_enum(Buffer_format format) {
        switch (format) {
            case Buffer_format::UNSIGNED_BYTE:
                return GL_UNSIGNED_BYTE;
            case Buffer_format::UNSIGNED_INT:
                return GL_UNSIGNED_INT;
            case Buffer_format::UNSIGNED_SHORT:
                return GL_UNSIGNED_SHORT;
            case Buffer_format::FLOAT:
                return GL_FLOAT;
            case Buffer_format::UNSIGNED_INT_24_8:
                return GL_UNSIGNED_INT_24_8;
        }
    }

private:

    int m_width{};
    int m_height{};
    GLuint m_texture_id{};
    unsigned int m_unit{};
    std::string m_key{};
    Texture_type m_texture_type{};
    
public:

    Texture(
        int width, 
        int height, 
        unsigned int unit, 
        Texture_type texture_type
    ) {
        m_unit = unit;
        m_width = width;
        m_height = height;
        m_texture_type = texture_type;
        generate_texture(m_texture_id);
    }

    Texture(
        int width, 
        int height, 
        unsigned int unit, 
        unsigned char* data,
        Texture_type texture_type,
        Texture_format external_format, 
        Texture_format internal_format, 
        Buffer_format buffer_format
    );

    ~Texture();

    void set_data(int width, int height, unsigned char* data, Texture_type texture_type, Texture_format external_format, Texture_format internal_format, Buffer_format buffer_format) {
        
        if (!data) {
            std::cout << "invalid image data, create empty texture" << std::endl;
        } else {
            std::cout << "image data valid" << std::endl;
        }

        attach_texture();
        glTexImage2D(
            texture_type_to_gl_enum(texture_type),
            0,
            texture_format_to_gl_enum(internal_format),
            width,
            height,
            0,
            texture_format_to_gl_enum(external_format),
            buffer_format_to_gl_enum(buffer_format),
            data
        );
        detach_texture();
    }

    void destroy();
    void set_wrap(Warp warp, Wrap_type wrap_type);
    void set_filter(Filter filter, Filter_type filter_type);
    void generate_mipmaps() {
        attach_texture();
        glGenerateMipmap(texture_type_to_gl_enum(m_texture_type));
        detach_texture();
    }

    void set_default_warp_filter() {
        set_wrap(Warp::S, Wrap_type::REPEAT);
        set_wrap(Warp::T, Wrap_type::REPEAT);
        set_filter(Filter::MIN, Filter_type::LINEAR);
        set_filter(Filter::MAG, Filter_type::LINEAR);
    }
    
    void attach_texture();
    void detach_texture();

    bool is_registered_to_cache() const {
        return !m_key.empty();
    }

    [[nodiscard]] int width() const; 
    [[nodiscard]] int height() const;

    [[nodiscard]] GLuint id() const;

    [[nodiscard]] unsigned int unit() const;
    unsigned int& unit();

    [[nodiscard]] Texture_type texture_type() const { 
        return m_texture_type;
    }
};