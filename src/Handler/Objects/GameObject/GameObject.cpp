#include "GameObject.h"


GameObject::GameObject() : 
matrix(1.0f),
objShader("shaders/GameObject/defaultVertexShader.glsl", "shaders/GameObject/defaultFragmentShader.glsl"),
mVAO()
{
    mVAO.Bind();
    VBO mVBO(Triangle, sizeof(Triangle));
    mVBO.Bind();
    
    EBO mEBO(TriangleIndicies, sizeof(TriangleIndicies));
    mEBO.Bind();

    mVAO.LinkAttrib(mVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
    
    mVAO.Unbind();
    mVBO.Unbind();
    mEBO.Unbind();

    VBO mColVBO(Color, sizeof(Color));
    
    mVAO.Bind();
    mColVBO.Bind();
    mVAO.LinkAttrib(mColVBO, 1, 3, GL_FLOAT, 3 * sizeof(float), 0);
    mVAO.Unbind();
    mColVBO.Unbind();


}


void GameObject::Translate(glm::vec3 addPos)
{
    objPosition += addPos;
}

void GameObject::Resize(float size)
{
    objSize = size;
}

void GameObject::Render()
{

    matrix = glm::mat4(objSize, 0.0f, 0.0f, objPosition.x,
                        0.0f, objSize, 0.0f, objPosition.y,
                        0.0f, 0.0f, objSize, objPosition.z,
                        0.0f, 0.0f, 0.0f, 1.0f);

    objShader.UseProgram();
    objShader.UniformMatrix4fv("u_Transform", matrix);

    mVAO.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    mVAO.Unbind();
    objShader.DisableProgram();

}

