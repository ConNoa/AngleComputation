#pragma once

#include "shape.hpp"
#include <memory>
#include <cmath> // INFINITY


class Shape;

struct Hit
{
	//KONSTRUTOREN----------------------------------------------------------------
		Hit();
		Hit(bool hit, double distance, glm::vec3 const& intersection,
	        glm::vec3 const& normal, Shape* const shape);
	  Hit(Hit const& tmp_hit);


	//FUNKTIONEN------------------------------------------------------------------
		Hit& operator=(Hit const& tmp_hit);

	//VARIABLEN-------------------------------------------------------------------
    bool m_hit;
    double m_distance;
    glm::vec3 m_point;
    glm::vec3 m_normal;
    Shape* m_shape; //Soll RAW-Pointer sein, damit this funktioniert und und... vlt noch const setzen?
};
