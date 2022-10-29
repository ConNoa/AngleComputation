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
  ~Plane();

  //FUNKTIONEN------------------------------------------------------------------
  virtual std::ostream& print(std::ostream& os) const;
  virtual Ray   intersect(Ray &ray_in) const = 0;
  // virtual Hit   intersect(Ray &ray_in, int count_hits) const = 0;
  virtual void  draw() const = 0;
  virtual void  update() = 0;
  virtual void  update_path() = 0;
  virtual void  draw_construction() const = 0;
  virtual void  draw_focalpoint() const = 0;

  float  snells_law(float alpha_i, float n_i, float n_t)                  const;
  vec3   cacl_angle_ray_normal(vec3 const &ray_in, vec3 const &normal_in) const;
  float  compute_lens_angle(float radius_ , float diameter_lens_)         const;


  virtual Hit depthtest(Ray const &ray_in) const = 0;
  void scale(float faktor)                  ;
  void translate(vec3 const& vec)           ;
  void rotate(float angle,vec3 const& vec)  ;

  //----------------------------------------------------------------------------
  //MEMEBER-VARIABLEN-----------------------------------------------------------
  //----------------------------------------------------------------------------
  vec3  m_orig;           //Origin -  Mittelpunkt der Linse
  float m_direction;       //Real-Durchmesser der Linse

private:


};
