#include "Mirror.hpp"


Mirror::Mirror() {
    std::cout << "Mirror is being created" << std::endl;
}
Mirror::~Mirror() {
    std::cout << "Mirror is being deleted" << std::endl;
}
Mirror::Mirror(glm::fvec3 orig_in, glm::fvec3 norm_in):
        orig_(orig_in),
        norm_(norm_in){}


glm::fvec3 Mirror::reflect(Beam  const& beam_in){
  glm::fvec3 dir_in  = beam_in.dir_;
  glm::fvec3 r;
  norm_ = glm::normalize(norm_);
  //dir_in = glm::normalize(dir_in);

  r = dir_in -2*glm::dot(dir_in, norm_)*norm_;


  return r;
}
