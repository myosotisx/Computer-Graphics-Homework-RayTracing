#ifndef VERTICES_H
#define VERTICES_H

#include <glad/glad.h>


class VerticesContainer {
public:
    virtual void loadVertices() = 0;
};


float verticesPlane[] = {
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
};

float verticesCube[] ={
    // front
    0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
    1.0f, 0.0f, 1.0f,  1.0f,  0.0f,
    1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    0.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    0.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    // back
    1.0f, 0.0f, 0.0f,  0.0f,  0.0f,
    0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
    1.0f, 0.0f, 0.0f,  0.0f,  0.0f,

    // left
    0.0f, 0.0f, 0.0f,  0.0f,  0.0f,
    0.0f, 0.0f, 1.0f,  1.0f,  0.0f,
    0.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    0.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
    0.0f, 0.0f, 0.0f,  0.0f,  0.0f,

    // right
    1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
    1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    1.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    1.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    // top
    0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
    1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
    1.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    1.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
    0.0f, 1.0f, 1.0f,  0.0f,  0.0f,

    // down
    0.0f, 0.0f, 0.0f,  0.0f,  0.0f,
    1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    1.0f, 0.0f, 1.0f,  1.0f,  1.0f,
    1.0f, 0.0f, 1.0f,  1.0f,  1.0f,
    0.0f, 0.0f, 1.0f,  0.0f,  1.0f,
    0.0f, 0.0f, 0.0f,  0.0f,  0.0f,
};

float verticesPyramid[] ={
    // front
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    0.5f, 1.0f, 0.5f,  0.5f, 1.0f,

    // back
    1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    0.5f, 1.0f, 0.5f,  0.5f, 1.0f,

    // left
    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    0.5f, 1.0f, 0.5f,  0.5f, 1.0f,

    // right
    1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    0.5f, 1.0f, 0.5f,  0.5f, 1.0f,

    // down
    0.0f, 0.0f, 0.0f,  0.0f,  0.0f,
    1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    1.0f, 0.0f, 1.0f,  1.0f,  1.0f,
    1.0f, 0.0f, 1.0f,  1.0f,  1.0f,
    0.0f, 0.0f, 1.0f,  0.0f,  1.0f,
    0.0f, 0.0f, 0.0f,  0.0f,  0.0f,
};

float verticesDiamond[] ={
    // front up
    0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    0.5f, 2.0f, 0.5f,  0.5f, 1.0f,

    // back up
    1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.5f, 2.0f, 0.5f,  0.5f, 1.0f,

    // left up
    0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    0.5f, 2.0f, 0.5f,  0.5f, 1.0f,

    // right up
    1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.5f, 2.0f, 0.5f,  0.5f, 1.0f,

    // front down
    1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    0.5f, 0.0f, 0.5f,  0.5f, 1.0f,

    // back down
    0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.5f, 0.0f, 0.5f,  0.5f, 1.0f,

    // left down
    0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.5f, 0.0f, 0.5f,  0.5f, 1.0f,

    // right down
    1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    0.5f, 0.0f, 0.5f,  0.5f, 1.0f,
};


class Vertices: public VerticesContainer {
private:
    static Vertices *planeVertices, *cubeVertices, *pyramidVertices, *diamonVertices;
public:
    int verticesNum, bufLength, attribNum, *attribLengths;
    unsigned int VAO, VBO;
    float *vertices;
    Vertices(int _verticesNum, int _bufLength, int _attribNum, int _attribLengths[], float _vertices[])
        : verticesNum(_verticesNum),
          bufLength(_bufLength),
          vertices(_vertices),
          attribNum(_attribNum) {

        attribLengths = new int[attribNum];
        for(int i=0; i<attribNum; i++) {
            attribLengths[i] = _attribLengths[i];
        }
    }
    static Vertices* getPlaneVertices() {
        if(!planeVertices) {
            int length[] ={3, 2};
            planeVertices = new Vertices(6, 5, 2, length, verticesPlane);
        }
        return planeVertices;
    }
    static Vertices* getCubeVertices() {
        if(!cubeVertices) {
            int lengths[] ={3, 2};
            cubeVertices = new Vertices(36, 5, 2, lengths, verticesCube);
        }
        return cubeVertices;
    }
    static Vertices* getPyramidVertices() {
        if(!pyramidVertices) {
            int lengths[] ={3, 2};
            pyramidVertices = new Vertices(18, 5, 2, lengths, verticesPyramid);
        }
        return pyramidVertices;
    }
    static Vertices* getDiamondVertices() {
        if(!diamonVertices) {
            int lengths[] ={3, 2};
            diamonVertices = new Vertices(18, 5, 2, lengths, verticesDiamond);
        }
        return diamonVertices;
    }
    void loadVertices() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesNum*bufLength*sizeof(float), vertices, GL_STATIC_DRAW);
        int offset = 0;
        for(int j=0; j<attribNum; j++) {
            glVertexAttribPointer(j, attribLengths[j], GL_FLOAT, GL_FALSE, bufLength*sizeof(float), (void*)(offset*sizeof(float)));
            glEnableVertexAttribArray(j);
            offset += attribLengths[j];
        }
    }
    void Draw(Shader &shader) {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, verticesNum);
    }
};
Vertices* Vertices::planeVertices = nullptr;
Vertices* Vertices::cubeVertices = nullptr;
Vertices* Vertices::pyramidVertices = nullptr;
Vertices* Vertices::diamonVertices = nullptr;
#endif