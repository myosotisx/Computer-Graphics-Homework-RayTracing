#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.h"
#include "model.h"
#include "material.h"


class ModelObject: Object {
private:
	Model *model;
	Material *mat;
	ModelObject(glm::vec3 position=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 offset=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale=glm::vec3(1.0f, 1.0f, 1.0f))
		: Object(position, offset, scale) {}
};

#endif