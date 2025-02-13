#pragma once 

#include "global/core.h"

namespace utils {
    inline void decompose_transform(
        const glm::mat4& matrix,
        glm::vec3& position,
        glm::vec3& rotation_euler,
        glm::vec3& scale
    ) {
        glm::quat quaternion;
        glm::vec3 skew;
        glm::vec4 perspective;

        glm::decompose(matrix, scale, quaternion, position, skew, perspective);

        glm::mat4 rotation = glm::toMat4(quaternion);
        glm::extractEulerAngleXYZ(rotation, rotation_euler.x, rotation_euler.y, rotation_euler.z);
    
        rotation_euler.x = glm::degrees(rotation_euler.x);
        rotation_euler.y = glm::degrees(rotation_euler.y);
        rotation_euler.z = glm::degrees(rotation_euler.z);

    }
}