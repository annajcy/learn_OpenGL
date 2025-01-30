#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image() = default;
Image::~Image() = default;

void Image::init(const std::string& path, bool flip_y) {
    stbi_set_flip_vertically_on_load(flip_y);
    m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);
}

void Image::destroy() {
    stbi_image_free(m_data);
}

[[nodiscard]] int Image::width() const {
    return m_width;
}

[[nodiscard]] int Image::height() const {
    return m_height;
}

[[nodiscard]] int Image::channels() const {
    return m_channels;
}

[[nodiscard]] unsigned char* Image::data() const {
    return m_data;
}