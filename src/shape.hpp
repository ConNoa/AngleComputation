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
  virtual void update_path() = 0;

  virtual void scale(float faktor) = 0;
  virtual void rotate(float angle,glm::vec3 const& vec) = 0;
  virtual void translate(glm::vec3 const& vec)  = 0;


private:
  std::string m_name;
  std::shared_ptr<Material> m_mat;


};

std::ostream& operator << (std::ostream& os, Shape const& s);
