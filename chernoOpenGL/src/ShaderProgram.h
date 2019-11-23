#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>
#include <unordered_map>

class ShaderProgram
{
private:

    uint32_t mRendererId;
    std::unordered_map<std::string, int32_t> mUniformLocations;
    #if DEBUG
        std::string mVertexFilePath;
        std::string mFragmentFilePath;
    #endif

public:

    ShaderProgram( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath );
    ~ShaderProgram();

    void bind() const;
    void unbind() const;

    void setUniform4f( const std::string& name, const float f0, const float f1, const float f2, const float f3 );

private:

    static std::string parseShader( const std::string& filePath );
    static uint32_t compileShader( const uint32_t type, const std::string& source );
    static uint32_t createShaderProgram( const std::string& vertexShader, const std::string& fragmentShader );

    int32_t getUniformLocation( const std::string& uniformName );

};

#endif