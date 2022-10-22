#include "ray.hpp"



	 //KONSTRUTOREN----------------------------------------------------------------
	Ray::Ray():
		m_orig{0.0f},
		m_direction{0.0},
		m_inv_direction{0.0}{}

	Ray::Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		m_orig{orig},
		m_direction{dir},
		m_inv_direction{glm::vec3{-1.0*dir.x, -1.0*dir.y, -1.0*dir.z}}{}


	void Ray::draw(){
			ofBeginShape();
				ofSetColor(ofColor::yellow);
				m_direction = normalize(m_direction)*1000;
				// std::cout<< "Ray draw ()  - " <<std::endl;
				// std::cout<< "m_orig of Ray = "<< m_orig << std::endl;
	      // std::cout<< "direction of Ray = " << m_direction<< std::endl;
				ofDrawLine(glm::vec2(m_orig), glm::vec2(m_orig+m_direction));
				// std::cout<< "after Ray draw ()  - " <<std::endl;
				// std::cout<< "m_orig of Ray = "<< m_orig << std::endl;
				// std::cout<< "direction of Ray = " << m_direction<< std::endl;


			ofEndShape();

	}


	void Ray::transform(glm::mat4 const &t_mat){
		glm::vec4 a{m_orig,1.0f};
		glm::vec4 b{m_direction,0.0f};

		m_orig = glm::vec3(t_mat*a);
		m_direction = glm::vec3(t_mat*b);
		m_inv_direction = glm::vec3{-1.0*m_direction.x, -1.0*m_direction.y, -1.0*m_direction.z};

		return;
	}


	Ray transformRay(glm::mat4 const& t_mat, Ray &ray){
		glm::vec4 a{ray.m_orig,1.0f};
		glm::vec4 b{ray.m_direction,0.0f};

		return {glm::vec3(t_mat*a),glm::vec3(t_mat*b)};
	}
