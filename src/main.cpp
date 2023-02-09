#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Handler/Shader/Shader.h"
#include "Handler/Objects/VBO/VBO.h"
#include "Handler/Objects/VAO/VAO.h"

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



    Shader defaultShader("shaders/dVertex.glsl", "shaders/dFragment.glsl");

    GLuint ebo;

    glGenBuffers(1, &ebo);
    
    

    VAO vao;

    vao.Bind();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TriangleIndicies), TriangleIndicies, GL_STATIC_DRAW);
    

    VBO vbo(Triangle, sizeof(Triangle)), cbo(Color, sizeof(Color)); 

   
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    vao.Unbind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    vao.Bind();
    vao.LinkAttrib(cbo, 1, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    

    vao.Unbind();
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::cout << "\n\n\n\n\n to be sure you can delete it will be changed a lot of times" << std::endl;

    


    
    float x = 0;
    float y = 0;
    float z = 0;

    float size = 0.2f;

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ProccessInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 0.2f, 1.0f);

        defaultShader.UseProgram();
        vao.Bind();
        if(x > 2) x = -2.0f;
        x += 0.01f;

        //x = 0;

        

        glm::mat4 matrix = glm::mat4(1.0f * size, 0.0f, 0.0f, x,
                            0.0f, 1.0f * size, 0.0f, y,
                            0.0f, 0.0f, 1.0f * size, z,
                            0.0f, 0.0f, 0.0f, 1.0f);

        defaultShader.UniformMatrix4fv("u_Transform", matrix);

        float time = glfwGetTime();
        defaultShader.Uniform1f("u_Time", time);
    

        glDrawArrays(GL_TRIANGLES, 0, 6);

        for(int i = 1; i <= 12 * 3; i++)
        {
            glm::mat4 matrix = glm::mat4(1.0f * size, 0.0f, 0.0f, x + cos((i + 0.3f) + time)*0.7f,
                                         0.0f, 1.0f * size, 0.0f, y + sin((i + 0.3f) + time) * 0.7f,
                                         0.0f, 0.0f, 1.0f * size, z,
                                         0.0f, 0.0f, 0.0f, 1.0f);

            defaultShader.UniformMatrix4fv("u_Transform", matrix);


           glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }

        glfwSwapBuffers(window);
    }

    vao.Delete();
    vbo.Delete();
    cbo.Delete();
    defaultShader.DeleteProgram();
    glfwTerminate();
    return 0;
}
