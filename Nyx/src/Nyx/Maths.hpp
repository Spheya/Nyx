#pragma once

#include "Maths/MathsLibrary.hpp"

#include "Core/Logger.hpp"

#include <functional>

namespace Nyx {
    constexpr float PI = 3.14159265359f;
    constexpr float HALF_PI = PI * 0.5f;
    constexpr float TWO_PI = 2.0f * PI;

    constexpr float E = 2.7182818284f;

    constexpr float PHI = 1.61803398875f;

    constexpr float SQRT_TWO = 1.41421356237f;
    constexpr float SQRT_THREE = 1.73205080757f;
    constexpr float SQRT_FIVE = 2.2360679775f;

    constexpr float DEGREES_TO_RADIANS = PI / 180.0f;
    constexpr float RADIANS_TO_DEGREES = 180.0f / PI;
}

// GLM Data Types
template<typename OStream>
OStream& operator<<(OStream& os, const glm::vec2& v) {
    return os << "[x=" << v.x << ", y=" << v.y <<"]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::vec3& v) {
    return os << "[x=" << v.x << ", y=" << v.y << ", z=" << v.z << "]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::vec4& v) {
    return os << "[x=" << v.x << ", y=" << v.y << ", z=" << v.z << ", w=" << v.w << "]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::ivec2& v) {
    return os << "[x=" << v.x << ", y=" << v.y << "]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::ivec3& v) {
    return os << "[x=" << v.x << ", y=" << v.y << ", z=" << v.z << "]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::ivec4& v) {
    return os << "[x=" << v.x << ", y=" << v.y << ", z=" << v.z << ", w=" << v.w << "]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::mat3& m) {
    return os << "\n" <<
        "                         [" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << "]\n" <<
        "                         [" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << "]\n" <<
        "                         [" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << "]";
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::mat4& m) {
    return os << "\n" <<
        "                         [" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]\n" <<
        "                         [" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]\n" <<
        "                         [" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]\n" <<
        "                         [" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]";
}