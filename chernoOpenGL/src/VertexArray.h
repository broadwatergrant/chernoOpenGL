
#ifndef VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:

    uint32_t mRendererId;

public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void AddBuffer( const VertexBuffer& aVertexBuffer, const VertexBufferLayout& aLayout );
};

#endif // !VERTEX_ARRAY_H
