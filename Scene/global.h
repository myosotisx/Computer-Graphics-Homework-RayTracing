#ifndef GLOBAL_H
#define GLOBAL_H

const static float FLOAT_EPS = 1e-5;
const static float FLOAT_INF = 100000000.0f;

const static glm::vec3 FLOAT_EPS_VEC3 = glm::vec3(FLOAT_EPS, FLOAT_EPS, FLOAT_EPS);
const static glm::vec3 FLOAT_INF_VEC3 = glm::vec3(FLOAT_INF, FLOAT_INF, FLOAT_INF);

void printVec3(const glm::vec3 v) {
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

#endif
