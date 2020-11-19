#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>

#include "object.h"
#include "light.h"
#include "ray.h"


class Scene {
private:
	int maxRTDepth;
	bool RTAccelerate;
	std::map<VerticesContainer*, int> containers;
public:
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Scene(int _maxRTDepth=5, bool RTAccelerate=true): maxRTDepth(_maxRTDepth), RTAccelerate(RTAccelerate) {}
	void addObject(Object *object) {
		objects.push_back(object);
		VerticesContainer *container = object->container;
		if(containers.find(container) == containers.end()) {
			containers[container] = 0;
		}
		containers[container] += 1;
		
	}
	void addLight(Light *light) {
		lights.push_back(light);
	}
	bool deleteObject(Object *object, bool deleteMem=true) {
		if(!object) return false;
		std::vector<Object*>::iterator iter = std::find(objects.begin(), objects.end(), object);
		if(iter != objects.end()) {
			objects.erase(iter);
		}
		else {
			return false;
		}
		if(deleteMem) {
			VerticesContainer *container = object->container;
			std::map<VerticesContainer*, int>::iterator iter = containers.find(container);
			if(iter != containers.end()) {
				if(containers[container] <= 1) {
					containers.erase(iter);
				}
				else {
					containers[container] -= 1;
				}
			}
			delete object;
		}
		return true;
	}
	void destroyScene() {
		for(Light *light: lights) {
			delete light;
		}
		for(Object *object: objects) {
			delete object;
		}
	}
	void loadVertices() {
		for(auto containerPair: containers) {
			containerPair.first->loadVertices();
		}
	}
	void setMaxRTDepth(int depth) {
		maxRTDepth = depth;
	}
	void setRTAccelerate(bool accelerate) {
		RTAccelerate = accelerate;
	}
	void printVerticesInfo() {
		for(auto containerPair: containers) {
			printf("Address: %p Num of references: %d\n", containerPair.first, containerPair.second);
		}
	}
	glm::vec3 rayTrace(const Ray& ray, int curDepth=0) {
		glm::vec3 color(0.0f, 0.0f, 0.0f);
		if(curDepth >= maxRTDepth) {
			return color;
		}

		Object *object = nullptr;
		glm::vec3 fragPos;
		glm::vec3 norm;
		bool outter;
		calcIntersect(ray, object, fragPos, norm, outter);

		if(!object) {
			return color;
		}
		if(!outter) {
			norm = -norm;
		}

		const Material *mat = object->getMaterial();
		// ambient
		if(outter && mat->kShade > FLOAT_EPS) {
			color += mat->kShade * shade(mat, fragPos, norm, ray);
		}

		// reflect
		if(mat->kReflect > FLOAT_EPS) {
			glm::vec3 reflectDir = glm::reflect(ray.dir, norm);
			color += mat->kReflect * rayTrace(Ray(fragPos, reflectDir), curDepth+1);
		}

		// refract
		if(mat->kRefract > FLOAT_EPS) {
			float curRefractIndex = 1.0f;
			float nextRefractIndex = mat->refractIndex;
			if(!outter) {
				std::swap(curRefractIndex, nextRefractIndex);
			}
			glm::vec3 refractDir = glm::refract(ray.dir, norm, curRefractIndex/nextRefractIndex);
			color += mat->kRefract * rayTrace(Ray(fragPos, refractDir), curDepth+1);
		}
		
		return color;
	}
private:
	glm::vec3 shade(const Material *material, const glm::vec3& fragPos, const glm::vec3& norm, const Ray& ray) {
		glm::vec3 color(0.0f, 0.0f, 0.0f);
		for(Light *light: lights) {
			Object *object = nullptr;
			glm::vec3 _fragPos(0.0f); // dummy
			glm::vec3 _norm(0.0f);    // dummy
			bool _outter;             // dummy
			float tmin = FLOAT_INF;

			PointLight *pointLight = dynamic_cast<PointLight*>(light);
			if(pointLight) {
				tmin = glm::length(pointLight->position-fragPos);
			}

			calcIntersect(Ray(fragPos, light->calcLightDir(fragPos)), object, _fragPos, _norm, _outter, tmin);
			bool inShadow = object != nullptr;
			color += light->calcLight(material, fragPos, norm, -ray.dir, inShadow);
		}
		return color;
	}
	void calcIntersect(const Ray& ray, Object*& object, glm::vec3& fragPos, glm::vec3& norm, bool& outter, float tmin=FLOAT_INF) {
		object = nullptr;
		glm::vec3 _norm;
		glm::vec3 _fragPos;
		bool _outter;
		for(Object *_object: objects) {
			AABB *AABBObject = dynamic_cast<AABB*>(_object);
			// Intersect with AABB first
			if(RTAccelerate && AABBObject && !AABBObject->rayIntersectAABB(ray)) {
				continue;
			}
			float t = _object->rayIntersect(ray, _fragPos, _norm, _outter, tmin);
			if(t >= tmin) continue;
			tmin = t;
			norm = _norm;
			fragPos = _fragPos;
			outter = _outter;
			object = _object;
		}
	}
};
#endif
