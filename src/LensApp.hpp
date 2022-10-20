#pragma once


#include <iostream>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include "Mirror.hpp"
#include "Beam.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtx/intersect.hpp>
#include "Composition.hpp"
#include "shape.hpp"

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


	std::shared_ptr<Composite> m_composite; 	//All the lenses etc.


};
