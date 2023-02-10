#ifndef HANDLER_GAME_OBJECT_H
#define HANDLER_GAME_OBJECT_H


#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "../VAO/VAO.h"
#include "../VBO/VBO.h"
#include "../EBO/EBO.h"
#include "../../Shader/Shader.h"

class GameObject
{
private:
    glm::vec3 objPosition = glm::vec3(0.0f);
    glm::mat4 matrix;

    Shader objShader;

    float objSize = 1.0f;

    VAO mVAO;
    


    float Triangle[12] = 
    {
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,

       //  -1.0f,  1.0f,  0.0f,
        // 1.0f, -1.0f,  0.0f,
         1.0f,  1.0f,  0.0f
    };

    unsigned int TriangleIndicies[6] = 
    {
        0, 1, 2,
        1, 2, 3
    };

    float Color[18] = 
    {
        1.0f, 0.1f, 0.1f,
        0.1f, 1.0f, 0.1f,
        0.1f, 0.1f, 1.0f,
        
        1.0, 1.0f, 0.1f,
        0.1f, 1.0f, 1.0f,
        1.0f, 0.1f, 1.0f
    };


public:
    GameObject();
    
    void Translate(glm::vec3 addPos);
    void Resize(float size);


    glm::vec3 GetPosition() const;

    void Render();


};


#endif
