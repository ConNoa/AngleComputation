#pragma once


#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <iostream>
// #include <map>
// #include <iosfwd>
// #include <opencv2/opencv.hpp>
// #include <string>
// #include "Multipixel.hpp"
// #include "ofMain.h"
// #include "ofxDatGui.h"
// #include "ofxGui.h"
// #include "ofxCv.h"
// #include "ofxOpenCv.h"
// #include "Pixel.hpp"
//
// using namespace cv;
// using namespace std;
using namespace glm;



class Lensefield{
  public:

    Lensefield();
    ~Lensefield();

    void setup();
    void draw();

    vec3 pos;
    vec3 dim;
    ofColor col_bg;


};
