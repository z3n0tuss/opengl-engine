#include "shader_program.hpp"

ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource)  {
    vertexCode = vertexSource;
    fragmentCode = fragmentSource;
};

ShaderProgram::~ShaderProgram() {

}

bool ShaderProgram::initialise() {
    shaderProgramId = glCreateProgram();

    if (!shaderProgramId) {
        printf("Error creating shader program.");
        return false;
    }

    if(!registerShader(vertexCode, GL_VERTEX_SHADER)) {
        printf("Error creating vertex shader.");
        return false;
    };

    if (!registerShader(fragmentCode, GL_FRAGMENT_SHADER)) {
        printf("Error creating fragment shader.");
        return false;
    }

    glLinkProgram(shaderProgramId);

     // Check for any errors with linking
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &result);

    if(!result) {
        glGetProgramInfoLog(shaderProgramId, sizeof(errorLog), nullptr, errorLog);
        printf("Error linking shader program | '%s'\n", errorLog);
        return false;
    }

    // Check if shader program is valid
    glValidateProgram(shaderProgramId);

    // Check for any errors with validation
    glGetProgramiv(shaderProgramId, GL_VALIDATE_STATUS, &result);

    if(!result) {
        glGetProgramInfoLog(shaderProgramId, sizeof(errorLog), nullptr, errorLog);
        printf("Error validating shader program | '%s'\n", errorLog);
        return false;
    }

    printf("Successfully registered shader program with id: %d\n", shaderProgramId);
    return true;
}

bool ShaderProgram::registerShader(const char* source, GLenum shaderType) {
    printf("Registering shader with source...\n");
    printf("%s\n\n", source);

    GLuint shaderId = glCreateShader(shaderType);

    // This is weird?? Why store it in an array? But this is what they want 
    const GLchar* shaderCodeContainer[] = {
        source
    };

     // Another weird array
    GLint codeLengthContainer[1] = {
        strlen(source)
    };

    glShaderSource(shaderId, 1, shaderCodeContainer, codeLengthContainer);
    glCompileShader(shaderId);

    // Check for any errors with validation
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if(!result) {
        glGetShaderInfoLog(shaderId, sizeof(errorLog), nullptr, errorLog);
        printf("%s", errorLog);
        printf("Error compiling %d shader | '%s'\n", shaderType, errorLog);
        return false;
    }

    glAttachShader(shaderProgramId, shaderId);

    // Delete the shader once it's linked to the program as we don't need it anymore
    glDeleteShader(shaderId);

    return true;
}

void ShaderProgram::addUniform(const char* name) {
    load();
    GLint location = glGetUniformLocation(shaderProgramId, name);
    printf("Registered uniform %s with location: %d\n", name, location);
    uniforms[name] = location;
    unload();
}

void ShaderProgram::setMatrix4UniformValue(const char* name, glm::mat4 value) {
    glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::load() {
    glUseProgram(shaderProgramId);
}

void ShaderProgram::unload() {
    glUseProgram(0);
}