#include "LensApp.hpp"

void LensApp::setup(){

    ofBackground(75, 75, 75);

    setup_gui();

    //
    // m_composite= std::make_shared<Composite>("my_Lens_composition");
    // m_composite->add(new_lens_box);
    // std::cout<< "Composite added" <<std::endl;
    //
    // vec3    movevec{0.0f, 000.0f, 0.0f};
    // new_lens_box->translate(movevec);
    //


    setup_lens();
    load_lens_parameters(shrd->select_lens);
    for(auto it : m_lens_shapes){it->update_path();}

    m_mems.setup();



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
  m_mems.draw();

std::cout <<"---------------------------------------------"<< std::endl;
  for(auto lens_it : m_lens_shapes){
    for(auto ray_it : m_mems.m_mems_rays){
      Hit temp_hit;
      temp_hit = lens_it->intersect(ray_it);
    }
  }
  return;
}

void LensApp::setup_gui(){
    //-------------GÚI INTERFACE------------------------------------------------
    shrd->s_orig_x.set("s_orig_x", 590, 0, 1000);
    shrd->s_orig_y.set("s_orig_y", 684, 500, 900);
    shrd->s_orig_z.set("s_orig_z", 0, 0, 0);
    shrd->s_rot_z.set("s_rot_z", 0, 0, 360);

    shrd->s_diameter.set("s_diameter", 182.66, 1, 600);
    shrd->s_width.set("s_width", 0, 0, 25);
    shrd->s_type_r1.set("s_type_r1", 1, 1, 3);
    shrd->s_r1.set("s_r1", 98.36, 0, 2000);
    shrd->s_type_r2.set("s_type_r2", 1, 1, 3);
    shrd->s_r2.set("s_r2", 94.36, 0, 2000);
    shrd->s_n.set("s_n", 1.3456789f, 1, 3);
    shrd->s_show_constr_lines.set(false);
    shrd->show_rays.set(false);
    shrd->show_focus_etc.set(false);
    shrd->select_lens.set("Select Lens", 0, 0, 5);
    shrd->store_lens.set(false);


    shrd->lens_attr_gui = new ofxDatGui();
    shrd->lens_attr_gui->addLabel("Lens Parameters");
    shrd->lens_attr_gui->addButton("Save Lenssettings");

    shrd->lens_attr_gui->addSlider(shrd-> s_orig_x);
    shrd->lens_attr_gui->addSlider(shrd-> s_orig_y);
    //shrd->lens_attr_gui->addSlider(shrd-> s_orig_z);
    shrd->lens_attr_gui->addSlider(shrd-> s_rot_z);

    shrd->lens_attr_gui->addSlider(shrd-> s_diameter);
    shrd->lens_attr_gui->addSlider(shrd-> s_width);
    shrd->lens_attr_gui->addSlider(shrd-> s_type_r1);
    shrd->lens_attr_gui->addSlider(shrd-> s_r1);
    shrd->lens_attr_gui->addSlider(shrd-> s_type_r2);
    shrd->lens_attr_gui->addSlider(shrd-> s_r2);
    shrd->lens_attr_gui->addSlider(shrd-> s_n);

    shrd->lens_attr_gui->addToggle("Show Construction Lines", shrd->s_show_constr_lines);
    shrd->lens_attr_gui->addToggle("Show Normals", shrd->show_rays);
    shrd->lens_attr_gui->addToggle("Show Focus etc", shrd->show_focus_etc);
    shrd->lens_attr_gui->addSlider(shrd-> select_lens);
    shrd->lens_attr_gui->addToggle("Store Lens", shrd->store_lens);

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

    shrd->s_orig_x = m_lens_shapes[shrd->select_lens]->m_orig.x;
    shrd->s_orig_y = m_lens_shapes[shrd->select_lens]->m_orig.y;
    shrd->s_orig_z = m_lens_shapes[shrd->select_lens]->m_orig.z;
    shrd->s_rot_z = m_lens_shapes[shrd->select_lens]->m_rot_z;
    shrd->s_diameter = m_lens_shapes[shrd->select_lens]->m_diameter;
    shrd->s_width = m_lens_shapes[shrd->select_lens]->m_width;
    shrd->s_type_r1 = m_lens_shapes[shrd->select_lens]->m_type_r1;
    shrd->s_r1 = m_lens_shapes[shrd->select_lens]->m_r1;
    shrd->s_type_r2 = m_lens_shapes[shrd->select_lens]->m_type_r2;
    shrd->s_r2 = m_lens_shapes[shrd->select_lens]->m_r2;
    shrd->s_n = m_lens_shapes[shrd->select_lens]->m_n;
    shrd->s_show_constr_lines = m_lens_shapes[shrd->select_lens]->m_show_constr_lines;
    return;

}

void LensApp::change_lens_parameters(std::string label_in){

  m_lens_shapes[shrd->select_lens]->m_act_manipulated = true;

  if (label_in == "s_orig_x"){
    m_lens_shapes[shrd->select_lens]->m_orig.x = shrd->s_orig_x;
  }
  if (label_in == "s_orig_y"){
    m_lens_shapes[shrd->select_lens]->m_orig.y = shrd->s_orig_y;
  }
  if (label_in == "s_orig_z"){
    m_lens_shapes[shrd->select_lens]->m_orig.z = shrd->s_orig_z;
  }
  if (label_in == "s_rot_z"){
      m_lens_shapes[shrd->select_lens]->m_rot_z = shrd->s_rot_z;
  }
  if (label_in == "s_diameter"){
      m_lens_shapes[shrd->select_lens]->m_diameter = shrd->s_diameter;
  }
  if (label_in == "s_width"){
      m_lens_shapes[shrd->select_lens]->m_width = shrd->s_width;
  }
  if (label_in == "s_type_r1"){
      m_lens_shapes[shrd->select_lens]->m_type_r1 = shrd->s_type_r1;
  }
  if (label_in == "s_r1"){
      m_lens_shapes[shrd->select_lens]->m_r1 = shrd->s_r1;
  }
  if (label_in == "s_type_r2"){
      m_lens_shapes[shrd->select_lens]->m_type_r2 = shrd->s_type_r2;
  }
  if (label_in == "s_r2"){
      m_lens_shapes[shrd->select_lens]->m_r2 = shrd->s_r2;
  }
  if (label_in == "s_n"){
      m_lens_shapes[shrd->select_lens]->m_n = shrd->s_n;
  }

}

void LensApp::onSliderEvent(ofxDatGuiSliderEvent e){
  cout << e.target->getName() << " : " << e.value << endl;

  if(shrd->select_lens < m_lens_shapes.size()){
    if (e.target->getLabel() == "Select Lens"){
      load_lens_parameters((int)e.value);
    }
    // std::string parm_name = e.target->
    change_lens_parameters(e.target->getLabel());
  }

}

void LensApp::onToggleEvent(ofxDatGuiToggleEvent e){
    cout << e.target->getLabel() << " checked = " << e.checked << endl;
    if (e.target->getLabel() == "Show Construction Lines"){
      shrd->s_show_constr_lines = e.checked;
      //m_lens_shapes[shrd->select_lens]
      for(auto it : m_lens_shapes){
        //    it->print(std::cout);
          it->m_show_constr_lines = shrd->s_show_constr_lines;
      }
    }
    if (e.target->getLabel() == "Show Normals"){
      shrd->show_rays = e.checked;
      //m_lens_shapes[shrd->select_lens]
      for(auto it : m_lens_shapes){
        //    it->print(std::cout);
          it->m_draw_normals = shrd->show_rays;
      }
    }



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
