#pragma once

#include <iostream>
#include "shape.hpp"
#include <memory>
#include <cmath> // INFINITY

using namespace glm;

class Shape;

struct Hit
{
	//KONSTRUTOREN----------------------------------------------------------------
		Hit();
		Hit(bool hit, double distance, vec3 const& intersection,
	        vec3 const& normal, Shape* const shape);
	  Hit(Hit const& tmp_hit);


	//FUNKTIONEN------------------------------------------------------------------

		void draw(vec3 const& direction_from) const;

		void print() const;

		Hit& operator=(Hit const& tmp_hit);

	//VARIABLEN-------------------------------------------------------------------
    bool m_hit;
    double m_distance;
    vec3 m_point;
    vec3 m_normal;
    const Shape* m_shape; //Soll RAW-Pointer sein, damit this funktioniert und und... vlt noch const setzen?

};
