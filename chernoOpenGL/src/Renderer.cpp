
#include "Renderer.h"

#include <iostream>

#include "spdlog\spdlog.h"

void glClearError()
{
    while( GL_NO_ERROR != glGetError() )
    {}
}

bool glLogCall( const char* function, const char* file, const int line )
{
    while( GLenum error = glGetError() )
    {
        spdlog::error( "OpenGL:{}:{}:{}: ({:x})", file, function, line, error );
        return false;
    }

    return true;
}

void Renderer::clear() const
{
    glCall( glClear(GL_COLOR_BUFFER_BIT) );
}

void Renderer::draw(const VertexArray & vArray, const IndexBuffer & iBuffer, const ShaderProgram & shader) const
{

    shader.bind();

    // Bind vertex array & index buffer
    vArray.bind();
    iBuffer.bind();

    // Draw
    glCall( glDrawElements( GL_TRIANGLES, iBuffer.getCount(), GL_UNSIGNED_INT, nullptr ) );

}
