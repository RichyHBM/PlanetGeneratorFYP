#ifndef SIDEMANAGER_HPP
#define SIDEMANAGER_HPP

#include "Quad.hpp"
#include <vector>
#include "../GLHelp/GLHelp.hpp"
#include "../RuntimeSettings.hpp"
#include "../Physics/Frustrum.hpp"

struct DistortionPlane {
    glm::vec3 Origin;
    glm::vec3 Direction;
};

class SideManager
{
public:
    SideManager( const Quad &q );
    ~SideManager();
    std::vector<Quad> Subdivide( const Quad &q );
    void Draw( const glm::mat4 &MVP );
    void Update( const Frustrum &frustrum );
    void BindData();
    void Distort( const glm::vec3 &origin, const glm::vec3 &direction );
    void Spherify();
    int GetVertexCount();
    void RebuildDistortions();
    void RebuildSide();

protected:
    void NormalizeVert( glm::vec3 &v );

    Quad mInitialQuad;

    std::vector<Quad> mQuads;
    std::vector<DistortionPlane> mDistortionPlanes;

    VBO mPositionBuffer;
    VBO mNormalBuffer;
    Shader *mShader;
private:
};

#endif // SIDEMANAGER_HPP
