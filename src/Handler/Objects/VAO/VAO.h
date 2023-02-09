#ifndef HANDLER_VAO_H
#define HANDLER_VAO_H


#include <glad/glad.h>
#include "../VBO/VBO.h"


class VAO
{
private:
    GLuint vaoID;

public:
    VAO();


    void Bind();
    void Unbind();
    void Delete();
    void LinkAttrib(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, void* start);

    GLuint GetVAOID();

};







#endif

