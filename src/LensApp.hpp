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
#include "State.hpp"
#include "lensefield.hpp"
#include "Lens.hpp"



using namespace glm;

class LensApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

//---------------------------------------------
	// ofxPanel gui;
	//
	// ofxFloatSlider angle_a;
	// ofxVec3Slider plane;
	// ofxIntSlider dist_b_m;
	// ofxIntSlider dist_m_p;
	// ofxIntSlider plane_w;
	// ofxIntSlider plane_h;
	//
	// ofxIntSlider sim_img_w;
	// ofxIntSlider sim_img_h;
	// ofxIntSlider sim_sp_x;
	// ofxIntSlider sim_sp_y;
	// ofxIntSlider mirr_w;
	// ofxIntSlider mirr_h;
	// ofxIntSlider sim_mir_pos_x;
	// ofxIntSlider sim_mir_pos_y;
	// ofxLabel screenSize;
	//
	//
	// ofParameterGroup parameters;
  // ofParameter<float> r1;
  // ofParameter<float> r2;
	//
	// ofParameter<ofColor> color;
	// ofxPanel gui;


	//-----Information holding struct----------------------------------------


	shared_ptr<State> shrd;

	//------Containers for lenses---------------------------------------

	std::shared_ptr<Composite> m_composite; 	//All the lenses etc.
	std::vector<std::shared_ptr<Shape>> m_lens_shapes;


};
