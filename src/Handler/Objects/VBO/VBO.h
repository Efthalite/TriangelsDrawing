#ifndef HANDLER_VBO_H
#define HANDLER_VBO_H

#include <glad/glad.h>


class VBO
{
private:
    GLuint vboID;

public:
    VBO(float* vertices, GLsizeiptr size);


    void Bind();
    void Unbind();
    void Delete();

    GLuint GetVBOID();

};





#endif