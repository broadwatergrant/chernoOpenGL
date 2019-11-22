
#ifndef RENDERER_H
#define RENDERER_H

#include <GL\glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
#define glCall(x) \
    glClearError(); \
    x; \
    ASSERT( glLogCall( #x, __FILE__, __LINE__ ) )

void glClearError();
bool glLogCall( const char* function, const char* file, const int line );

#endif // !RENDERER_H
