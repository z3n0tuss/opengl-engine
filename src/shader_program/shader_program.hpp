#include <GL/glew.h>
#include <stdio.h>
#include <cstring>
#include <map>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
    public:
        ShaderProgram(const char* vertexCode, const char* fragmentCode);
        ~ShaderProgram();

        bool initialise();
        void load();
        void unload();
        
        // Add a uniform to the shader
        void addUniform(const char* name);

        // Lets us pass a value to the shader
        void setMatrix4UniformValue(const char* name, glm::mat4 value);

    private:
        GLuint shaderProgramId;
        const char* vertexCode;
        const char* fragmentCode;

        std::map<const char*, unsigned int> uniforms;

        bool registerShader(const char* source, GLenum shaderType);

        // Error handling stuff (errors during shader compilation / linking are put into this)
        GLint result = 0;
        GLchar errorLog[1024] = { 0 };
};