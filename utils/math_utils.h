#pragma once 

#include "global/core.h"

namespace utils {
    inline void decompose_transform(
        const glm::mat4& matrix,
        glm::vec3& position,
        glm::quat& rotation,
        glm::vec3& scale
    ) {
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(matrix, scale, rotation, position, skew, perspective);
    }
}