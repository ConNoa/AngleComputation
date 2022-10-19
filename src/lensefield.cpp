#include "lensefield.hpp"



Lensefield::Lensefield() {
    std::cout << "Lensefield is being created" << std::endl;
}
Lensefield::~Lensefield() {
    std::cout << "Lensefield is being deleted" << std::endl;
}

void Lensefield::setup(){


return;

}


void Lensefield::draw(){
  ofPushMatrix();
  ofBeginShape();
    ofFill();
    ofSetColor(col_bg);
//    ofDrawBox(pos, dim[0],dim[1], dim[2]);
  ofEndShape();
  ofPopMatrix();

  return;
}
