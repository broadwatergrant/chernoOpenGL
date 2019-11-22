
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <cstdint>

enum class CardinalLocationIdx: uint32_t {
    SW  = 0,
    S   = 1,
    SE  = 2,
    E   = 3,
    NE  = 4,
    N   = 5,
    NW  = 6,
    W   = 7,

    Count
};

typedef float position_t;
struct vertex_t {

    position_t x;
    position_t y;

    vertex_t( const position_t x, const position_t y ) : x( x ), y( y ) {}

    vertex_t() : vertex_t( 0, 0 ) {}

    vertex_t( const CardinalLocationIdx cardinalLocationIdx, const float scaler = 1  );
};

class VertexBuffer {
private:

    uint32_t mRendererId;
    #if DEBUG
        void* mData;
        size_t mDataSize;
    #endif

public:

    VertexBuffer( const void* data, const size_t size );
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    inline const uint32_t getRendererId() const { return this->mRendererId; }

    #if DEBUG
        const void *getData() const;
        size_t getDataSize() const;
    #endif

};

#endif // !VERTEX_BUFFER_H
