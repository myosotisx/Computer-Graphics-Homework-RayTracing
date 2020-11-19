#ifndef COMPLEX_OBJECT_H
#define COMPLEX_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.h"


class Bunny: public ModelObject {
private:
    static Model *bunnyMod;
public:
    Bunny(const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f, 0.0f))
        : ModelObject(getBunnyModel(), _position, _offset, _scale, _rotate) {}
    static Model* getBunnyModel() {
        if(!bunnyMod) {
            bunnyMod = new Model("resources/objects/bun_zipper_res2.ply");
        }
        return bunnyMod;
    }
};


class Dragon: public ModelObject {
private:
    static Model *dragonMod;
public:
    Dragon(const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f, 0.0f))
        : ModelObject(getBunnyModel(), _position, _offset, _scale, _rotate) {}
    static Model* getBunnyModel() {
        if(!dragonMod) {
            dragonMod = new Model("resources/objects/dragon_vrip_res3.ply");
        }
        return dragonMod;
    }
};


class Happy: public ModelObject {
private:
    static Model *happyMod;
public:
    Happy(const glm::vec3& _position=glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& _offset=glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& _scale=glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& _rotate=glm::vec3(0.0f, 0.0f, 0.0f))
        : ModelObject(getBunnyModel(), _position, _offset, _scale, _rotate) {}
    static Model* getBunnyModel() {
        if(!happyMod) {
            happyMod = new Model("resources/objects/happy_vrip_res3.ply");
        }
        return happyMod;
    }
};
Model* Bunny::bunnyMod = nullptr;
Model* Dragon::dragonMod = nullptr;
Model* Happy::happyMod = nullptr;
#endif