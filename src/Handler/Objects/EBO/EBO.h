#ifndef HANDLER_EBO_H
#define HANDLER_EBO_H

#include <glad/glad.h>

class EBO
{
private:
    GLuint eboID;

public:
    EBO(GLuint* vertices, GLsizeiptr size);


    void Bind();
    void Unbind();
    void Delete();

    GLuint GetEBOID();

};



#endif