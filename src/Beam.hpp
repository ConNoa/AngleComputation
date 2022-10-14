#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <iostream>

class Beam{
  public:

    Beam();
    ~Beam();
    Beam(glm::fvec3 orig_in, glm::fvec3 dir_in);


    glm::fvec3 orig_;
    glm::fvec3 dir_;

};
