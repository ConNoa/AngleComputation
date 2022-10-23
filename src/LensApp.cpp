#include "LensApp.hpp"

void LensApp::setup(){

    ofBackground(75, 75, 75);

    setup_gui();


    setup_lens();
    load_lens_parameters(shrd->s_select_lens);
    for(auto it : m_lens_shapes){it->update_path();}

    m_mems.setup();

    //run_routine();


}

void LensApp::update(){

  return;
}


void LensApp::draw(){
  for(auto it : m_lens_shapes){
    //    it->print(std::cout);
      it->update();
      it->draw();
  }
  // m_mems.draw();

  for(auto lens_it : m_lens_shapes){
    int counter = 0;
    for(auto ray_it : m_mems.m_mems_rays){
      counter += 1;
      Hit temp_hit;
      temp_hit = lens_it->intersect(ray_it, counter);
    }
  }
  return;
}

void LensApp::setup_gui(){
    //-------------GÚI INTERFACE------------------------------------------------
    shrd->s_orig_x.set("s_orig_x", 680, 0, 1000);
    shrd->s_orig_y.set("s_orig_y", 700, 500, 800);
    shrd->s_orig_z.set("s_orig_z", 0, -600, 600);
    shrd->s_rot_z.set("s_rot_z", 0, 0, 360);

    shrd->s_diameter.set("s_diameter", 521.44, 1, 600);
    shrd->s_width.set("s_width", 50, 0, 100);
    shrd->s_type_r1.set("s_type_r1", 1, 1, 3);
    shrd->s_r1.set("s_r1", 459.02, 0, 4000);
    shrd->s_type_r2.set("s_type_r2", 1, 1, 3);
    shrd->s_r2.set("s_r2", 442.62, 0, 4000);
    shrd->s_n.set("s_n", 2.0f, 1, 3);

    shrd->s_show_constr_lines.set(true);
    shrd->s_draw_rays.set(true);
    shrd->s_draw_normals.set(true);
    shrd->s_show_focus_etc.set(true);
    shrd->s_select_lens.set("Select Lens", 0, 0, 5);
    shrd->s_store_lens.set(false);


    shrd->lens_attr_gui = new ofxDatGui();
    shrd->lens_attr_gui->addLabel("Lens Parameters");
    shrd->lens_attr_gui->addButton("Save Lenssettings");

    shrd->lens_attr_gui->addSlider(shrd-> s_orig_x);
    shrd->lens_attr_gui->addSlider(shrd-> s_orig_y);
    shrd->lens_attr_gui->addSlider(shrd-> s_orig_z);
    shrd->lens_attr_gui->addSlider(shrd-> s_rot_z);

    shrd->lens_attr_gui->addSlider(shrd-> s_diameter);
    shrd->lens_attr_gui->addSlider(shrd-> s_width);
    shrd->lens_attr_gui->addSlider(shrd-> s_type_r1);
    shrd->lens_attr_gui->addSlider(shrd-> s_r1);
    shrd->lens_attr_gui->addSlider(shrd-> s_type_r2);
    shrd->lens_attr_gui->addSlider(shrd-> s_r2);
    shrd->lens_attr_gui->addSlider(shrd-> s_n);

    shrd->lens_attr_gui->addToggle("Draw Construction Lines", shrd->s_show_constr_lines);
    shrd->lens_attr_gui->addToggle("Draw Rays", shrd->s_draw_rays);
    shrd->lens_attr_gui->addToggle("Draw Normals", shrd->s_draw_normals);
    shrd->lens_attr_gui->addToggle("Draw Focus etc", shrd->s_show_focus_etc);
    shrd->lens_attr_gui->addSlider(shrd->s_select_lens);
    shrd->lens_attr_gui->addToggle("Store Lens", shrd->s_store_lens);

    shrd->lens_attr_gui->setPosition(20, 20);
    shrd->lens_attr_gui->onSliderEvent(this, &LensApp::onSliderEvent);
    shrd->lens_attr_gui->onToggleEvent(this, &LensApp::onToggleEvent);
    shrd->lens_attr_gui->onButtonEvent(this, &LensApp::onButtonEvent);


}

void LensApp::setup_lens(){

  vec3 orig_pos;
  orig_pos.x = shrd->s_orig_x;
  orig_pos.y = shrd->s_orig_y;
  orig_pos.z = shrd->s_orig_z;


  std::shared_ptr<Lensbox> lens_2 = std::make_shared<Lensbox>(orig_pos, shrd->s_diameter, shrd->s_width, shrd->s_type_r1, shrd->s_r1, shrd->s_type_r2, shrd->s_r2, shrd->s_n);
    std::cout<< "This is the new created Lens: [ "<< endl;
    lens_2->print(std::cout);
    std::cout<< " ]. " <<std::endl;
  lens_2->update();
  m_lens_shapes.push_back(lens_2);


  return;
}


void LensApp::load_lens_parameters(int lens_nmbr){
  cout<<"load parameters of lens "<< lens_nmbr << endl;

    shrd->s_orig_x = m_lens_shapes[shrd->s_select_lens]->m_orig.x;
    shrd->s_orig_y = m_lens_shapes[shrd->s_select_lens]->m_orig.y;
    shrd->s_orig_z = m_lens_shapes[shrd->s_select_lens]->m_orig.z;
    shrd->s_rot_z = m_lens_shapes[shrd->s_select_lens]->m_rot_z;
    shrd->s_diameter = m_lens_shapes[shrd->s_select_lens]->m_diameter;
    shrd->s_width = m_lens_shapes[shrd->s_select_lens]->m_width;
    shrd->s_type_r1 = m_lens_shapes[shrd->s_select_lens]->m_type_r1;
    shrd->s_r1 = m_lens_shapes[shrd->s_select_lens]->m_r1;
    shrd->s_type_r2 = m_lens_shapes[shrd->s_select_lens]->m_type_r2;
    shrd->s_r2 = m_lens_shapes[shrd->s_select_lens]->m_r2;
    shrd->s_n = m_lens_shapes[shrd->s_select_lens]->m_n;
    shrd->s_show_constr_lines = m_lens_shapes[shrd->s_select_lens]->m_show_constr_lines;
    return;

}

void LensApp::change_lens_parameters(std::string label_in){

  m_lens_shapes[shrd->s_select_lens]->m_act_manipulated = true;

  if (label_in == "s_orig_x"){
    m_lens_shapes[shrd->s_select_lens]->m_orig.x = shrd->s_orig_x;
  }
  if (label_in == "s_orig_y"){
    m_lens_shapes[shrd->s_select_lens]->m_orig.y = shrd->s_orig_y;
  }
  if (label_in == "s_orig_z"){
    m_lens_shapes[shrd->s_select_lens]->m_orig.z = shrd->s_orig_z;
  }
  if (label_in == "s_rot_z"){
      m_lens_shapes[shrd->s_select_lens]->m_rot_z = shrd->s_rot_z;
  }
  if (label_in == "s_diameter"){
      m_lens_shapes[shrd->s_select_lens]->m_diameter = shrd->s_diameter;
  }
  if (label_in == "s_width"){
      m_lens_shapes[shrd->s_select_lens]->m_width = shrd->s_width;
  }
  if (label_in == "s_type_r1"){
      m_lens_shapes[shrd->s_select_lens]->m_type_r1 = shrd->s_type_r1;
  }
  if (label_in == "s_r1"){
      m_lens_shapes[shrd->s_select_lens]->m_r1 = shrd->s_r1;
  }
  if (label_in == "s_type_r2"){
      m_lens_shapes[shrd->s_select_lens]->m_type_r2 = shrd->s_type_r2;
  }
  if (label_in == "s_r2"){
      m_lens_shapes[shrd->s_select_lens]->m_r2 = shrd->s_r2;
  }
  if (label_in == "s_n"){
      m_lens_shapes[shrd->s_select_lens]->m_n = shrd->s_n;
  }

}

void LensApp::onSliderEvent(ofxDatGuiSliderEvent e){
  cout << e.target->getName() << " : " << e.value << endl;

  if(shrd->s_select_lens < m_lens_shapes.size()){
    if (e.target->getLabel() == "Select Lens"){
      load_lens_parameters((int)e.value);
    }
    // std::string parm_name = e.target->
    change_lens_parameters(e.target->getLabel());
  }

}

void LensApp::onToggleEvent(ofxDatGuiToggleEvent e){
    cout << e.target->getLabel() << " checked = " << e.checked << endl;
    if (e.target->getLabel() == "Draw Construction Lines"){
      shrd->s_show_constr_lines = e.checked;
      //m_lens_shapes[shrd->select_lens]
      for(auto it : m_lens_shapes){
        //    it->print(std::cout);
          it->m_show_constr_lines = shrd->s_show_constr_lines;
      }
    }
    if (e.target->getLabel() == "Draw Rays"){
      shrd->s_draw_rays = e.checked;
      //m_lens_shapes[shrd->select_lens]
      for(auto it : m_lens_shapes){
        //    it->print(std::cout);
          it->m_draw_rays = shrd->s_draw_rays;
      }
    }
    if (e.target->getLabel() == "Draw Normals"){
      shrd->s_draw_normals = e.checked;
      //m_lens_shapes[shrd->select_lens]
      for(auto it : m_lens_shapes){
        //    it->print(std::cout);
          it->m_draw_normals = shrd->s_draw_normals;
      }
    }
    if (e.target->getLabel() == "Draw Focus etc"){
      shrd->s_show_focus_etc = e.checked;
      //m_lens_shapes[shrd->select_lens]
      for(auto it : m_lens_shapes){
        //    it->print(std::cout);
          it->m_draw_focalpoint = shrd->s_show_focus_etc;
      }
    }
  return;
  }


void LensApp::onButtonEvent(ofxDatGuiButtonEvent e){
    cout<<"Buttonpressed  !"<<endl;

    for(auto it : m_lens_shapes){
      //    it->print(std::cout);
        it->update_path();
    }
}


//--------------------------------------------------------------
void LensApp::keyPressed(int key){

}

//--------------------------------------------------------------
void LensApp::keyReleased(int key){

}

//--------------------------------------------------------------
void LensApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void LensApp::mouseDragged(int x, int y, int button){
  // cout << "mouse-dr   x:" << x << " y:" << y << " button:" << button << endl;

}

//--------------------------------------------------------------
void LensApp::mousePressed(int x, int y, int button){
  // cout << "mouse-pr   x:" << x << " y:" << y << " button:" << button << endl;

}

//--------------------------------------------------------------
void LensApp::mouseReleased(int x, int y, int button){
  for(auto it : m_lens_shapes){
    //    it->print(std::cout);
      it->update_path();
      it->m_act_manipulated = false;
  }
}

//--------------------------------------------------------------
void LensApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void LensApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void LensApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void LensApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void LensApp::dragEvent(ofDragInfo dragInfo){

}
