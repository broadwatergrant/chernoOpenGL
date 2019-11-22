#include "VertexBuffer.h"

#include "Renderer.h"
#include "spdlog\spdlog.h"

const vertex_t cardinalLocations[ static_cast<uint32_t>( CardinalLocationIdx::Count ) ] = {
    { /* SW */  -1.0f,  -1.0f },
    { /* S  */   0.0f,  -1.0f },
    { /* SE */  +1.0f,  -1.0f },
    { /* E  */  +1.0f,   0.0f },
    { /* NE */  +1.0f,  +1.0f },
    { /* N  */   0.0f,  +1.0f },
    { /* NW */  -1.0f,  +1.0f },
    { /* W  */  -1.0f,   0.0f }
};

 vertex_t::vertex_t( const CardinalLocationIdx cardinalLocationIdx, const float scaler  )
    : vertex_t(
        /* x */ cardinalLocations[ static_cast<uint32_t>( cardinalLocationIdx ) ].x * scaler,
        /* y */ cardinalLocations[ static_cast<uint32_t>( cardinalLocationIdx ) ].y * scaler
    )
{}

VertexBuffer::VertexBuffer(const void * data, const size_t size)
{
    glCall( glGenBuffers( 1, &this->mRendererId ) );
    this->bind();
    glCall( glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW ) );

    #if DEBUG
        this->mData = malloc( size );
        memcpy( this->mData, data, size );
        this->mDataSize = size;
    #endif

    spdlog::debug( "Created vertex buffer {} of size {}", this->mRendererId, size );
}

VertexBuffer::~VertexBuffer()
{
    glCall( glDeleteBuffers( 1, &this->mRendererId ) );
}

void VertexBuffer::bind() const
{
    glCall( glBindBuffer( GL_ARRAY_BUFFER, this->mRendererId ) );
}

void VertexBuffer::unbind() const
{
    glCall( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
}

#if DEBUG

    const void *VertexBuffer::getData() const
    {
    return this->mData;
    }

    size_t VertexBuffer::getDataSize() const
    {
        return this->mDataSize;
    }
#endif