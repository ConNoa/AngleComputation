#pragma once

// #include <limits>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "ofxGui.h"
#include "ofxCv.h"
#include <iostream>
#include "shape.hpp"
#include "hit.hpp"

class Lensbox : public Shape{
public:
  //KONSTRUTOREN----------------------------------------------------------------
  Lensbox();
  Lensbox(glm::vec3 const& min, glm::vec3 const& max);
  Lensbox(glm::vec3 const& orig, float diameter, float width, float r1, float r2, float n);
  Lensbox(std::string const& name, std::shared_ptr<Material> mat, glm::vec3 const& min, glm::vec3 const& max);
  ~Lensbox()override;

  //GETTER----------------------------------------------------------------------
  glm::vec3 const& max() const;
  glm::vec3 const& min() const;

  //SETTER----------------------------------------------------------------------
  void max(glm::vec3 const& max);
  void min(glm::vec3 const& min);

  //FUNKTIONEN------------------------------------------------------------------
  std::ostream& print(std::ostream& os) const override;
  Hit intersect(Ray ray) const override;

  void draw() const override;
  void draw_construction() const;

  void update() override;

  void scale(float faktor) override;
  void translate(glm::vec3 const& vec) override;
  void rotate(float angle,glm::vec3 const& vec) override;

  //Hilfsfunktionen
  float compute_lens_angle(float radius_ , float diameter_lens_);


private:
  glm::vec3 m_min;
  glm::vec3 m_max;

  glm::vec3 m_orig;       //Origin -  Mittelpunkt der Linse
  float m_diameter;       //Real-Durchmesser der Linse
  float m_width;          //Breite des Glaskörpers zwischen geschliffenen Linsenseiten

  float m_r1;             //Radius der theoretischen Kugel der vorderen Linsenseite
  float m_r2;             //Radius der theoretischen Kugel der hinteren Linsenseite

  float m_n;              //Brechungsindex der Linse

  glm::vec3 m_center_d0;  //vorderer Scheitelpunkt der Linse
  glm::vec3 m_center_d1;  //Linsendurchmesser vollständig vordere Linsenseite (manchmal auch H1 ?  Hauptpunkt)
  glm::vec3 m_center_d2;  //Linsendurchmesser vollständig hintere Linsenseite (manchmal auch H2 ?  Hauptpunkt)
  glm::vec3 m_center_d3;  //hinterer Scheitelpunkt der Linse


  glm::vec3 m_f1;         //vorderer Brennpunkt
  glm::vec3 m_f2;         //vorderer Brennpunkt


  //variables for draw and visualisation
  ofPath lens;

  glm::vec3 m_O_d1;       //Top Point for outerLensediameter  für Mittelachse
  glm::vec3 m_O_d2;       //Bottom Point for outerLensediameter  für Mittelachse

  float   m_ankat_r1;
  float   m_ankat_r2;

  float   m_ankat_angle_r1;
  float   m_ankat_angle_r2;

  glm::vec3 NULLPUNKT {0, 0, 0};
  glm::vec3 m_trans_vec {0, 0, 0};


};
