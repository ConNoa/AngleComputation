#include "Beam.hpp"


Beam::Beam() {
    std::cout << "Beam is being created" << std::endl;
}
Beam::~Beam() {
    std::cout << "Beam is being deleted" << std::endl;
}
Beam::Beam(glm::fvec3 orig_in, glm::fvec3 dir_in):
        orig_(orig_in),
        dir_(dir_in){}
