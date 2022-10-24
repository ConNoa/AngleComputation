#pragma once


#include <iostream>
#include "ofMain.h"
#include "ofxGui.h"
// #include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include "Mirror.hpp"
#include "Beam.hpp"
#include <glm/gtx/intersect.hpp>
#include "LensApp.hpp"
#include "State.hpp"


// #include "attributes.hpp"
using namespace glm;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void setup_gui();
		void setup_lensfield();
		void update();
		void draw();
		void draw_lensfield();
		void vector_reflect();
		vec3 v_r_90cw(vec3 v_in);
		vec3 v_r_90ccw(vec3 v_in);


		vec2 compute_angle_sampleray(vec3 s_ray_in);

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






		//vorgaben:
		vec3 		beamer_pos;
	  vec3 		beamer_size;

		vec3 		mirror_n_;
		vec3 		mirror_pos;
		vec3 		mirror_n;
		vec3 		mirror_n_draw;
		float  	mirror_le;  //length
		float 	mirror_n_le;
		vec3 		mirror_li;
		vec3 		mirror_re;
		float		mirror_l_norm;		//length of normalized

		vec3 		image_plane_s;
		vec3 		image_plane_e;
		vec3 		image_le;
		vec3 		image_dis;

		vec3 		ray_n;	//ausrichtung des strahls
		vec3 		ray_pos;
		float 	ray_mir_l;// laenge des strahls bevor er auf den Mirror Trifft
		vec3 		smple_ray;

		//errechnen sich:
		vec3 		ray_s;//raystart
		vec3 		ray_e; //rayend
		vec3 		drw_pln;

		vec3 		ursp;


		vec2 krds;
		vec3 pnt_x;
		vec3 pnt_y;
		vec3 rAm_v;  //normale von Ray nachdem er auf den Mirror aufgetroffen ist (Richtungsvektor)  //zentrum des Projezierten Bildes
		vec3 rAm_rotref;  //rotationsrefferenz um die winkel zwischen lotrechter und abgewinkeltem lichtstrahl zu berechnen
		vec3 ray_o;
		float ray_o_l;
		float intersectionDistance;
		float intersectionDis;


		ofColor red;
		ofColor blue;
		ofColor green;

//------------------------------------------------

		ofxPanel gui;

		ofxFloatSlider angle_a;
		ofxVec3Slider plane;
		ofxIntSlider dist_b_m;
		ofxIntSlider dist_m_p;
		ofxIntSlider plane_w;
		ofxIntSlider plane_h;

		ofxIntSlider sim_img_w;
		ofxIntSlider sim_img_h;
		ofxIntSlider sim_sp_x;
		ofxIntSlider sim_sp_y;
		ofxIntSlider mirr_w;
		ofxIntSlider mirr_h;
		ofxIntSlider sim_mir_pos_x;
		ofxIntSlider sim_mir_pos_y;
		ofxLabel screenSize;


		shared_ptr<LensApp> lenses;

		shared_ptr<State> shrd;



};
