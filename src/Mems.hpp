#pragma once


// #include <limits>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "ofxGui.h"
#include "ofxCv.h"
#include <iostream>
#include <vector>
#include "ray.hpp"

using namespace glm;

class Mems
{

public:

    Mems();
    Mems(vec3 const &orig, vec3 const &orient);
    Mems(vec3 const &orig, vec3 const &orient, vec3 const &dimensions, vec2 const &amm_mirr);
    ~Mems();

    void setup();
    void update();

    void draw();

    // void addRay();
    void addRay(vec3 const& origin, float angle);
    void addRay(vec3 const& origin, float angle, ofColor const& col_in);

    void scale(float faktor);
    void translate(glm::vec3 const& vec);
    void rotate(float angle,glm::vec3 const& vec);

    std::ostream& print(std::ostream& os) const;


    vec3 m_orig;                //Position of Mems in 3D Space
    vec3 m_orient;              //Orientation of Mems in 3D Space
    vec3 m_dimensions;          //width & height of Mems
    vec2 m_amm_mirr;            //Ammount of Mirrors on MEMS in x and y direction

    std::vector<Ray> m_mems_rays;

private:
};
