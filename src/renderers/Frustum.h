#pragma once

#include "../pch/pch_std.h"

class Frustum
{
private:
    std::array<glm::vec4, 6> planes;
public:
    void getPlanes(const glm::mat4& vp_matrix);

    bool pointInFrustum(const glm::ivec3& point) const;
    bool cubeInFrustum(const glm::ivec3& point, const glm::ivec3& half_size) const;
private:
};