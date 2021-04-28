#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "../primitive/primitive.hpp"
#include "../shader_program/shader_program.hpp"

class Window {
    public:
        ~Window();

        bool initialise(int w, int h, const std::string& windowName);
        void run();

    private:
        GLFWwindow *window;

        void setWindowHints();
        bool initialiseGlew();
};