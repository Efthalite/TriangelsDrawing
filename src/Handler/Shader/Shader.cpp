#include "Shader.h"
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>


std::string Shader::ShaderSource(std::string filePath)
{
    std::string result;
    std::ifstream inFile(filePath, std::ios::binary);
    std::stringstream streamBuffer;

    if(!inFile)
    {
        std::cout << "Couldn't open " << filePath << std::endl;
        return nullptr;
    }

    streamBuffer << inFile.rdbuf();
    result = streamBuffer.str();


    return result;
}


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    programID = glCreateProgram();

    CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

}



void Shader::CreateShader(std::string shaderPath, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    int success;
    char errorLog[2048];

    std::string shaderSourceBuffer = ShaderSource(shaderPath);
    std::cout << shaderPath << " source is: \n" << shaderSourceBuffer << std::endl;

    const char* shaderCode = shaderSourceBuffer.c_str();
    glShaderSource(shader, 1, &shaderCode, NULL);

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        std::cout << "Failed to compile a shader\n";
        glGetShaderInfoLog(shader, sizeof(errorLog)/sizeof(errorLog[0]), NULL, errorLog);
        std::cout << errorLog << std::endl;

    }


    glAttachShader(programID, shader);
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success)
    {
        std::cout << "Failed to link " << shaderPath << " with program" << std::endl;
        glGetProgramInfoLog(programID, sizeof(errorLog)/sizeof(errorLog[0]), NULL, errorLog );
        std::cout << errorLog << std::endl;
    }

    glDeleteShader(shader);
}



void Shader::UseProgram()
{
    glUseProgram(programID);
}

void Shader::DisableProgram()
{
    glUseProgram(0);
}

void Shader::DeleteProgram()
{
    glDeleteProgram(programID);
}

GLuint Shader::GetProgramID()
{
    return programID;
}




void Shader::Uniform1f(std::string uniformName, float value)
{
    glUniform1f(glGetUniformLocation(programID, uniformName.c_str()), value);
}

void Shader::UniformMatrix4fv(std::string uniformName, glm::mat4 matrix4x4)
{
    glUniformMatrix4fv(glGetUniformLocation(programID, uniformName.c_str()), 1, GL_TRUE, glm::value_ptr(matrix4x4));
}


