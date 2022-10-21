 #include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  setup_gui();

  beamer_pos =  {300, 100, 0};
  beamer_size = {50, 20, 20};
  ursp = {0, 0, 0};
  pnt_x = {0, 0, 0};
  pnt_y = {0, 0, 0};
  ray_n = {1, 0, 0};
  ray_pos = {0,0,0};
  ray_mir_l = 600;
  mirror_n_ = {-1, 1, 0};
  mirror_pos = {300, 0, 0};
  mirror_n = {-1, 1, 0};
  mirror_le = 60;
  mirror_n_le = 90;
  ray_o_l = 400;
  image_dis = {0, 550, 0};
  image_le = {192, 0, 144};
  // cout << "mirror_n_ " << mirror_n_ << endl;
  // cout << "mirror_n " << mirror_n << endl;
  mirror_n = normalize(mirror_n);
  mirror_n_ = normalize(mirror_n_);
  float angle_mir = orientedAngle((mirror_n_), (mirror_n), {1,0,0});
  // cout << "angle mir " << angle_mir << endl;
  ray_n = normalize(ray_n);

  bool inters = false;
  inters = glm::intersectRayPlane(ray_pos, ray_n, mirror_pos, mirror_n, intersectionDis);
  if (inters == true){
    // cout<< "intersection was true  " << inters << " idstance is "<< intersectionDis<< endl;
  }


//computations for all other variables
ray_s[0] = ray_pos[0];
ray_s[1] = ray_pos[1];
ray_s[2] = ray_pos[2];
//ray_e[0] = ray_s[0]+ray_n[0]*ray_mir_l;
//ray_e[1] = ray_s[1]+ray_n[1]*ray_mir_l;
ray_e = ray_s +ray_n*float(dist_b_m);//
//
// lf.pos = {1000, 100, 0};
// lf.dim = {500, 50, 0};
// lf.col_bg = {255, 250, 226};
mirror_n = normalize(mirror_n);
mirror_re = v_r_90cw(mirror_n);
//mirror_re = (mirror_n);
// cout << "mirror_n rot"<< mirror_re<< endl;
mirror_l_norm = sqrt(mirror_re[0]*mirror_re[0]+mirror_re[1]*mirror_re[1]);
// cout << "mirror_l_norm "<< mirror_l_norm<< endl;
mirror_re = mirror_re*mirror_le/2+ray_e;
mirror_li = v_r_90ccw(mirror_n)*mirror_le/2+ray_e;
//mirror_li = (mirror_n)*mirror_le/2+ray_e;
// cout << "mirror_li "<< mirror_li<< endl;
// cout << "mirror_re "<< mirror_re<< endl;
mirror_n_draw = mirror_n*mirror_n_le+ray_e;
image_dis = float(dist_m_p)+ray_e;
image_plane_s = image_dis-image_le/2;
image_plane_e = image_dis+image_le/2;


bool intersection = false;
vec3 plane_normal = {0, -1, 0};
intersection = glm::intersectRayPlane(ray_e, normalize(reflect(ray_n, mirror_n)), image_plane_s, plane_normal, intersectionDistance);
if (intersection == true){
    // cout<< "intersection was true  " << intersection << " idstance is "<< intersectionDistance<< endl;
  }

ray_o = normalize(reflect(ray_n, mirror_n))*intersectionDistance+ray_e; //*ray_o_l;

// float d = 500; //distance mirror plane in cm
// float x = 10; //distance von punkt zu lotrechter auf plane
// float alpha_r = atan( x, d);
// float alpha_d = alpha_r * (180.0/3.141592653589793238463);
// vec3 testrot = {120, 20, 0};
// cout << testrot << endl;
// vec3 testnorm = {0, 0,  1 };
// testrot = rotate(testrot , 1.5708f , testnorm);
// cout << testrot << endl;

//
//
// lf.pos = {1000, 100, 0};
// lf.dim = {500, 50, 0};
// lf.col_bg = {255, 250, 226};
}

void ofApp::setup_gui(){

  	gui.setup(); // most of the time you don't need a name
  	gui.add(angle_a.setup("angle", 0, 10, 300));
  	gui.add(plane.setup("Plane coords", {500, 500, 0}, {0, 0, 0}, {800, 900, 600}));
    gui.add(dist_b_m.setup("Distance Beamer mirror", 300, 100, 900));
    gui.add(dist_m_p.setup("Plane distance in cm", 600, 150, 900));
    gui.add(plane_w.setup("Plane width in cm ", 560, 0, 800));
    gui.add(plane_h.setup("Plane height in cm", 560, 0, 800));
    //simulation
    gui.add(sim_img_w.setup("sim_img width", 500, 1, 6000));
    gui.add(sim_img_h.setup("sim_img height", 500, 1, 6000));
    gui.add(sim_sp_x.setup("sim_sp x", 500, 0, 6000));
    gui.add(sim_sp_y.setup("sim_sp y", 500, 0, 6000));
    gui.add(mirr_w.setup("mirr width", 0, 0, 1000));
    gui.add(mirr_h.setup("mirr height", 0, 0, 1000));
    gui.add(sim_mir_pos_x.setup("sim_mir pos x", 0, 0, 1000));
    gui.add(sim_mir_pos_y.setup("sim_mir pos y", 0, 0, 1000));

  	gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    gui.setPosition(50, 50);

    // lf.setup();
}


//--------------------------------------------------------------
void ofApp::update(){
  //computations for all other variables
  ray_s[0] = ray_pos[0];
  ray_s[1] = ray_pos[1];
  ray_s[2] = ray_pos[2];
  ray_e = ray_s +ray_n*float(dist_b_m);

  mirror_n = normalize(mirror_n);
  mirror_re = v_r_90cw(mirror_n);
  mirror_l_norm = sqrt(mirror_re[0]*mirror_re[0]+mirror_re[1]*mirror_re[1]);
  mirror_re = mirror_re*mirror_le/2;
  mirror_li = v_r_90ccw(mirror_n)*mirror_le/2;
  mirror_n_draw = mirror_n*mirror_n_le;


  image_dis[1] = float(dist_m_p);
  image_plane_s = image_dis-image_le/2;
  image_plane_e = image_dis+image_le/2;

  ray_o = normalize(reflect(ray_n, mirror_n))*intersectionDistance; //*ray_o_l;

  drw_pln[0] = 0;
  drw_pln[1] = dist_m_p;
  drw_pln[2] = 0;

  bool intersection = false;
  vec3 plane_normal = {0, -1, 0};
  intersection = glm::intersectRayPlane(ray_e, normalize(reflect(ray_n, mirror_n)), drw_pln, plane_normal, intersectionDistance);
  if (intersection == true){
    //  cout<< "intersection was true  " << intersection << " idstance is "<< intersectionDistance<< endl;
    }

  if(sim_sp_x > sim_img_w){sim_sp_x=int(sim_img_w);}
  if(sim_sp_y > sim_img_h){sim_sp_y=int(sim_img_h);}



}

//--------------------------------------------------------------
void ofApp::draw(){




	gui.draw();

  // lf.draw();


  ofPushMatrix();
  ofNoFill();

    ofBeginShape();  //Beamer
      ofSetColor(255,255,255);
      ofDrawRectangle(beamer_pos[0], beamer_pos[1], beamer_size[0], beamer_size[1]*2);
    ofEndShape();

    ofTranslate(beamer_pos[0]+beamer_size[0], beamer_pos[1]+beamer_size[1], 0);

    ofBeginShape();   //RAy from Beamer to Mirror
      ofSetColor(255, 255, 255);
      ofDrawLine(ray_s, ray_e);
    ofEndShape();

  //  ofTranslate(ray_e[0]-ray_s[0],ray_e[1]-ray_s[1], 0 );
    ofTranslate(ray_e-ray_s);

    ofBeginShape();   //Mirror + normal
      ofSetColor(0,0,255);
      ofDrawArrow({0,0,0}, mirror_n_draw, 5);
      ofSetColor(0,255,0);
      ofDrawLine(mirror_re[0], mirror_re[1], mirror_li[0], mirror_li[1]);
    ofEndShape();

    ofBeginShape(); // Rays out of Mirror
      ofSetColor(255,255,255);
      ofDrawLine(ray_o[0], ray_o[1], 0, 0); //center no tilt no pan
      krds[0] = 0;
      krds[1] = 0;
      ofDrawBitmapString(ofToString(krds), drw_pln[0]+5, drw_pln[1]-5);
      ofDrawBitmapString(ofToString("d= "), drw_pln[0]+5, drw_pln[1]-5-dist_m_p/2);
      ofDrawBitmapString(ofToString(int(dist_m_p)), drw_pln[0]+32, drw_pln[1]-5-dist_m_p/2);
      ofSetColor(128, 128, 128);
      ofDrawLine(0, 0, ray_o[0]+plane_w/2, ray_o[1]); //center max pan
      krds[0] = int(drw_pln[0]+plane_w/2);
      krds[1] = drw_pln[2];
      ofDrawBitmapString(ofToString(krds), drw_pln[0]+plane_w/2+5, drw_pln[1]-5);
      ofSetColor(128, 128, 128);
      ofDrawLine(0, 0, ray_o[0]-plane_w/2, ray_o[1]); //center min pan
      krds[0] = int(drw_pln[0]+plane_w/2);
      krds[1] = drw_pln[2];
      ofDrawBitmapString(ofToString(krds), drw_pln[0]-plane_w/2-55, drw_pln[1]-5);

      float xx = (float(sim_sp_x) / float(sim_img_w)-0.5f)*float(plane_w);
      float yy = (float(sim_sp_y) / float(sim_img_h)-0.5f)*float(plane_h);
      smple_ray = drw_pln;
      smple_ray[0] = xx;
      smple_ray[2] = yy;
      ofSetColor(255, 128, 0);
      ofDrawLine(ursp, smple_ray);
      krds[0] = smple_ray[0]+plane_w/2;
      krds[1] = smple_ray[2];
      vec3 nme_r = smple_ray;
      nme_r[0] = xx-55;
      nme_r[2] = yy-5;
      ofDrawBitmapString(ofToString(krds), smple_ray);
      krds[0] = int(drw_pln[0]+plane_w/2);
      krds[1] = drw_pln[2];
      ofDrawBitmapString(ofToString(krds), drw_pln[0]-plane_w/2-55, drw_pln[1]-5);
    ofEndShape();

    ofTranslate(drw_pln);
    ofBeginShape();
      ofSetColor(0,0,0);
      ofSetColor(125, 125, 0);
      ofDrawBox({0,0,0}, plane_w, 1, plane_h);
    ofEndShape();




  ofSetColor(255, 128 , 0);
  vec2 compangl = compute_angle_sampleray(smple_ray);
  ofDrawBitmapString(ofToString("Angle"), ofGetWidth(), 40);
  ofDrawBitmapString(ofToString(compangl), 0, 60);

  ofPopMatrix();



}





void ofApp::vector_reflect(){
  //Beam firstBeam = Beam((0,0,0),(0,0,1));

  vec3 l(1.f, -1.f, 0.f);
  vec3 n(0.0f, 1.f, 0.f);
  vec3 r(0.0f, 0.0f, 0.0f);

  vec2 l_2(1.f, -1.f);
  l_2 = normalize(l_2);
  vec2 n_2(0.0f, 1.f);
//  n_2 = normalize(n_2);

  cout<< "l: "<< l<<endl;
  cout<< "n: "<< n<<endl;
  cout<< "r: "<< r<<endl;

  l = normalize(l)*-1.f;
  n = normalize(n);

  float angle_ln = angle(l, n);

  cout << "angle_ln: "<< angle_ln << endl;

  float OriAngle = orientedAngle(l_2, n_2);

  cout << "OriAngle: "<< OriAngle << endl;

  cout<< "l: "<< l<<endl;
  cout<< "n: "<< n<<endl;
  cout<< "r: "<< r<<endl;


  float dp = dot(l, n);

  cout<< "after dot product dp : "<< dp<<endl;

  vec3 dpn = n* dp;

  cout<< "after dot product * n   dpn : "<< dpn<<endl;

  vec3 dpn2 = dpn *2;

  cout<< "after dot product*n*2  dpn2 : "<< dpn2<<endl;

  vec3 minuslplusdpn2 = -l+dpn2;

  cout<< "minuslplusdpn2 : "<< minuslplusdpn2<<endl;

  vec3 malminus1 = minuslplusdpn2 * -1.0f;

    cout<< "minuslplusdpn2 : "<< malminus1<<endl;



  vec3 reflectionvector = reflect(l, n);

  cout<< "using reflect::" << reflectionvector<< endl;


  //Mirror myMirror = Mirror((0,0,10);(0,-1,-1));

//  fvec3  new_ray = myMirror.reflect(firstBeam);

  cout<<" this is new ray:" << endl;
//  cout<< new_ray<<endl;


}


vec3 ofApp::v_r_90cw(vec3 v_in){
  vec3 v_out = {-v_in[1], v_in[0], v_in[2]};
  return v_out;
}

vec3 ofApp::v_r_90ccw(vec3 v_in){
  vec3 v_out = {v_in[1], -v_in[0], v_in[2]};
  return v_out;
}



vec2 ofApp::compute_angle_sampleray(vec3 s_ray_in ){
  vec2 angles;
  vec3 mulx_vec = {1,1,0}; //mulx_vec for displaying only one direction of ray
  vec3 muly_vec = {0,1,1};
  vec3 sr_x = normalize(s_ray_in*mulx_vec);
  vec3 sr_y = normalize(s_ray_in*muly_vec);
  vec3 ray_norm = {0,1,0};
  vec3 rotrefy = {1,0,0};
  vec3 rotrefx = {0,0,1};
  float r_angle_x = orientedAngle(sr_x, ray_norm, rotrefx)* (180.0/3.141592653589793238463);
  float r_angle_y = orientedAngle(sr_y, ray_norm, rotrefy)* (180.0/3.141592653589793238463);
  angles[0] = r_angle_x/2;
  angles[1] = r_angle_y/2;

  return  angles;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  cout << "mouse-dr   x:" << x << " y:" << y << " button:" << button << endl;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  cout << "mouse-pr   x:" << x << " y:" << y << " button:" << button << endl;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
