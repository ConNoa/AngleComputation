#pragma once

#include <cmath>
#include <catch.hpp>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include "shape.hpp"
#include "Lensbox.hpp"
// #include "sphere.hpp"

#include "ray.hpp"
#include "hit.hpp"



class Composite : public Shape
{
 public:
    //KONSTRUTOREN----------------------------------------------------------------------
    Composite();
    Composite(std::string const& name);
    ~Composite();

    //FUNKTIONEN-------------------------------------------------------------------------
    Hit intersect(Ray ray) const;
    /*
    void translate(glm::vec3 const& distance) override;
    void rotate(double angle, glm::vec3 const& point) override;
    void scale(double scale_factor) override;
    */
    void add(std::shared_ptr<Shape>  shape_ptr);
    //
    void scale(float faktor) override;
    void rotate(float angle,glm::vec3 const& vec) override;
    void translate(glm::vec3 const& vec) override;


 private:
    std::string m_name;
    std::vector<std::shared_ptr<Shape>> m_shapes;
};
