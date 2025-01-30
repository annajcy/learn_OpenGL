#pragma once

#include <string>

class Image {
private:

    int m_width{};
    int m_height{};
    int m_channels{};
    unsigned char* m_data{nullptr};
    
public:

    Image();
    ~Image();
    
    void init(const std::string& path, bool flip_y = true);
    void destroy();
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] int channels() const;
    [[nodiscard]] unsigned char* data() const;
};