#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "ofxGui.h"
#include "ofxCv.h"

#include <iostream>

using namespace glm;


class Lens{
  public:

    Lens();
    ~Lens();
    Lens(int orig_inx, int orig_iny,int orig_inz, float d_in, float r1_in, float r2_in, float n_in, float breite_in);
    Lens(vec3 orig_in, float d_in, float r1_in, float r2_in, float n_in, float breite_in);

    void setup();
    void draw();
    void draw_construction();
    float compute_lens_angle(float radius_ , float diameter_lens_);
    void print();

    void translate(vec3 translation_in);
    void rotate(float rotation_in);


    vec3 orig_;
    vec3 dir_;
    vec3 normal_;
    float breite_;

    int o_x;
    int o_y;
    int o_z;

    float r1_;     //Radius1
    float r1_d;
    vec3 f1;

    float r2_;     //Radius2
    float r2_d;
    vec3 f2;


    float d_;      //Durchmesser
    vec3 d_1;

    vec3 d_2;
    float n_;      //Brechfaktor
    vec3 tr_in;

  	ofPath path;
  	ofPath path2;
  	ofPath path3;
    ofPath lens1;



};
