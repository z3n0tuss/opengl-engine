#include "GL/glew.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Primitive {
    private:
        GLuint vaoId;
        GLuint vboId;
        bool left = true;
        float xSpeed = 0.005;

        // This model matrix will store the position, rotation and scale of the primitive.
        // We will apply transformations to this using glm which is how we will apply transforms.
        glm::mat4 modelMatrix{1.0f};

        void initialise(float vertices[], int vertexCount);

        void generateAndBindVertexArray();
        void generateAndBindBuffers();
        void bindVertexDataToBuffer(float vertices[], int vertexCount);
        void createAndEnableVertexAttribPointers();
        void unbind();

    public:
        Primitive(float vertices[], int vertexCount);
        ~Primitive();

        void tick();
        void draw();

        glm::mat4 getModelMatrix();
};