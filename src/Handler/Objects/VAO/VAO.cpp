#include "VAO.h"




VAO::VAO()
{
    glGenVertexArrays(1, &vaoID);
}

void VAO::Bind()
{
    glBindVertexArray(vaoID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &vaoID);
}

void VAO::LinkAttrib(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, void* start)
{
    vbo.Bind();

    glVertexAttribPointer(index, size, type, GL_FALSE, stride, start);
    glEnableVertexAttribArray(index);
    
    vbo.Unbind();
}



GLuint VAO::GetVAOID()
{
    return vaoID;
}