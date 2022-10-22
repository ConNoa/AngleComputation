#include "hit.hpp"

//KONSTRUTOREN----------------------------------------------------------------

	//Default (Kein Hit!)
		Hit::Hit():
			m_hit{ false },
			m_distance{ INFINITY },
			m_point{ vec3{ INFINITY, INFINITY, INFINITY } },
			m_normal{ vec3{ INFINITY, INFINITY, INFINITY } },
			m_shape{ nullptr } {}


	//Custom 1
		Hit::Hit(bool hit, double distance, vec3 const& intersection,
		    vec3 const& normal, Shape* const shape):
			m_hit{hit},
			m_distance{distance},
			m_point{intersection},
			m_normal{normal},
			m_shape{shape} {}

	//Custom 2
		Hit::Hit(Hit const& tmp_hit) :
			m_hit{ tmp_hit.m_hit },
			m_distance{ tmp_hit.m_distance },
			m_point{ tmp_hit.m_point },
			m_normal{ tmp_hit.m_normal },
			m_shape{ tmp_hit.m_shape } {std::cout<<"Custom 2 Hit constructed\n";}

//FUNKTIOENNE----------------------------------------------------------------
		void Hit::draw() const{

			ofBeginShape();
			ofSetColor(ofColor::black);
			ofDrawLine(m_point-vec3{50, 0, 0}, m_point+vec3{50, 0, 0});
			ofSetColor(75, 196, 213);
			ofDrawArrow(m_point, m_point+m_normal*300, 3);
			ofEndShape();


		}


		Hit& Hit::operator=(Hit const& tmp_hit)
		{
		    if (this == &tmp_hit) {
		        return *this;
		    }

		    m_hit = tmp_hit.m_hit;
		    m_distance = tmp_hit.m_distance;
		    m_point = tmp_hit.m_point;
		    m_normal = tmp_hit.m_normal;
		    m_shape = tmp_hit.m_shape;

		    return *this;
		}
