#include "VertexArray.h"

#include "Renderer.h"

#include "Log.h"
#if DEBUG
#include <sstream>
#endif

VertexArray::VertexArray()
{
    glCall( glGenVertexArrays( 1, &this->mRendererId ) );

    LOGD( "Created vertex array {}", this->mRendererId );
}

VertexArray::~VertexArray()
{
    glCall( glDeleteVertexArrays( 1, &this->mRendererId ) );
}

void VertexArray::bind() const
{
    glCall( glBindVertexArray( this->mRendererId ) );
}

void VertexArray::unbind() const
{
    glCall( glBindVertexArray( 0 ) );
}

void VertexArray::AddBuffer(const VertexBuffer & aVertexBuffer, const VertexBufferLayout & aLayout)
{
    this->bind();
    aVertexBuffer.bind();
    const auto& elements = aLayout.getElements();
    size_t offset = 0;

    for( size_t i = 0; i < elements.size(); ++i )
    {
        const auto& element = elements[ i ];
        glCall( glEnableVertexAttribArray( static_cast< GLuint >( i ) ) );
        glCall( glVertexAttribPointer(
            static_cast< GLuint >( i ),
            static_cast< GLuint >( element.count ),
            element.type,
            element.normalized ? GL_TRUE : GL_FALSE,
            aLayout.getStride(),
            (const void*) offset
        ) );
        offset += element.count * element.typeSize();
    }

    LOGD( "Vertex array {} added vertex buffer {}", this->mRendererId, aVertexBuffer.getRendererId() );
    #if DEBUG
        const uint8_t *bufferData = (uint8_t *)aVertexBuffer.getData();
        size_t f = 0;
        size_t bufferDataSize = aVertexBuffer.getDataSize();
        const uint8_t *currentData = bufferData;
        for(size_t stride = 0; stride < ( bufferDataSize / aLayout.getStride() ); ++stride )
        {
            std::stringstream vertexStream;
            vertexStream << "\t\tVertex " << stride << ": ( ";
            for( size_t e = 0; e < elements.size(); ++e )
            {
                const auto& element = elements[ e ];
                for(size_t i = 0; i < element.count; i++)
                {
                    switch(element.type)
                    {
                    case GL_FLOAT:
                        vertexStream << *reinterpret_cast<const float *>( currentData ) << " ";
                        break;
                    case GL_UNSIGNED_INT:
                        vertexStream << *reinterpret_cast<const uint32_t *>( currentData ) << " ";
                        break;
                    case GL_UNSIGNED_BYTE:
                        vertexStream << *reinterpret_cast<const uint8_t *>( currentData ) << " ";
                        break;
                    default:
                        break;
                    }

                    currentData += element.typeSize();
                }
            }
            vertexStream << ")";
            LOGT( vertexStream.str() );
        }
    #endif
}
