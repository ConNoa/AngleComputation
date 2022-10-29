#pragma once

#include <glm/glm.hpp>

#include "ofMain.h"
// #include "ofApp.h"

class Ray
{

public:

		Ray();
		Ray(glm::vec3 const& orig, glm::vec3 const& dir);
		Ray(glm::vec3 const& orig, glm::vec3 const& dir, ofColor const & col);

		void draw();

		void transform(glm::mat4 const &t_mat);

		void print() const;


		Ray transformRay(glm::mat4 const& mat, Ray &ray);

		glm::vec3 m_orig;
		glm::vec3 m_direction;
		glm::vec3 m_inv_direction;
		float m_distance_hit;
		ofColor m_color;
		// glm::vec3 m_hitpoint;

};
