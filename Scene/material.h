#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <functional>


class Material {
    static Material *blackMat, *goldMat, *silverMat, *byzantiumMat, *bronzeMat, *ceruleanMat, *glassMat, *mirrorMat, *planeGridMaterial;
public:
    std::function<glm::vec3(const glm::vec3& pos)> ambient;
    std::function<glm::vec3(const glm::vec3& pos)> diffuse;
    std::function<glm::vec3(const glm::vec3& pos)> specular;
    std::function<float(const glm::vec3& pos)> shininess;
    float kShade;
    float kReflect;
    float kRefract;
    float refractIndex;
    static Material* getBlackMaterial() {
        if(!blackMat) {
            blackMat = new Material();
            blackMat->kShade = 1.0f;
            blackMat->kReflect = 0.0f;
            blackMat->kRefract = 0.0f;
            blackMat->refractIndex = 1.0f;
            blackMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {0.0f, 0.0f, 0.0f};
            };
            blackMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {0.0f, 0.0f, 0.0f};
            };
            blackMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {0.0f, 0.0f, 0.0f};
            };
            blackMat->shininess = [](const glm::vec3& pos)->float {
                return 0.0f;
            };
        }
        return blackMat;
    }
    static Material* getGoldMaterial() {
        if(!goldMat) {
            goldMat = new Material();
            goldMat->kShade = 0.95f;
            goldMat->kReflect = 0.05f;
            goldMat->kRefract = 0.0f;
            goldMat->refractIndex = 1.0f;
            goldMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 0.843f, 0.0f};
            };
            goldMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {0.5f, 0.422f, 0.0f};
            };
            goldMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {0.6f, 0.6f, 0.6f};
            };
            goldMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return goldMat;
    }
    static Material* getSilverMaterial() {
        if(!silverMat) {
            silverMat = new Material();
            silverMat->kShade = 0.95f;
            silverMat->kReflect = 0.05f;
            silverMat->kRefract = 0.0f;
            silverMat->refractIndex = 1.0f;
            silverMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return { 0.753f, 0.753f, 0.753f };
            };
            silverMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return { 0.376f, 0.376f, 0.376f };
            };
            silverMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return { 0.6f, 0.6f, 0.6f };
            };
            silverMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return silverMat;
    }
    static Material* getByzantiumMaterial() {
        if(!byzantiumMat) {
            byzantiumMat = new Material();
            byzantiumMat->kShade = 0.95f;
            byzantiumMat->kReflect = 0.05f;
            byzantiumMat->kRefract = 0.0f;
            byzantiumMat->refractIndex = 1.0f;
            byzantiumMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {0.439f, 0.080f, 0.388f};
            };
            byzantiumMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {0.219f, 0.040f, 0.194f};
            };
            byzantiumMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 1.0f, 1.0f};
            };
            byzantiumMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return byzantiumMat;
    }
    static Material* getBronzeMaterial() {
        if(!bronzeMat) {
            bronzeMat = new Material();
            bronzeMat->kShade = 0.95f;
            bronzeMat->kReflect = 0.05f;
            bronzeMat->kRefract = 0.0f;
            bronzeMat->refractIndex = 1.0f;
            bronzeMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {0.796f, 0.427f, 0.404f};
            };
            bronzeMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {0.398f, 0.214f, 0.202f};
            };
            bronzeMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 1.0f, 1.0f};
            };
            bronzeMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return bronzeMat;
    }
    static Material* getCeruleanMaterial() {
        if(!ceruleanMat) {
            ceruleanMat = new Material();
            ceruleanMat->kShade = 0.95f;
            ceruleanMat->kReflect = 0.05f;
            ceruleanMat->kRefract = 0.0f;
            ceruleanMat->refractIndex = 1.0f;
            ceruleanMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {0.0f, 0.482f, 0.654f};
            };
            ceruleanMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {0.0f, 0.241f, 0.327f};
            };
            ceruleanMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 1.0f, 1.0f};
            };
            ceruleanMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return ceruleanMat;
    }
    static Material* getGlassMaterial() {
        if(!glassMat) {
            glassMat = new Material();
            glassMat->kShade = 0.01f;
            glassMat->kReflect = 0.0f;
            glassMat->kRefract = 0.99f;
            glassMat->refractIndex = 1.52f;
            glassMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 1.0f, 1.0f};
            };
            glassMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 1.0f, 1.0f};
            };
            glassMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {0.8f, 0.8f, 0.8f};
            };
            glassMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return glassMat;
    }
    static Material* getMirrorMaterial() {
        if(!mirrorMat) {
            mirrorMat = new Material();
            mirrorMat->kShade = 0.01f;
            mirrorMat->kReflect = 0.99f;
            mirrorMat->kRefract = 0.0f;
            mirrorMat->refractIndex = 1.52f;
            mirrorMat->ambient = [](const glm::vec3& pos)->glm::vec3 {
                return {0.898f, 0.894f, 0.886f};
            };
            mirrorMat->diffuse = [](const glm::vec3& pos)->glm::vec3 {
                return {0.449f, 0.447f, 0.443f};
            };
            mirrorMat->specular = [](const glm::vec3& pos)->glm::vec3 {
                return {1.0f, 1.0f, 1.0f};
            };
            mirrorMat->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return mirrorMat;
    }
    static Material* getPlaneGridMaterial(float ratio=1.0f) {
        if(!planeGridMaterial) {
            auto isBlack = [=](const glm::vec3& pos) {
                return fmod(floor(pos.x/ratio) + floor(pos.z/ratio), 2) == 0;
            };
            planeGridMaterial = new Material();
            planeGridMaterial->kShade = 0.8f;
            planeGridMaterial->kReflect = 0.2f;
            planeGridMaterial->kRefract = 0.0f;
            planeGridMaterial->refractIndex = 1.0f;
            planeGridMaterial->ambient = [=](const glm::vec3& pos)->glm::vec3 {
                glm::vec3 color(0.0f, 0.0f, 0.0f);
                if(isBlack(pos)) {
                    return color;
                }
                else {
                    return glm::vec3(1.0f, 1.0f, 1.0f)-color;
                }
            };
            planeGridMaterial->diffuse = [=](const glm::vec3& pos)->glm::vec3 {
                glm::vec3 color(0.0f, 0.0f, 0.0f);
                if(isBlack(pos)) {
                    return color;
                }
                else {
                    return glm::vec3(1.0f, 1.0f, 1.0f)-color;
                }
            };
            planeGridMaterial->specular = [=](const glm::vec3& pos)->glm::vec3 {
                glm::vec3 color(0.0f, 0.0f, 0.0f);
                if(isBlack(pos)) {
                    return color;
                }
                else {
                    return glm::vec3(1.0f, 1.0f, 1.0f) - color;
                }
            };
            planeGridMaterial->shininess = [](const glm::vec3& pos)->float {
                return 32.0f;
            };
        }
        return planeGridMaterial;
    }
};
Material* Material::blackMat = nullptr;
Material* Material::goldMat = nullptr;
Material* Material::silverMat = nullptr;
Material* Material::byzantiumMat = nullptr;
Material* Material::bronzeMat = nullptr;
Material* Material::ceruleanMat = nullptr;
Material* Material::glassMat = nullptr;
Material* Material::mirrorMat = nullptr;
Material* Material::planeGridMaterial = nullptr;
#endif
