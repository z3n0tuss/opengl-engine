#include "window.hpp"
#include <list>

// Vertex shader
static const char* vShader = "\n\
    #version 330 \n\
    layout (location = 0) in vec3 pos; \n\
    uniform mat4 modelMatrix; \n\
    \n\
    void main() { \n\
        gl_Position = modelMatrix * vec4(pos.x * 0.4, pos.y * 0.4, pos.z, 1.0);             \n\
    }";

// Fragment shader
static const char* fragmentShader = "\n\
    #version 330 \n\
    out vec4 color; \n\
    \n\
    void main() { \n\
        color = vec4(0.2, 0.4, 0.7, 1.0);             \n\
    }";

std::list<Primitive> primitives;

bool Window::initialise(int w, int h, const std::string& windowName) {
    if (!glfwInit()) {
        printf("GLFW failed to intialise");
        glfwTerminate();
        return false;
    }

    setWindowHints();

    window = glfwCreateWindow(w, h, windowName.c_str(), nullptr, nullptr);

    if (!window)
    {
        printf("GLFW Window creation failed");
        return false;
    }

    if (!initialiseGlew()) {
        return false;
    }

    return true;
}

Window::~Window() {
    glfwDestroyWindow(window);
}

// Sets various global config properties that we want
void Window::setWindowHints() {
    // GLFW 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // No backwards compatibility with old stinky opengl
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Allow forward compatibility with shiny cool opengl tho
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

bool Window::initialiseGlew(){
     // Get dimensions of buffer (the size of the window minus the toolbar and stuff, i.e. the actual surface we draw too)
    int buffer_width, buffer_height;
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);

    // Tie glew opengl context to our window
    glfwMakeContextCurrent(window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        printf("Glew init failed");
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    // Setup viewport size
    glViewport(0, 0, buffer_width, buffer_height);

    return true;
}

void Window::run() {
    float triangle_vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    float triangle_two_vertices[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
    };

    Primitive triangle{triangle_vertices, 9};

    primitives.push_front(triangle);

    ShaderProgram shader_program{vShader, fragmentShader};

    auto initialisationSuccessful = shader_program.initialise();

    // The matrix model is the matrix we use to store the position, rotation and scale of the entity.
    shader_program.addUniform("modelMatrix");

    if (!initialisationSuccessful) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    // Loop until window close
    while(!glfwWindowShouldClose(window))
    {
        // Get and handle user input and events
        glfwPollEvents();

        // clear the window
        glClearColor(0.2f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.load();
        
        std::list<Primitive>::iterator it;

        for(it = primitives.begin(); it != primitives.end(); it++) {
            shader_program.setMatrix4UniformValue("modelMatrix", it->getModelMatrix());
            it->tick();
            it->draw();
        }

        shader_program.unload();

        glfwSwapBuffers(window);
    }

}