#ifndef VBH
#define VBH

#include <cstdint>

typedef uint32_t index_t;

class IndexBuffer {
private:

    uint32_t mRendererId;
    uint32_t mCount;

public:

    IndexBuffer( const index_t* data, const size_t count );
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline uint32_t getCount() const { return mCount; }

};

#endif // !VBH
