#pragma once

#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Beam.hpp"

class Mirror{
  public:

    Mirror();
    ~Mirror();
    Mirror(glm::fvec3 orig_in, glm::fvec3 dir_in);

    glm::fvec3 reflect(Beam const& beam_in);


    glm::fvec3  orig_;
    glm::fvec3  norm_;

};
