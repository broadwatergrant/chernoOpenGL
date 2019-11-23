#include "IndexBuffer.h"

#include "Renderer.h"
#include "Log.h"

IndexBuffer::IndexBuffer( const index_t* data, const size_t count )
    : mRendererId( 0 )
    , mCount( count )
{
    ASSERT( sizeof(index_t) == sizeof( GLuint ) );

    glCall( glGenBuffers( 1, &this->mRendererId ) );
    this->bind();
    glCall( glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( index_t ), data, GL_STATIC_DRAW ) );

    LOGD( "Created index buffer {}", this->mRendererId );
    for(size_t i = 0; i < count; ++i)
    {
        LOGT( "\t\tindex {}: {}", i, data[i] );
    }
}

IndexBuffer::~IndexBuffer()
{
    glCall( glDeleteBuffers( 1, &this->mRendererId ) );
}

void IndexBuffer::bind() const
{
    glCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->mRendererId ) );
}

void IndexBuffer::unbind() const
{
    glCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) );
}
