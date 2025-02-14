#include "image.h"
#include "stb_image.h"

Image::Image(const std::string& path, bool flip_y) {
    init(path, flip_y);
}

Image::Image(const unsigned char* data, int data_size, bool flip_y) {
    init(data, data_size, flip_y);
}

Image::~Image() {
    destroy();
}

void Image::init(const std::string& path, bool flip_y) {
    stbi_set_flip_vertically_on_load(flip_y);
    m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);
}

void Image::init(const unsigned char* data, int data_size, bool flip_y) {
    stbi_set_flip_vertically_on_load(flip_y);
    m_data = stbi_load_from_memory(data, data_size, &m_width, &m_height, &m_channels, STBI_rgb_alpha);
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