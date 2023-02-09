#include "EBO.h"



EBO::EBO(GLuint* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &eboID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    Unbind();
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
    glDeleteBuffers(1, &eboID);
}



GLuint EBO::GetEBOID()
{
    return eboID;
}