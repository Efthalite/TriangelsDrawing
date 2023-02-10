#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Handler/Objects/GameObject/GameObject.h"

#include "Handler/Shader/Shader.h"
#include "Handler/Objects/VBO/VBO.h"
#include "Handler/Objects/EBO/EBO.h"
#include "Handler/Objects/VAO/VAO.h"

void Movement(GLFWwindow* window, GameObject& obj)
{
    float speed = 0.03f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        obj.Translate(glm::vec3(speed, 0, 0));
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        obj.Translate(glm::vec3(-speed, 0, 0));
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        obj.Translate(glm::vec3(0, speed, 0));
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        obj.Translate(glm::vec3(0, -speed, 0));
    }


}


void ProccessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

int main()
{
    int winWidth = 1080, winHeight = 1080;
    const char* winTitle = "GameObjectTest";

    float Triangle[] = 
    {
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,

       //  -1.0f,  1.0f,  0.0f,
        // 1.0f, -1.0f,  0.0f,
         1.0f,  1.0f,  0.0f
    };

    unsigned int TriangleIndicies[] = 
    {
        0, 1, 2,
        1, 2, 3
    };

    float Color[] = 
    {
        1.0f, 0.1f, 0.1f,
        0.1f, 1.0f, 0.1f,
        0.1f, 0.1f, 1.0f,
        
        1.0, 1.0f, 0.1f,
        0.1f, 1.0f, 1.0f,
        1.0f, 0.1f, 1.0f
    };


    if(!glfwInit())
    {
        std::cout << "Failed to initialize glfw\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, winTitle, nullptr, nullptr);

    if(!window)
    {
        std::cout << "Failed to create a window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, winWidth, winHeight);




    GameObject entity, CenterQuad;

    entity.Resize(0.4f);
    CenterQuad.Resize(0.2f);
   // RotatingQuad.Resize(0.2f);


    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ProccessInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 0.2f, 1.0f);

        float time = glfwGetTime();

        CenterQuad.Render();
        if(CenterQuad.GetPosition().x < 2.0f) CenterQuad.Translate(glm::vec3(0.01, 0.0f, 0.0f));
        else CenterQuad.Translate(glm::vec3(-4.0f, 0.0f, 0.0f));


        for(int i = 0; i < 6; i++)
        {
            GameObject RotatingQuad;
            RotatingQuad.Resize(0.15f);

            RotatingQuad.Translate(glm::vec3(CenterQuad.GetPosition().x, 0.0f, 0.0f));
            



            RotatingQuad.Translate(glm::vec3(cos(time + i), sin(time + i), 0.0f));
            RotatingQuad.Render();
        }

        Movement(window, entity);
        entity.Render();

        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}
