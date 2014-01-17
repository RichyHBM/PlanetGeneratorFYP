#ifndef TRIANGLEMANAGER_HPP
#define TRIANGLEMANAGER_HPP

#include "Triangle.hpp"
#include <vector>
#include "framework/GLHelp/GLHelp.hpp"

#define PLANETRADIUS 5.0f

class TriangleManager
{
public:
    TriangleManager();
    ~TriangleManager();
    void Subdivide();
    //void Undivide();
    void Normalize();
    void Draw(const glm::mat4 &MVP);
    void AddTriangle(const Triangle& t);

    void BindData();
protected:
    void NormalizeVert(glm::vec3 &v);

    std::vector<Triangle> mTriangles;
    std::vector<glm::vec3> mPositionsList;

    VBO mPositionBuffer;
    Shader *mShader;
private:
};

#endif // TRIANGLEMANAGER_HPP
