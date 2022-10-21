#pragma once



#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxGui.h"

#include <memory>


struct State{


ofxDatGui* m_gui;
ofxDatGuiDropdown* dropdown;
ofxDatGui* zoom_gui;
ofxDatGuiToggle* sample_toggle;
ofxDatGuiButton* resample;
ofxDatGui* angle_gui;
vector<ofxDatGuiComponent *> components;
//-----sampleparameters
ofParameter<bool> restart_sampling = false;
ofParameter<int> rand_seed_samp;
ofParameter<int> m_sampleamm_abs;
ofParameter<float> m_sampleamm_rel;
ofParameter<int> m_superpix_res;
ofParameter<int> superpixel_width;
ofParameter<int> superpixel_height;
ofParameter<int> cosx_e;
ofParameter<int> cosy_e;
ofParameter<int> border_width;
ofParameter<int> border_height;
ofParameter<int> out_res_x;
ofParameter<int> out_res_y;
ofParameter<bool> switch_screen1 = false;
ofParameter<bool> safe_images = false;
//-----zoom-GUI
ofParameter<float> m_zoom_fac;
ofParameter<int> b_zoom_fac;

//-----command-GUI
ofParameter<bool> compute_filter;
ofParameter<bool> randomsamp;
ofParameter<bool> switch_screen2;
//----informational-GUI
ofParameter<int> dim_SP_ges_x;
ofParameter<int> dim_SP_ges_y;
ofxLabel dim_monitor1;
ofxLabel label;

//colors
ofColor black;

//Anglecalculation

ofParameter<bool> ang_sh;

ofParameter<float> max_angle;
ofParameter<int> dist_m_p;

ofParameter<int> plane_w;
ofParameter<int> plane_h;

ofParameter<int> sim_sp_x;
ofParameter<int> sim_sp_y;

};
