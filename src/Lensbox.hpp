#pragma once

// #include <limits>

#include "shape.hpp"
#include "hit.hpp"

class Lensbox : public Shape{
public:
  //KONSTRUTOREN----------------------------------------------------------------
  Lensbox();
  Lensbox(glm::vec3 const& min, glm::vec3 const& max);
  //Lensbox(std::string const& name, Material const& mat, glm::vec3 const& min, glm::vec3 const& max);
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

  void scale(float faktor) override;
  void translate(glm::vec3 const& vec) override;
  void rotate(float angle,glm::vec3 const& vec) override;


private:
  glm::vec3 m_min;
  glm::vec3 m_max;
};
