#pragma once


#include "ofxDatGui.h"
#include <memory>
// #include "ofxGui.h"


struct State{


ofxDatGui* lens_attr_gui;
// ofxDatGuiDropdown* dropdown;
// ofxDatGui* zoom_gui;
// ofxDatGuiToggle* sample_toggle;
// ofxDatGuiButton* resample;
// ofxDatGui* angle_gui;
// vector<ofxDatGuiComponent *> components;


//-----Lensparameters
ofParameter<int> s_orig_x;
ofParameter<int> s_orig_y;
ofParameter<int> s_orig_z;
ofParameter<int> s_rot_z;
ofParameter<float> s_diameter;
ofParameter<float> s_width;
ofParameter<int> s_type_r1;
ofParameter<float> s_r1;
ofParameter<int> s_type_r2;
ofParameter<float> s_r2;
ofParameter<float> s_n;


ofParameter<bool> s_show_constr_lines;
ofParameter<bool> s_draw_rays;
ofParameter<bool> s_draw_normals;
ofParameter<bool> s_show_focus_etc;
ofParameter<int>  s_select_lens;
ofParameter<bool> s_store_lens;

/*
>s_orig_x;
>s_orig_y;
>s_orig_z;
>s_rot_z;
>s_diameter;
>s_width;
>s_type_r1;
>s_r1;
>s_type_r2;
>s_r2;
>s_n;
>show_constr_lines;
>show_rays;
>show_focus_etc;
>select_lens;
>store_lens;
*/


/*
//
// ofxLabel dim_monitor1;
// ofxLabel label;

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
*/


//------Containers for lenses---------------------------------------

};
