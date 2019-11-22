
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