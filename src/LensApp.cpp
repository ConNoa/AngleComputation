#include "LensApp.hpp"



void LensApp::setup(){

    ofBackground(0, 250, 226);


    vec3    orig_in{500.0f, 500.0f, 0.0f};
    float   dia_in = 350.0f;
    float   width_in = 250.0f;
    float   r1_in   =  200.0f;
    float   r2_in   = 200.0f;
    float   n_in    = 1.3456789f;



    std::shared_ptr<Shape> new_lens_box = std::make_shared<Lensbox>(orig_in, dia_in, width_in, r1_in, r2_in, n_in);
    std::cout<< "This is the new created LensBox: [ "<< endl;
    new_lens_box->print(std::cout);
    std::cout<< " ]. " <<std::endl;


    m_composite= std::make_shared<Composite>("my_Lens_composition");
    m_composite->add(new_lens_box);
    std::cout<< "Composite added" <<std::endl;

    vec3    movevec{400.0f, 000.0f, 0.0f};
    new_lens_box->translate(movevec);


    m_lens_shapes.push_back(new_lens_box);

    std::cout<< "Shape added to Vector of Lensshapes" <<std::endl;


    for(auto it : m_lens_shapes){
      //    it->print(std::cout);
         it->update();
    }

}


void LensApp::update(){

  return;
}



void LensApp::draw(){

  for(auto it : m_lens_shapes){
    //    it->print(std::cout);
       it->draw();
  }

  return;
}
