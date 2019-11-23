
#ifndef RENDERER_H
#define RENDERER_H

#include <GL\glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

#define ASSERT(x) if (!(x)) __debugbreak()
#define glCall(x) \
    glClearError(); \
    x; \
    ASSERT( glLogCall( #x, __FILE__, __LINE__ ) )

void glClearError();
bool glLogCall( const char* function, const char* file, const int line );


class Renderer
{
private:



public:

    void clear() const;
    void draw( const VertexArray& vArray, const IndexBuffer& iBuffer, const ShaderProgram& shader ) const;

};

#endif // !RENDERER_H
