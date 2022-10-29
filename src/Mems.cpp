#include "Mems.hpp"



//KONSTRUTOREN----------------------------------------------------------------

  //Default
Mems::Mems():
          m_orig{20,700,0},
          m_orient{1,0,0},
          m_dimensions{0, 30, 15},
          m_amm_mirr{20, 30}{std::cout << "Mems is being created" << std::endl;}

Mems::Mems(vec3 const &orig, vec3 const &orient):
          m_orig(orig),
          m_orient(orient),
          m_dimensions{30, 15, 0},
          m_amm_mirr{50, 30}{}


Mems::Mems(vec3 const &orig, vec3 const &orient, vec3 const &dimensions, vec2 const &amm_mirr):
          m_orig(orig),
          m_orient(orient),
          m_dimensions(dimensions),
          m_amm_mirr(amm_mirr){}


Mems::~Mems(){
    std::cout << "Mems is being deleted" << std::endl;
}


void Mems::setup(){

  float x_ax = m_dimensions.x / m_amm_mirr.x;
  float y_ax = m_dimensions.y / m_amm_mirr.y;

// Mems update wurde für dynamic_cast test auskommentiert

  std::cout << "Mems::update() :  " << std::endl;
  // std::cout << "x_ax = " << y_ax << std::endl;
  // std::cout << "y_ax = " << y_ax << std::endl;
  std::cout<< "---->all Mirror Positions"<<std::endl;

  // std::cout << "[ " ;

  for( int yi=0; yi<= m_amm_mirr.y; yi++){
     //std::cout<< "yi = " << yi<< " ";
    for(int xi=0; xi< m_amm_mirr.x; xi++){
      // std::cout<<"xi = " <<xi <<std::endl;
      vec3 pos = vec3{m_orig.x, yi*y_ax+m_orig.y-m_dimensions.y/2, xi*x_ax-m_dimensions.x/2};
      int i = m_mems_rays.size();
      // std::cout<< "[pos"<< i<<" = "<< pos<< "] ";
      // std::cout<< "m_orient = " << m_orient<< std::endl;
      Ray new_ray{pos, m_orient};
      m_mems_rays.push_back(new_ray);
    }
  }
  std::cout<< " "<<std::endl;
  addRay({20, 700, 0}, 0.5f);
  addRay({20, 700, 0}, -0.5f);
  addRay({20, 700, 0}, 2.0f);
  addRay({20, 700, 0}, -2.0f);

  return;
}

void Mems::addRay(vec3 const& origin, float angle){
  vec3 direct = vec3{1,0,0};
  // float angle_ursp = 0.5/(180.0/3.141592653589793238463);
  float angle_ursp = angle/(180.0/3.141592653589793238463);
  //angle_ursp = 0.0f;
  fmat4 rot_mat_t = glm::rotate(angle_ursp, fvec3{0.0f, 0.0f, 1.0f});
  //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;

  fmat3 rot_mat_t_shrnkd = fmat3(rot_mat_t);

  vec3 direct_new = (rot_mat_t_shrnkd*direct);

  std::cout<< "direction new of ray: "<< direct_new<< std::endl;
  // Ray redray{{20, 750, 0}, direct_new, {255, 0, 0}};
  Ray redray{origin, direct_new, {255, 0, 0}};
  m_mems_rays.push_back(redray);


  return;

}



void Mems::update(){


  return;
}


void Mems::draw(){


}
