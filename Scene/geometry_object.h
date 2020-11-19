#ifndef GEOMETRY_OBJECT_H
#define GEOMETRY_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.h"


class Cube: public VerticesObject {
public:
    Cube(
        const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f)
    )
        : VerticesObject(Vertices::getCubeVertices(), _position, _offset, _scale) {}
    glm::mat4 getModelMatrix(float time) {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, position);
        trans = glm::scale(trans, scale);
        trans = glm::translate(trans, offset);
        return trans;
    }
};


class Pyramid: public VerticesObject {
public:
    Pyramid(int _verticesNum, int _bufLength, float _vertices[], glm::vec3 _position=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _offset=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale=glm::vec3(1.0f, 1.0f, 1.0f))
        : VerticesObject(Vertices::getPyramidVertices(), _position, _offset, _scale) {}
};


class Diamond: public VerticesObject {
public:
    Diamond(
        const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f),
        const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f, 0.0f)
    )
        : VerticesObject(Vertices::getDiamondVertices(), _position, _offset, _scale, _rotate) {}
};


enum Plane_Face {
    FRONT_FACE,
    BACK_FACE,
    LEFT_FACE,
    RIGHT_FACE,
    TOP_FACE,
    BOTTOM_FACE
};

class Plane : public VerticesObject {
public:
    Plane_Face face;
    Plane(
        Plane_Face _face, 
        const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f)
    )
        : VerticesObject(Vertices::getPlaneVertices(), _position, _offset, _scale),
          face(_face) {
        if(face == FRONT_FACE) {
            rotate = glm::vec3(0.0f, 180.0f, 0.0f);
        }
        else if(face == LEFT_FACE) {
            rotate = glm::vec3(0.0f, 90.0f, 0.0f);
        }
        else if(face == RIGHT_FACE) {
            rotate = glm::vec3(0.0f, 270.0f, 0.0f);
        }
        else if(face == TOP_FACE) {
            rotate = glm::vec3(90.0f, 0.0f, 0.0f);
        }
        else if(face == BACK_FACE) {
            rotate = glm::vec3(270.0f, 0.0f, 0.0f);
        }
    }
};


class Sphere: public Object, AABB {
public:
    float radius;
    Sphere(
        float _radius, const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f))
        : Object(nullptr, _position),
          radius(_radius) {

        calcAABB();
    }

    float rayIntersect(const Ray& ray, glm::vec3& fragPos, glm::vec3& norm, bool& outter, float tmin=FLOAT_INF) {
        glm::vec3 vc = ray.origin - position;

        float a = glm::dot(ray.dir, ray.dir);
        float b = 2*glm::dot(vc, ray.dir);
        float c = glm::dot(vc, vc) - radius * radius;
        if(abs(c) < FLOAT_EPS) c = 0;

        float delta = b*b-4*a*c;
        if(delta < FLOAT_EPS) return tmin;
        delta = sqrt(delta);
        float t1 = (-b+delta)/2/a;
        float t2 = (-b-delta)/2/a;
        float t;
        if(t1 < FLOAT_EPS && t2 < FLOAT_EPS) return tmin;
        if(t2 > FLOAT_EPS) t = t2;
        else t = t1;

        if(t >= tmin) return tmin;
        fragPos = ray.origin+t*ray.dir;
        norm = glm::normalize(fragPos-position);
        outter = c > FLOAT_EPS;
        return t;
    }
    void calcAABB() {
        min = position-glm::vec3(radius);
        max = position+glm::vec3(radius);

        min -= FLOAT_EPS_VEC3;
        max += FLOAT_EPS_VEC3;
    }
};
#endif