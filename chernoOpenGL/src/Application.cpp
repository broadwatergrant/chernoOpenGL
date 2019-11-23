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
#include "ShaderProgram.h"

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
    ShaderProgram shaderProgram( "res/shaders/vertex.shader", "res/shaders/fragment.shader" );
    Renderer renderer;

    // Initialize loop variables
    float r         = 0.00f;
    float r_inc     = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();

        // Update loop variables
        if( !( 0.0f <= r && r <= 1.0f ) )
        {
            r_inc *= -1;
        }
        r += r_inc;

        shaderProgram.setUniform4f( "u_Color", r, 0.0f, 0.0f, 1.0f );
        renderer.draw( vArray, iBuffer, shaderProgram );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}