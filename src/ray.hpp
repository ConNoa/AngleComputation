#pragma once

#include <glm/glm.hpp>

class Ray
{

public:

		Ray();
		Ray(glm::vec3 const& orig, glm::vec3 const& dir);

		void transform(glm::mat4 const &t_mat);

		Ray transformRay(glm::mat4 const& mat, Ray &ray);

		glm::vec3 m_orig;
		glm::vec3 m_direction;
		glm::vec3 m_inv_direction;

};
