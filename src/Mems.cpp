#include "Mems.hpp"



//KONSTRUTOREN----------------------------------------------------------------

  //Default
Mems::Mems():
          m_orig{10,700,0},
          m_orient{1,0,0},
          m_dimensions{30, 15, 0},
          m_amm_mirr{5, 3}{std::cout << "Mems is being created" << std::endl;}

Mems::Mems(vec3 const &orig, vec3 const &orient):
          m_orig(orig),
          m_orient(orient),
          m_dimensions{30, 15, 0},
          m_amm_mirr{500, 300}{}


Mems::Mems(vec3 const &orig, vec3 const &orient, vec3 const &dimensions, vec2 const &amm_mirr):
          m_orig(orig),
          m_orient(orient),
          m_dimensions(dimensions),
          m_amm_mirr(amm_mirr){}


Mems::~Mems(){
    std::cout << "Mems is being deleted" << std::endl;
}


void Mems::update(){

  float x_ax = m_dimensions.x / m_amm_mirr.x;
  float y_ax = m_dimensions.y / m_amm_mirr.y;

  std::cout << "Mems::update() :  " << std::endl;
  std::cout << "x_ax = " << y_ax << std::endl;
  std::cout << "y_ax = " << y_ax << std::endl;

  for( int yi=0; yi< m_amm_mirr.y; yi++){
    std::cout<< "yi = " << yi<< std::endl;
    for(int xi=0; xi< m_amm_mirr.x; xi++){
      std::cout<<"xi = " <<xi <<std::endl;
      vec3 pos = vec3{0, yi*y_ax+m_orig.y, xi*x_ax+m_orig.x};
      std::cout<< "pos = "<< pos << std::endl;
      Ray new_ray{pos, vec3{0,0,1}};
      m_mems_rays.push_back(new_ray);
    }
  }



}
