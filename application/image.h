#pragma once

#include "global/core.h"

class Image {

private:
    int m_width{};
    int m_height{};
    int m_channels{};
    unsigned char* m_data{nullptr};
    
public:
    
    Image(const unsigned char* data, int data_size, bool flip_y = true);
    Image(const std::string& path, bool flip_y = true);
    ~Image();
    
    void init(const unsigned char* data, int data_size, bool flip_y = true);
    void init(const std::string& path, bool flip_y = true);
    void destroy();
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] int channels() const;
    [[nodiscard]] unsigned char* data() const;
};