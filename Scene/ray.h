#ifndef RAY_H
#define RAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"


class Ray {
public:
	glm::vec3 origin, dir;
	Ray(const glm::vec3& _origin, const glm::vec3& _dir): origin(_origin), dir(glm::normalize(_dir)) {}
	float triangleIntersect(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, glm::vec3& p, glm::vec3& n, bool& outter, float &t1, float &t2, float tmin=FLOAT_INF) const {
		glm::vec3 u = v1-v0, v = v2-v0;
		n = glm::normalize(glm::cross(u, v));

		float b = glm::dot(n, dir);
		if(abs(b) < FLOAT_EPS) return -1.0f;

		float a = -glm::dot(n, origin-v0);

		float t = a/b;
		if(t < FLOAT_EPS) return -1.0f;

		if(t >= tmin) return -2.0f;

		p = origin+t*dir;
		glm::vec3 w = p-v0;

		float uu = glm::dot(u, u);
		float uv = glm::dot(u, v);
		float vv = glm::dot(v, v);
		float wu = glm::dot(w, u);
		float wv = glm::dot(w, v);

		float deno = 1/(uv*uv-uu*vv);

		float _t1 = (uv*wv-vv*wu)*deno;
		if(_t1 < -FLOAT_EPS || _t1 > 1.0f+FLOAT_EPS) return -1.0f;

		float _t2 = (uv*wu-uu*wv)*deno;
		if(_t2 < -FLOAT_EPS || (_t1+_t2) > 1.0f+FLOAT_EPS) return -1.0f;
		
		outter = b < 0;
		t1 = _t1;
		t2 = _t2;
		return t;
	}
};
#endif
