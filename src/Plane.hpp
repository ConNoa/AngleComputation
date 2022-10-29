#pragma once

#include "hit.hpp"
#include "shape.hpp"

using namespace glm;

class Plane : public Shape {

public:
  //KONSTRUTOREN----------------------------------------------------------------
  Plane();
  Plane(int mat_id);
  Plane(std::string const& name, int mat_id);
  Plane(vec3 const& orig, vec3 const& direction);
  Plane(vec3 const& orig, vec3 const& direction, int mat_id);
  ~Plane();

  //FUNKTIONEN------------------------------------------------------------------
  std::ostream& print(std::ostream& os) const;
  Ray   intersect(Ray &ray_in) const;
  Hit depthtest(Ray const &ray_in) const;
  // virtual Hit   intersect(Ray &ray_in, int count_hits) const = 0;
  void  draw() const ;
  void  update();
  void  update_path();


  void scale(float faktor)                  ;
  void translate(vec3 const& vec)           ;
  void rotate(float angle,vec3 const& vec)  ;
//
  //----------------------------------------------------------------------------
  //MEMEBER-VARIABLEN-----------------------------------------------------------
  //----------------------------------------------------------------------------
  vec3  m_orig;           //Origin -  Mittelpunkt
  vec3 m_direction;
  bool m_draw_rays;

private:


};
