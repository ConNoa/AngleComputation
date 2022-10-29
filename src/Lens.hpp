#pragma once

#include "hit.hpp"
#include "shape.hpp"

using namespace glm;

class Lens : public Shape {

public:
  //KONSTRUTOREN----------------------------------------------------------------
  Lens();
  Lens(int mat_id);
  Lens(std::string const& name, int mat_id);
  Lens(vec3 const& orig, float diameter, float width, float r1, float r2);
  Lens(vec3 const& orig, float diameter, float width, float r1, float r2, int mat_id);
  virtual ~Lens();

  //FUNKTIONEN------------------------------------------------------------------
  virtual std::ostream& print(std::ostream& os) const;
  virtual Ray   intersect(Ray &ray_in) const = 0;
  virtual Hit   intersect(Ray &ray_in, int count_hits) const = 0;
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
  float m_diameter;       //Real-Durchmesser der Linse
  float m_width;          //Breite des Glaskörpers zwischen geschliffenen Linsenseiten
  float m_r1;             //Radius der theoretischen Kugel der vorderen Linsenseite
  float m_r2;             //Radius der theoretischen Kugel der hinteren Linsenseite





  // float m_n;              //Brechungsindex der Linse
  //
  // float m_rot_z;          //Rotation der Linse um die Z-Achse
  //
  //
  // const float m_n_air = 1.000292f;
  //
  // vec3 m_center_d0;       //vorderer Scheitelpunkt der Linse
  // vec3 m_center_d1;       //Linsendurchmesser vollständig vordere Linsenseite (manchmal auch H1 ?  Hauptpunkt)
  // vec3 m_center_d2;       //Linsendurchmesser vollständig hintere Linsenseite (manchmal auch H2 ?  Hauptpunkt)
  // vec3 m_center_d3;       //hinterer Scheitelpunkt der Linse
  //
  // vec3 m_center_r1;       //Mittelpunkt des Kreises um R1
  // vec3 m_center_r2;       //Mittelpunkt des Kreises um R2
  //
  // vec3 m_f1;              //vorderer Brennpunkt
  // vec3 m_f2;              //vorderer Brennpunkt
  //
  //
  // // variables for draw and visualisation
  // //----------------------------------------------------------------------------
  //
  // ofPath  lens;
  //
  // vec3    m_O_d1;       //Top Point for outerLensediameter  für Mittelachse
  // vec3    m_O_d2;       //Bottom Point for outerLensediameter  für Mittelachse
  //
  // float   m_ankat_r1;
  // float   m_ankat_r2;
  //
  // float   m_ankat_angle_r1;
  // float   m_ankat_angle_r2;
  //
  // vec3    NULLPUNKT {0, 0, 0};
  // vec3    m_trans_vec {0, 0, 0};
  //
  // float   m_D1;
  // float   m_D2;
  //
  // bool    m_show_constr_lines = true;
     bool    m_act_manipulated = false;
  // bool    m_draw_normals = true;
  // bool    m_draw_rays = true;
  // bool    m_draw_focalpoint = true;
  //
  //
  // int     m_type_r1;
  // int     m_type_r2;
  //----------------------------------------------------------------------------

private:


};
