#pragma once


#include <iostream>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDatGui.h"

#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include "Mirror.hpp"
#include "Beam.hpp"
// #include <glm/glm.hpp>
// #include <glm/vec3.hpp> // glm::vec3
// #include <glm/vec4.hpp> // glm::vec4
// #include <glm/gtx/intersect.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include "shape.hpp"
#include "State.hpp"
#include "lensefield.hpp"
#include "Lens_konvex.hpp"
#include "Lens_konkav.hpp"
#include "Mems.hpp"
#include "Lens_konkav.hpp"
#include "Lens_konvex.hpp"



using namespace glm;

class LensApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();


	void ray_shape_hit(int round, Ray & ray, std::vector<std::shared_ptr<Shape>> const& shapes);
	void setup_gui();
	void setup_lens();

	void load_lens_parameters(int lens_nmbr);
	void change_lens_parameters(std::string label_in);


	void onToggleEvent(ofxDatGuiToggleEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);
	void onButtonEvent(ofxDatGuiButtonEvent e);


	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	//-----Information holding struct----------------------------------------


	shared_ptr<State> shrd;


	Mems m_mems;

		std::vector<std::shared_ptr<Shape>> m_all_shapes;

		// std::shared_ptr<Shape> lens_inside;

	//std::shared_ptr<Composite> m_composite; 	//All the lenses etc.


};
