#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.h"
#include "material.h"
#include "vertices.h"


enum ObjectType {
    STATIC,
    DYNAMIC
};

class Object {
public:
    glm::vec3 position;
    glm::vec3 offset;
    glm::vec3 scale;
    glm::vec3 rotate;
    Material *mat;
    ObjectType type;
    VerticesContainer *container;
    Object(
        VerticesContainer *_container, 
        const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f), 
        const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f, 0.0f), 
        ObjectType _type=STATIC, 
        Material *_mat=nullptr
    )
        : container(_container),
          position(_position),
          offset(_offset),
          scale(_scale),
          rotate(_rotate),
          mat(_mat),
          type(_type) {

        if(!mat) {
            mat = Material::getBlackMaterial();
        }
    }
    virtual ~Object() {}
    glm::mat4 getModelMatrix(float time) {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, position);
        trans = glm::scale(trans, scale);
        trans = glm::rotate(trans, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::rotate(trans, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::rotate(trans, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
        trans = glm::translate(trans, offset);
        return trans;
    }
    void setMaterial(Material *_mat) { mat = _mat; }
    const Material* getMaterial() { return mat; }
    virtual float rayIntersect(const Ray& ray, glm::vec3& fragPos, glm::vec3& norm, bool& outter, float tmin=FLOAT_INF) = 0;
};


class AABB {
public:
    glm::vec3 min, max;
    AABB()
        : min(FLOAT_INF_VEC3),
          max(-FLOAT_INF_VEC3) {}
    bool AABBcollide(const AABB& object) {
        bool xCollide = (object.min.x >= min.x && object.min.x <= max.x) || (min.x >= object.min.x && min.x <= object.max.x);
        bool yCollide = (object.min.y >= min.y && object.min.y <= max.y) || (min.y >= object.min.y && min.y <= object.max.y);
        bool zCollide = (object.min.z >= min.z && object.min.z <= max.z) || (min.z >= object.min.z && min.z <= object.max.z);
        return xCollide && yCollide && zCollide;
    }
    bool rayIntersectAABB(const Ray& ray, float tmin=-FLOAT_INF, float tmax=FLOAT_INF) {
        float t0, t1;
        for(int i=0; i<3; i++) {
            t0 = (min[i]-ray.origin[i])/ray.dir[i];
            t1 = (max[i]-ray.origin[i])/ray.dir[i];
            if(ray.dir[i] < 0.0f) {
                std::swap(t0, t1);
            }
            tmax = std::min(t1, tmax);
            tmin = std::max(t0, tmin);
            if(tmax <= tmin) return false;
        }
        return true;
    }
    virtual void calcAABB() = 0;
};


class VerticesObject: public Object, public AABB {
public:
    int verticesNum, bufLength;
    Vertices *vertices;
    std::vector<glm::vec3> staticVertices;
    VerticesObject(
        Vertices *_vertices, 
        const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f), 
        const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f ,0.f)
    )
        : Object(_vertices, _position, _offset, _scale),
          vertices(_vertices) {
        
        verticesNum = vertices->verticesNum;
        bufLength = vertices->bufLength;
        calcAABB();
        if(type == STATIC) {
            glm::mat4 trans = getModelMatrix(float(glfwGetTime()));
            for(int i=0; i<verticesNum; i++) {
                glm::vec3 vertex = trans*glm::vec4(vertices->vertices[i*bufLength], vertices->vertices[i*bufLength+1], vertices->vertices[i*bufLength+2], 1.0f);
                staticVertices.push_back(vertex);
            }
        }
    }
    ~VerticesObject() {}
    float rayIntersect(const Ray& ray, glm::vec3& fragPos, glm::vec3& norm, bool& outter, float tmin=FLOAT_INF) {
        glm::mat4 trans = glm::mat4(1.0f); 
        if(type == DYNAMIC) {
            trans = getModelMatrix(float(glfwGetTime()));
        }
        glm::vec3 _norm;
        glm::vec3 _fragPos;
        bool _outter;
        glm::vec3 v0, v1, v2;
        float t1, t2; // dummy

        for(int i=0; i<verticesNum; i+=3) {
            if(type == STATIC) {
                v0 = staticVertices[i];
                v1 = staticVertices[i+1];
                v2 = staticVertices[i+2];
            }
            else {
                v0 = trans*glm::vec4(vertices->vertices[i*bufLength],
                    vertices->vertices[i*bufLength+1],
                    vertices->vertices[i*bufLength+2],
                    1.0f);
                v1 = trans*glm::vec4(vertices->vertices[(i+1)*bufLength],
                    vertices->vertices[(i+1)*bufLength+1],
                    vertices->vertices[(i+1)*bufLength+2],
                    1.0f);
                v2 = trans*glm::vec4(vertices->vertices[(i+2)*bufLength],
                    vertices->vertices[(i+2)*bufLength+1],
                    vertices->vertices[(i+2)*bufLength+2],
                    1.0f);
            }

            float t = ray.triangleIntersect(v0, v1, v2, _fragPos, _norm, _outter, t1, t2, tmin);
            if(t <= 0.0f) continue;
            tmin = t;
            norm = _norm;
            fragPos = _fragPos;
            outter = _outter;
        }
        return tmin;
    }
    void calcAABB() {
        glm::mat4 trans = getModelMatrix(float(glfwGetTime()));
        int n = verticesNum*bufLength;
        for(int i=0; i<n; i+=bufLength) {
            glm::vec3 v = trans*glm::vec4(vertices->vertices[i], vertices->vertices[i+1], vertices->vertices[i+2], 1.0f);

            if(v.x < min.x) min.x = v.x;
            if(v.y < min.y) min.y = v.y;
            if(v.z < min.z) min.z = v.z;

            if(v.x > max.x) max.x = v.x;
            if(v.y > max.y) max.y = v.y;
            if(v.z > max.z) max.z = v.z;
        }

        min -= FLOAT_EPS_VEC3;
        max += FLOAT_EPS_VEC3;
    }
};


class ModelObject: public Object, public AABB {
public:
    Model *model;
    std::vector<Vertex> staticVertices;
    ModelObject(
        Model *_model, 
        const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f), 
        const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f, 0.0f)
    )
        : Object(_model, _position, _offset, _scale, _rotate),
          model(_model) {
       
        calcAABB();
        if(type == STATIC) {
            glm::mat4 trans = getModelMatrix(float(glfwGetTime()));
            glm::mat3 transNorm = glm::mat3(glm::transpose(glm::inverse(trans)));
            for(const Mesh& mesh: model->meshes) {
                for(const Vertex& vertex: mesh.vertices) {
                    Vertex _vertex(vertex);
                    _vertex.Position = trans*glm::vec4(vertex.Position, 1.0f);
                    _vertex.Normal = glm::normalize(transNorm*vertex.Normal);
                    staticVertices.push_back(_vertex);
                }
            }
        }
    }
    ~ModelObject() {}
    float rayIntersect(const Ray& ray, glm::vec3& fragPos, glm::vec3& norm, bool& outter, float tmin=FLOAT_INF) {
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat3 transNorm = glm::mat3(1.0f);
        if(type == DYNAMIC) {
            trans = getModelMatrix(float(glfwGetTime()));
            transNorm = glm::mat3(glm::transpose(glm::inverse(trans)));
        }
        glm::vec3 _norm;
        glm::vec3 _fragPos;
        bool _outter;
        glm::vec3 v0, v1, v2;
        float t1, t2;

        for(const Mesh& mesh: model->meshes) {
            int n = mesh.indices.size();
            for(int i=0; i<n; i+=3) {
                if(type == STATIC) {
                    v0 = staticVertices[mesh.indices[i]].Position;
                    v1 = staticVertices[mesh.indices[i+1]].Position;
                    v2 = staticVertices[mesh.indices[i+2]].Position;
                }
                else {
                    v0 = trans*glm::vec4(mesh.vertices[mesh.indices[i]].Position, 1.0f);
                    v1 = trans*glm::vec4(mesh.vertices[mesh.indices[i+1]].Position, 1.0f);
                    v2 = trans*glm::vec4(mesh.vertices[mesh.indices[i+2]].Position, 1.0f);
                }

                float t = ray.triangleIntersect(v0, v1, v2, _fragPos, _norm, _outter, t1, t2, tmin);
                if(t <= 0.0f) continue;
                tmin = t;
                //norm = _norm;

                if(type == STATIC) {
                    norm = glm::normalize((1.0f - t1 - t2)*staticVertices[mesh.indices[i]].Normal
                        + t1*staticVertices[mesh.indices[i+1]].Normal
                        + t2*staticVertices[mesh.indices[i+2]].Normal);
                }
                else {
                    norm = glm::normalize((1.0f - t1 - t2)*(transNorm*mesh.vertices[mesh.indices[i]].Normal)
                        + t1*(transNorm*mesh.vertices[mesh.indices[i+1]].Normal)
                        + t2*(transNorm*mesh.vertices[mesh.indices[i+2]].Normal));
                }
                fragPos = _fragPos;
                outter = _outter;
            }
        }
        return tmin;
    }
    void calcAABB() {
        glm::mat4 trans = getModelMatrix(float(glfwGetTime()));
        for(const Mesh& mesh: model->meshes) {
            int n = mesh.vertices.size();
            for(int i=0; i<n; i++) {
                glm::vec3 v = trans*glm::vec4(mesh.vertices[i].Position, 1.0f);

                if(v.x < min.x) min.x = v.x;
                if(v.y < min.y) min.y = v.y;
                if(v.z < min.z) min.z = v.z;

                if(v.x > max.x) max.x = v.x;
                if(v.y > max.y) max.y = v.y;
                if(v.z > max.z) max.z = v.z;
            }
        }

        min -= FLOAT_EPS_VEC3;
        max += FLOAT_EPS_VEC3;
    }
};
#endif
