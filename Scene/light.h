#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "material.h"


class Light {
public:
	virtual glm::vec3 calcLight(const Material* mat, const glm::vec3& fragPos, const glm::vec3& norm, const glm::vec3& viewDir, bool inShadow) const = 0;
	virtual glm::vec3 calcLightDir(const glm::vec3& fragPos) = 0;
};


class DirectLight: public Light {
public:
	glm::vec3 ambient, diffuse, specular, dir;
	DirectLight(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular, const glm::vec3& _dir)
		: ambient(_ambient),
		  diffuse(_diffuse),
		  specular(_specular),
		  dir(glm::normalize(_dir)) {}

	glm::vec3 calcLight(const Material* mat, const glm::vec3& fragPos, const glm::vec3& norm, const glm::vec3& viewDir, bool inShadow) const {
		glm::vec3 color(0.0f);
		// calc ambient
		color += this->ambient * mat->ambient(fragPos);

		// calc diffuse
		if(!inShadow) {
			color += std::max(glm::dot(norm, -this->dir), 0.0f) * this->diffuse * mat->diffuse(fragPos);

			// calc specular
			glm::vec3 reflectDir = glm::reflect(dir, norm);
			float spec = glm::pow(std::max(glm::dot(viewDir, reflectDir), 0.0f), mat->shininess(fragPos));
			color += spec * this->specular * mat->specular(fragPos);
		}
		return color;
	}
	glm::vec3 calcLightDir(const glm::vec3& fragPos) {
		return -dir;
	}
};

class PointLight: public Light {
public:
	glm::vec3 ambient, diffuse, specular, position;
	float constant, linear, quadratic;
	PointLight(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular, const glm::vec3& _position, float _constant, float _linear, float _quadratic)
		: ambient(_ambient),
		  diffuse(_diffuse),
		  specular(_specular),
		  position(_position),
		  constant(_constant), 
		  linear(_linear),
		  quadratic(_quadratic) {}

	glm::vec3 calcLight(const Material* mat, const glm::vec3& fragPos, const glm::vec3& norm, const glm::vec3& viewDir, bool inShadow) const {
		glm::vec3 lightDir = glm::normalize(position-fragPos);
		glm::vec3 color(0.0f);
		// calc ambient
		color += this->ambient * mat->ambient(fragPos);

		if(!inShadow) {
			// calc diffuse
			color += std::max(glm::dot(norm, lightDir), 0.0f) * this->diffuse * mat->diffuse(fragPos);

			// calc specular
			glm::vec3 reflectDir = glm::reflect(-lightDir, norm);
			float spec = glm::pow(std::max(glm::dot(viewDir, reflectDir), 0.0f), mat->shininess(fragPos));
			color += spec * this->specular * mat->specular(fragPos);
		}
		
		// calc attenuation
		float distance = glm::length(position-fragPos);
		float attenuation = 1.0f/(constant+linear*distance+quadratic*(distance*distance));

		return color*attenuation;
	}
	glm::vec3 calcLightDir(const glm::vec3& fragPos) {
		return glm::normalize(position-fragPos);
	}
};
#endif
