#include "ray.hpp"



	 //KONSTRUTOREN----------------------------------------------------------------
	Ray::Ray():
		m_orig{0.0f},
		m_direction{0.0f},
		m_inv_direction{0.0f},
		m_distance_hit{0.0f},
		m_color{255, 255, 0}{}

	Ray::Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		m_orig{orig},
		m_direction{dir},
		m_inv_direction{glm::vec3{-1.0*dir.x, -1.0*dir.y, -1.0*dir.z}},
		m_distance_hit{100.0f},
		m_color{255, 255, 0}{}



	Ray::Ray(glm::vec3 const& orig, glm::vec3 const& dir, ofColor const& col):
		m_orig{orig},
		m_direction{dir},
		m_inv_direction{glm::vec3{-1.0*dir.x, -1.0*dir.y, -1.0*dir.z}},
		m_distance_hit{100.0f},
		m_color{col}{}


	Ray::Ray(Ray const& tmp_ray):
		m_orig{tmp_ray.m_orig},
		m_direction{tmp_ray.m_direction},
		m_inv_direction{tmp_ray.m_inv_direction},
		m_distance_hit{tmp_ray.m_distance_hit},
		m_color{tmp_ray.m_color}{}



	void Ray::draw(){
			// ofBeginShape();
			// 	ofSetColor(ofColor::yellow);
			// 	m_direction = normalize(m_direction)*1000;
			// 	// std::cout<< "Ray draw ()  - " <<std::endl;
			// 	// std::cout<< "m_orig of Ray = "<< m_orig << std::endl;
	    //   // std::cout<< "direction of Ray = " << m_direction<< std::endl;
			// 	ofDrawLine(glm::vec2(m_orig), glm::vec2(m_orig+m_direction));
			// 	// std::cout<< "after Ray draw ()  - " <<std::endl;
			// 	// std::cout<< "m_orig of Ray = "<< m_orig << std::endl;
			// 	// std::cout<< "direction of Ray = " << m_direction<< std::endl;
			//
			//
			// ofEndShape();

	}

	void Ray::transform(glm::mat4 const &t_mat){
		glm::vec4 a{m_orig,1.0f};
		glm::vec4 b{m_direction,0.0f};

		m_orig = glm::vec3(t_mat*a);
		m_direction = glm::vec3(t_mat*b);
		m_inv_direction = glm::vec3{-1.0*m_direction.x, -1.0*m_direction.y, -1.0*m_direction.z};

		return;
	}


	void Ray::print() const
	{
		std::cout << "Ray Informations: [\n"
		<< "m_orig: [" << m_orig << "]\n"
		<< "m_direction: [" << m_direction << "]\n"
		<< "m_inv_direction: [" << m_inv_direction << "]\n"
		<< "m_distance_hit: [" << m_distance_hit << "]\n"
	  << "Color: [" << m_color.r<<", "<<m_color.g<<", "<<m_color.b<< "] ]" <<std::endl;

	}

	Ray transformRay(glm::mat4 const& t_mat, Ray &ray){
		glm::vec4 a{ray.m_orig,1.0f};
		glm::vec4 b{ray.m_direction,0.0f};

		return {glm::vec3(t_mat*a),glm::vec3(t_mat*b)};
	}
