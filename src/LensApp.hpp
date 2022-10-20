#pragma once


#include <iostream>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include "Mirror.hpp"
#include "Beam.hpp"
#include <glm/gtx/intersect.hpp>
#include "hit.hpp"
#include "lensefield.hpp"
#include "Lens.hpp"



using namespace glm;

class LensApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();


	ofParameterGroup parameters;
  ofParameter<float> r1;
  ofParameter<float> r2;

	ofParameter<ofColor> color;
	ofxPanel gui;

	ofPath path;
	ofPath path2;
	ofPath path3;


	Lens test_lens;
	Lens lens2;

};