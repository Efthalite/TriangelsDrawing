#include "VBO.h"



VBO::VBO(float* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &vboID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    Unbind();
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &vboID);
}



GLuint VBO::GetVBOID()
{
    return vboID;
}