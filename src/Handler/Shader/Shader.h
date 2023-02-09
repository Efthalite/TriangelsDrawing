#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>


class Shader
{
private:
    GLuint programID;

    std::string ShaderSource (std::string filePath);
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

    void CreateShader(std::string shaderPath, GLenum shaderType);
    
    void UseProgram();
    void DisableProgram();
    void DeleteProgram();
    GLuint GetProgramID();


    void Uniform1f(std::string uniformName, float value);
    void UniformMatrix4fv(std::string uniformName, glm::mat4 matrix4x4);

};


#endif