#include "ShaderProgram.h"

#include <fstream>
#include <string>

#include "Renderer.h"
#include "Log.h"

ShaderProgram::ShaderProgram(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath)
{
    std::string vertexShaderSrc     = ShaderProgram::parseShader( vertexShaderFilePath );
    std::string fragmentShaderSrc   = ShaderProgram::parseShader( fragmentShaderFilePath );
    this->mRendererId               = ShaderProgram::createShaderProgram( vertexShaderSrc, fragmentShaderSrc );
    this->bind();
}

ShaderProgram::~ShaderProgram()
{
    glCall( glDeleteProgram( this->mRendererId ) );
}

void ShaderProgram::bind() const
{
    glCall( glUseProgram( this->mRendererId ) );
}

void ShaderProgram::unbind() const
{
    glCall( glUseProgram( 0 ) );
}

void ShaderProgram::setUniform4f(const std::string& name, const float f0, const float f1, const float f2, const float f3)
{
    int32_t location = this->getUniformLocation( name ); // may want to only get location once
    glUniform4f( location, f0, f1, f2, f3 );
}

std::string ShaderProgram::parseShader(const std::string & filePath)
{
    std::ifstream fileStream( filePath );
    return std::string( (   std::istreambuf_iterator<char>( fileStream )    ),
                            std::istreambuf_iterator<char>()                );
}

uint32_t ShaderProgram::compileShader( const uint32_t type, const std::string& source )
{
    glCall( uint32_t id = glCreateShader( type ) );
    const char* const src = source.c_str();
    glCall( glShaderSource( id, 1, &src, nullptr ) );
    glCall( glCompileShader( id ) );

    int result;
    glCall(  glGetShaderiv( id, GL_COMPILE_STATUS, &result ) );
    if( GL_FALSE == result )
    {
        int length;
        glCall( glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length ) );
        char* message = ( char* )alloca( length * sizeof( char ) );
        glCall( glGetShaderInfoLog( id, length, &length, message ) );
        LOGE( "Failed to compile shader." );
        LOGE( message );
        glCall( glDeleteShader( id ) );
        return 0;
    }

    return id;
}

uint32_t ShaderProgram::createShaderProgram( const std::string& vShader, const std::string& fShader )
{
    glCall( uint32_t program = glCreateProgram() );

    glCall( uint32_t vs = ShaderProgram::compileShader( GL_VERTEX_SHADER, vShader ) );
    glCall( uint32_t fs = ShaderProgram::compileShader( GL_FRAGMENT_SHADER, fShader ) );

    glCall( glAttachShader( program, vs ) );
    glCall( glAttachShader( program, fs ) );

    glCall( glLinkProgram( program ) );
    glCall( glValidateProgram( program ) );

    glCall( glDeleteShader( vs ) );
    glCall( glDeleteShader( fs ) );

    return program;
}

int32_t ShaderProgram::getUniformLocation(const std::string & uniformName)
{
    const auto& uniformLocation = this->mUniformLocations.find( uniformName );
    if( uniformLocation != this->mUniformLocations.end() )
    {
        return uniformLocation->second;
    }

    glCall( int32_t location = glGetUniformLocation( this->mRendererId, uniformName.c_str() ) );
    if( -1 == location )
    {
        LOGW( "Uniform {} does not exist", uniformName );
    }
    this->mUniformLocations[ uniformName ] = location;
    return location;
}

