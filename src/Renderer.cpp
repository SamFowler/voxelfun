#include "Renderer.hpp"
#include <iostream>

#include <fstream>
#include <iostream>

struct ShaderReader
{
    ShaderReader(std::string path);
    std::string source;
};

ShaderReader::ShaderReader(std::string path) 
{   
    std::ifstream inFile(path);
    std::string line;
    std::cout << "reading file: " << path << std::endl;
    if (inFile.is_open())
    {
        while (std::getline(inFile, line))
        {   
            source = source + line + "\n";
        }
        inFile.close();
    }
    else
    {
        std::cout << "Could not open file " << path << std::endl;
    }
}

static unsigned int CompileShader(unsigned int type, const std::string& sourcePath) 
{
    unsigned int id = glCreateShader(type);

    ShaderReader reader = ShaderReader(sourcePath);
    const GLchar* const shaderSourcePtr = reader.source.c_str();
    //const GLint shaderSourceLength = source.length();

    glShaderSource(id, 1, &shaderSourcePtr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl << message << std::endl;
        glDeleteShader(id);
        return 0;
    } else {
        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compiled successfully" << std::endl;
    }

    return id;
}

static unsigned int CreateShader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderPath);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

bool Renderer::Init(int win_width = 640, int win_height = 480) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL could not initialise. SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    m_window = sdl_shared(SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            win_width, win_height,
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_OPENGL
            ));

    if (m_window == nullptr) {
        std::cout << "Could not create window. SDL error: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    SDL_GLContext context = SDL_GL_CreateContext(m_window.get());

    if (context == NULL) {
        std::cout << "OpenGL context could not be created. SDL error: " << SDL_GetError() << std::endl;
    }
    //TODO: check for no gl context error

    std::cout << "Renderer successfully initialised with window width " << win_width << " and height " << win_height << std::endl;


    //Initialise GLEW
    glewExperimental = GL_TRUE; //TODO: do we want/need this?
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cout << "Glew could not be initialised. Glew error: " << glewGetErrorString(glewError) << std::endl;
    }

    //Set vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
       std::cout << "Unable to set VSync. SDL error: " << SDL_GetError() << std::endl;
    }

    //Vertex Array Object to store links between attributes and VBOs
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Vertex Buffer Object to send vertex data to GPU
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), m_positions, GL_STATIC_DRAW); //6 because positions is triangle at the moment

    const char* vertexSrc = R"glsl(
            #version 330 core
     
            in vec2 position;
            
            void main()
            {
                gl_Position = vec4(position, 0.0, 1.0);
            }
            )glsl";
    const char* fragSrc = R"glsl(
        #version 330 core
        
        out vec4 outColour;
        
        void main()
        {
            outColour = vec4(1.0, 1.0, 1.0, 1.0);
        }
        )glsl";

    //unsigned int shaderProgram = CreateShader(vertexSrc, fragSrc);
    unsigned int shaderProgram = CreateShader("shaders/cube_vert.glsl", "shaders/cube_frag.glsl");
    glUseProgram(shaderProgram);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);


    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "Test shader used" << std::endl;



    return true;

}

void Renderer::Draw() {
    //std::cout << "Drawing game" << std::endl;

   // glClearColor(0.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);



    glDrawArrays(GL_TRIANGLES, 0, 3);
    

    SDL_GL_SwapWindow(m_window.get());
}