#pragma once

#include <glm/glm.hpp>

#include "ofMain.h"
// #include "ofApp.h"

class Ray
{

public:

		Ray();
		Ray(glm::vec3 const& orig, glm::vec3 const& dir);

		void draw();

		void transform(glm::mat4 const &t_mat);


		Ray transformRay(glm::mat4 const& mat, Ray &ray);

		glm::vec3 m_orig;
		glm::vec3 m_direction;
		glm::vec3 m_inv_direction;
		float m_distance_hit;
		glm::vec3 m_hitpoint;

};
