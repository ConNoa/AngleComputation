#pragma once

#include "material.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <memory>
#include "ray.hpp"

struct Hit;

class Shape {
public:
  //KONSTRUTOREN----------------------------------------------------------------------
  Shape();
  Shape(std::string const& name, std::shared_ptr<Material> mat);
  virtual ~Shape();

  //FUNKTIONEN------------------------------------------------------------------------
  std::string name() const;
  std::shared_ptr<Material> material() const;

  virtual std::ostream& print(std::ostream& os) const;
  virtual Hit intersect(Ray &ray_in, int count_hits) const = 0;
  virtual void draw() const = 0;


  virtual void update() = 0;

  virtual void scale(float faktor) = 0;
  virtual void rotate(float angle,glm::vec3 const& vec) = 0;
  virtual void translate(glm::vec3 const& vec)  = 0;

  // glm::vec3 m_orig;       //Origin -  Mittelpunkt der Linse
  // float m_diameter;       //Real-Durchmesser der Linse
  // float m_width;          //Breite des Glaskörpers zwischen geschliffenen Linsenseiten
  //
  // float m_r1;             //Radius der theoretischen Kugel der vorderen Linsenseite
  // float m_r2;             //Radius der theoretischen Kugel der hinteren Linsenseite
  //
  // float m_n;              //Brechungsindex der Linse
  //
  // glm::vec3 m_center_d0;  //vorderer Scheitelpunkt der Linse
  // glm::vec3 m_center_d1;  //Linsendurchmesser vollständig vordere Linsenseite (manchmal auch H1 ?  Hauptpunkt)
  // glm::vec3 m_center_d2;  //Linsendurchmesser vollständig hintere Linsenseite (manchmal auch H2 ?  Hauptpunkt)
  // glm::vec3 m_center_d3;  //hinterer Scheitelpunkt der Linse
  //
  //
  // glm::vec3 m_f1;         //vorderer Brennpunkt
  // glm::vec3 m_f2;         //vorderer Brennpunkt
  //
  //
  //
  //
  // glm::vec3 m_O_d1;       //Top Point for outerLensediameter  für Mittelachse
  // glm::vec3 m_O_d2;       //Bottom Point for outerLensediameter  für Mittelachse
  //
  // float   m_ankat_r1;
  // float   m_ankat_r2;
  //
  // float   m_ankat_angle_r1;
  // float   m_ankat_angle_r2;
  //
  // glm::vec3 NULLPUNKT {0, 0, 0};
  // glm::vec3 m_trans_vec {0, 0, 0};
  //
  // int     m_type_r1;
  // int     m_type_r2;


private:
  std::string m_name;
  std::shared_ptr<Material> m_mat;


};

std::ostream& operator << (std::ostream& os, Shape const& s);
