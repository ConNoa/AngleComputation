#pragma once

#include "ofMain.h"

#include <iostream>
#include <memory>
#include <cmath> // INFINITY
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"
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

		void draw_normals() const;

		void draw(vec3 const& direction_from) const;

		void print() const;

		void Hit_print(int hitnmbr) const;

		Hit& operator=(Hit const& tmp_hit);

	//VARIABLEN-------------------------------------------------------------------
    bool m_hit;
    vec3 m_point;
    vec3 m_normal;

		double m_distance;

		Ray	m_ray;

    const Shape* m_shape; //Soll RAW-Pointer sein, damit this funktioniert und und... vlt noch const setzen?

};
