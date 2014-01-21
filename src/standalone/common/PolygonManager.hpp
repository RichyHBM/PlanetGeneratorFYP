#ifndef POLYGONMANAGER_HPP
#define POLYGONMANAGER_HPP

#include "Quad.hpp"
#include <vector>
#include "framework/GLHelp/GLHelp.hpp"

#define PLANETRADIUS 5.0f

class PolygonManager
{
public:
    PolygonManager();
    ~PolygonManager();
    void Subdivide();
    //void Undivide();
    void Draw( const glm::mat4 &MVP );
    void Update();
    void AddQuad( const Quad &q );
    void GiveHeight( glm::vec3 &v, float pHeight );
    void BindData();
    void Distort( const glm::vec3 &origin, const glm::vec3 &direction );
    void Spherify();
protected:
    void NormalizeVert( glm::vec3 &v );

    std::vector<Quad> mQuads;
    std::vector<glm::vec3> mPositionsList;
    std::vector<glm::vec3> mNormalsList;

    VBO mPositionBuffer;
    VBO mNormalBuffer;
    Shader *mShader;
private:
};

#endif // POLYGONMANAGER_HPP
