#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include "Log.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


static std::string parseShader( const std::string& filePath )
{
    std::ifstream fileStream( filePath );
    return std::string( (   std::istreambuf_iterator<char>( fileStream )    ),
                            std::istreambuf_iterator<char>()                );
}

static uint32_t compileShader( const uint32_t type, const std::string& source )
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
        std::cout << "Failed to compile shader." << std::endl;
        std::cout << message << std::endl;
        glCall( glDeleteShader( id ) );
        return 0;
    }

    return id;
}

static uint32_t createShader( const std::string& vShader, const std::string& fShader )
{
    glCall( uint32_t program = glCreateProgram() );

    glCall( uint32_t vs = compileShader( GL_VERTEX_SHADER, vShader ) );
    glCall( uint32_t fs = compileShader( GL_FRAGMENT_SHADER, fShader ) );

    glCall( glAttachShader( program, vs ) );
    glCall( glAttachShader( program, fs ) );

    glCall( glLinkProgram( program ) );
    glCall( glValidateProgram( program ) );

    glCall( glDeleteShader( vs ) );
    glCall( glDeleteShader( fs ) );

    return program;
}

void renderLoop( GLFWwindow* window );

static GLFWwindow* createContext();

int main()
{
    spdlog::set_level( spdlog::level::trace );
    GLFWwindow* window = createContext();
    renderLoop( window );
    return 0;
}

static GLFWwindow* createContext()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return nullptr;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "openGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval( 1 );

    if( GLEW_OK != glewInit() )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        assert( true );
        return nullptr;
    }

    return window;
}

void renderLoop( GLFWwindow* window )
{

    vertex_t vertexBufferData[] = {
        { CardinalLocationIdx::SW, 0.75f },
        { CardinalLocationIdx::SE, 0.75f },
        { CardinalLocationIdx::N,  0.00f },
        { CardinalLocationIdx::NW, 0.75f },
        { CardinalLocationIdx::NE, 0.75f }
    };

    const size_t indexCount = 6;
    index_t indexBufferData[ indexCount ] = {
        0, 3, 2,
        1, 4, 2
    };

    // Create & bind vertex array
    VertexArray vArray;
    VertexBuffer vBuffer( vertexBufferData, sizeof( vertexBufferData ) );
    VertexBufferLayout vBufferLayout;
    vBufferLayout.push<float>( 2 );
    vArray.AddBuffer( vBuffer, vBufferLayout );

    // Create & bind index buffer
    IndexBuffer iBuffer( indexBufferData, indexCount );

    // Compile shaders
    std::string vShader = parseShader( "res/shaders/vertex.shader" );
    std::string fShader = parseShader( "res/shaders/fragment.shader" );
    uint32_t shaderProgram = createShader( vShader, fShader );
    glCall( glUseProgram( shaderProgram ) );
    glCall( int u_Color = glGetUniformLocation( shaderProgram, "u_Color" ) );
    ASSERT( u_Color != -1 );

    // Initialize loop variables
    float r         = 0.00f;
    float r_inc     = 0.05f;

    // Reset bindings
    glCall( glUseProgram( 0 ) );
    glCall( glBindVertexArray( 0 ) );
    glCall( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
    glCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) );

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Update loop variables
        if( !( 0.0f <= r && r <= 1.0f ) )
        {
            r_inc *= -1;
        }
        r += r_inc;

        glCall( glUseProgram( shaderProgram ) );
        glUniform4f( u_Color, r, 0.0f, 0.0f, 1.0f );

        // Bind vertex array & index buffer
        vArray.bind();
        iBuffer.bind();

        // Draw
        glCall( glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr ) );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}