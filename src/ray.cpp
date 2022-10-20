#include "ray.hpp"

Ray transformRay(glm::mat4 const& mat, Ray const& ray)
{
	glm::vec4 a{ray.m_origin,1.0f};
	glm::vec4 b{ray.m_direction,0.0f};

	return {glm::vec3(mat*a),glm::vec3(mat*b)};
}