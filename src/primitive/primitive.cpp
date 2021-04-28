#include "primitive.hpp"

Primitive::Primitive(float vertices[], int vertexCount) {
    initialise(vertices, vertexCount);
}

Primitive::~Primitive() {

}

void Primitive::initialise(float vertices[], int vertexCount) {
    generateAndBindVertexArray();
    generateAndBindBuffers();
    bindVertexDataToBuffer(vertices, vertexCount);
    createAndEnableVertexAttribPointers();
    unbind();
}

void Primitive::generateAndBindVertexArray() {
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
}

void Primitive::generateAndBindBuffers() {
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
}

void Primitive::bindVertexDataToBuffer(float vertices[], int vertexCount) {
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertices, GL_STATIC_DRAW);
}

// This stores an attribute in location 0 which contains the x, y and z co-ordinates. Then we can retrieve this in the shader using (location = 0)
void Primitive::createAndEnableVertexAttribPointers() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void Primitive::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::mat4 Primitive::getModelMatrix() {
    return modelMatrix;
}

void Primitive::tick() {

    xSpeed = xSpeed + 0.0000000000005;

    // Moving the object by applying a translate to it on the x axis ( a translate is a move )
    modelMatrix = glm::translate(modelMatrix, glm::vec3(xSpeed, 0.0f, 0.0f));
}

void Primitive::draw() {
    glBindVertexArray(vaoId);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}