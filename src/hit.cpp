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
			m_shape{ tmp_hit.m_shape } {
				// std::cout<<"Custom 2 Hit constructed\n";
			}

//FUNKTIOENNE----------------------------------------------------------------
void Hit::draw_normals() const{

	ofBeginShape();
		//Drawing Normals
		ofSetColor(75, 196, 213);
		ofDrawArrow(m_point, m_point+m_normal*50, 3);
		// ofSetColor(146, 21, 37);
		ofDrawArrow(m_point, m_point-m_normal*50, 3);
	ofEndShape();

	return;
}

void Hit::draw(vec3 const& direction_from) const{

	vec3 direction_to = normalize(direction_from);
	ofBeginShape();

	//Drawing horizontal Black Lines
	ofSetColor(ofColor::orange);
		ofSetLineWidth(1);
		ofDrawLine(m_point, m_point+ direction_to* m_distance);
	ofEndShape();


}

void Hit::print() const {
			std::cout<< ":-------------------------------------------------------------: "  <<std::endl;
			std::cout << "Hit: ["<<std::endl;
			std::cout<< "m_hit   : [ " << m_hit << " ]" <<std::endl;
			std::cout<< "m_distance   : [ " <<m_distance  << " ]" <<std::endl;
			std::cout<< " m_point  : [ " << m_point.x << "  y und z fehlen noch-... ]"<<std::endl;
			std::cout<< " m_normal  : [ " <<  m_normal.x << "  y und z fehlen noch-... ]" <<std::endl;
			// std::cout<< " m_shape  : [ " << m_shape << " ]    ]   -------------------------- \n \n" <<std::endl;
			std::cout<< ":-------------------------------------------------------------: "  <<std::endl;

}

void Hit::Hit_print(int hitnmbr) const{

		std::cout<<"\n"<< hitnmbr<< "----------- Hit!  ----------------------------------"<<std::endl;
		std::cout<<"      with ray from : ["<< m_ray.m_orig << "]"<<std::endl;
		std::cout<<"  m_ray.m_direction : [" << m_ray.m_direction << "]"<<std::endl;
		std::cout<<" At             Pos : ["<< m_point<<"]" << std::endl;
		std::cout<<"Intersection-normal : ["<< m_normal<<"]" <<std::endl;
		std::cout<<"           Distance :"<< m_distance << std::endl;



}


		Hit& Hit::operator=(Hit const& tmp_hit){
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
