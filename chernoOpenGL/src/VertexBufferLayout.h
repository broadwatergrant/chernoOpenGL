#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <GL\glew.h>

#include <vector>

#include "Renderer.h"

struct VertexBufferElement
{
    uint32_t type;
    size_t count;
    bool normalized;

    uint32_t typeSize() const
    {
        switch( type )
        {
        case GL_FLOAT:
            return sizeof( float );
        case GL_UNSIGNED_INT:
            return sizeof( uint32_t );
        case GL_UNSIGNED_BYTE:
            return sizeof( unsigned char );
        default:
            ASSERT( false );
            return 0;
        }
    }
};

class VertexBufferLayout
{
private:

    std::vector<VertexBufferElement> mElements;
    uint32_t mStride;

public:

    VertexBufferLayout()
        : mElements()
        , mStride( 0 )
    {}

    template <typename T>
    void push( size_t count )
    {
        static_assert( false );
    }

    template <>
    void push<float>( size_t count )
    {
        this->mElements.push_back( { GL_FLOAT, count, false } );
        mStride += this->mElements[ this->mElements.size() - 1 ].typeSize() * count;
    }

    template <>
    void push<uint32_t>( size_t count )
    {
        this->mElements.push_back( { GL_UNSIGNED_INT, count, false } );
        mStride += this->mElements[ this->mElements.size() - 1 ].typeSize() * count;
    }

    template <>
    void push<unsigned char>( size_t count )
    {
        this->mElements.push_back( { GL_UNSIGNED_BYTE, count, true } );
        mStride += this->mElements[ this->mElements.size() - 1 ].typeSize() * count;
    }

    inline const std::vector<VertexBufferElement> getElements() const { return this->mElements; }
    inline uint32_t getStride() const { return this->mStride; }
};

#endif // !VERTEX_BUFFER_LAYOUT_H
