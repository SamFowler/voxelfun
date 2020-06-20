#include "Frustum.h"

void Frustum::getPlanes(const glm::mat4& vp)
{
    //left
    planes[0][0] = vp[0][3] + vp[0][0];
    planes[0][1] = vp[1][3] + vp[1][0];
    planes[0][2] = vp[2][3] + vp[2][0];
    planes[0][3] = vp[3][3] + vp[3][0];

    //right
    planes[1][0] = vp[0][3] - vp[0][0];
    planes[1][1] = vp[1][3] - vp[1][0];
    planes[1][2] = vp[2][3] - vp[2][0];
    planes[1][3] = vp[3][3] - vp[3][0];

    //bottom
    planes[2][0] = vp[0][3] + vp[0][1];
    planes[2][1] = vp[1][3] + vp[1][1];
    planes[2][2] = vp[2][3] + vp[2][1];
    planes[2][3] = vp[3][3] + vp[3][1];

    //top
    planes[3][0] = vp[0][3] - vp[0][1];
    planes[3][1] = vp[1][3] - vp[1][1];
    planes[3][2] = vp[2][3] - vp[2][1];
    planes[3][3] = vp[3][3] - vp[3][1];

    //near
    planes[4][0] = vp[0][2];
    planes[4][1] = vp[1][2];
    planes[4][2] = vp[2][2];
    planes[4][3] = vp[3][2];

    //far
    planes[5][0] = vp[0][3] - vp[0][2];
    planes[5][1] = vp[1][3] - vp[1][2];
    planes[5][2] = vp[2][3] - vp[2][2];
    planes[5][3] = vp[3][3] - vp[3][2];

}   

bool Frustum::pointInFrustum(const glm::ivec3& pt) const
{
    for (int i = 0; i < 2; i++)
        if ( planes[i].x * pt.x + planes[i].y * pt.y + planes[i].z * pt.z + planes[i].w <= 0 )
            return false;

    return true;
}

bool Frustum::cubeInFrustum(const glm::ivec3& lb /* lower bound */, const glm::ivec3& ub /* upper bound */) const
{
    for (int p = 0; p < 6; p++)
    {
        if( (planes[p][0] * (lb.x)   +   planes[p][1] * (lb.y)  +  planes[p][2] * (lb.z)   +   planes[p][3]) > 0 )
            continue;
        if( (planes[p][0] * (ub.x)   +   planes[p][1] * (lb.y)  +  planes[p][2] * (lb.z)   +   planes[p][3]) > 0 )
            continue;
        if( (planes[p][0] * (lb.x)   +   planes[p][1] * (ub.y)  +  planes[p][2] * (lb.z)   +   planes[p][3]) > 0 )
            continue;
        if( (planes[p][0] * (ub.x)   +   planes[p][1] * (ub.y)  +  planes[p][2] * (lb.z)   +   planes[p][3]) > 0 )
            continue;
        if( (planes[p][0] * (lb.x)   +   planes[p][1] * (lb.y)  +  planes[p][2] * (ub.z)   +   planes[p][3]) > 0 )  
            continue;
        if( (planes[p][0] * (ub.x)   +   planes[p][1] * (lb.y)  +  planes[p][2] * (ub.z)   +   planes[p][3]) > 0 )
            continue;
        if( (planes[p][0] * (lb.x)   +   planes[p][1] * (ub.y)  +  planes[p][2] * (ub.z)   +   planes[p][3]) > 0 )
            continue;
        if( (planes[p][0] * (ub.x)   +   planes[p][1] * (ub.y)  +  planes[p][2] * (ub.z)   +   planes[p][3]) > 0 )
            continue;

        /* 
        if( planes[p][0] * (pt.x - half_size.x)   +   planes[p][1] * (pt.y - half_size.y)  +  planes[p][2] * (pt.z - half_size.z)   +   planes[p][3] > 0 )
            continue;
        if( planes[p][0] * (pt.x + half_size.x)   +   planes[p][1] * (pt.y - half_size.y)  +  planes[p][2] * (pt.z - half_size.z)   +   planes[p][3] > 0 )
            continue;
        if( planes[p][0] * (pt.x - half_size.x)   +   planes[p][1] * (pt.y + half_size.y)  +  planes[p][2] * (pt.z - half_size.z)   +   planes[p][3] > 0 )
            continue;
        if( planes[p][0] * (pt.x + half_size.x)   +   planes[p][1] * (pt.y + half_size.y)  +  planes[p][2] * (pt.z - half_size.z)   +   planes[p][3] > 0 )
            continue;
        if( planes[p][0] * (pt.x - half_size.x)   +   planes[p][1] * (pt.y - half_size.y)  +  planes[p][2] * (pt.z + half_size.z)   +   planes[p][3] > 0 )  
            continue;
        if( planes[p][0] * (pt.x + half_size.x)   +   planes[p][1] * (pt.y - half_size.y)  +  planes[p][2] * (pt.z + half_size.z)   +   planes[p][3] > 0 )
            continue;
        if( planes[p][0] * (pt.x - half_size.x)   +   planes[p][1] * (pt.y + half_size.y)  +  planes[p][2] * (pt.z + half_size.z)   +   planes[p][3] > 0 )
            continue;
        if( planes[p][0] * (pt.x + half_size.x)   +   planes[p][1] * (pt.y + half_size.y)  +  planes[p][2] * (pt.z + half_size.z)   +   planes[p][3] > 0 )
            continue; */
        return false;
    }
    return true;
}

