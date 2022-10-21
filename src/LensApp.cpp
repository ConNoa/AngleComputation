#include "LensApp.hpp"



void LensApp::setup(){

    ofBackground(0, 250, 226);

    //
    //
    // path.moveTo(200,200);
    // path.lineTo(400,200);
    // path.lineTo(400,400);
    // path.lineTo(200,400);
    // path.close();
    // path.setStrokeColor(ofColor::blue);
    // path.setFillColor(ofColor::red);
    // path.setFilled(true);
    // path.setStrokeWidth(2);
    //
    //
    //
    // // create a new ofSubPath
    // path2.arc( 300, 300, 100, 100, 0, 180);
    // path2.close();
    // path2.setCircleResolution(720);
    // path2.setStrokeColor(ofColor::blue);
    // path2.setFillColor(ofColor::red);
    // path2.setFilled(true);
    // path2.setStrokeWidth(2);
    //
    //
    // float px = mouseX;
    // float py = mouseY;
    //
    //
    // float scale = ofDist(100, 100, 100, 100);
    //
    // for( float theta = 0; theta < TWO_PI; theta += 0.1)
    // {
    //     float r =  cos(theta * (scale/6)) * scale;
    //     path3.curveTo(100 + r * cos(theta), 200 + r * sin(theta));
    // }
    // path3.setCircleResolution(720);
    // path3.setStrokeColor(ofColor::blue);
    // path3.setFillColor(ofColor::red);
    // path3.setFilled(true);
    // path3.setStrokeWidth(2);
    // px = mouseX;
    // py = mouseY;


//  test_lens = Lens(p_x, p_y, p_z, d_in, r1,  r2,  brchzhl, breite);
test_lens = Lens(600, 600, 0 ,  300,  175, 160, 1.46f,   50);
lens2 = Lens(600, 200, 0 ,  200,  175, 160, 1.46f,   10);


    // test_lens.print();
    test_lens.setup();
    lens2.setup();
    // test_lens.print();



vec3    orig_in{33.0f, 66.0f, 99.0f};
float   dia_in = 150.0f;
float   width_in = 5.0f;
float   r1_in   = 400.0f;
float   r2_in   = 500.0f;
float   n_in    = 1.3456789f;



std::shared_ptr<Shape> new_lens_box = std::make_shared<Lensbox>(orig_in, dia_in, width_in, r1_in, r2_in, n_in);

// tmpcomp.insert(std::pair<std::string, shape_pointer>(box->name(), box));

m_composite= std::make_shared<Composite>("my_Lens_composition");


std::cout<< "This is the new created LensBox: [ "<< endl;
new_lens_box->print(std::cout);
std::cout<< " ]. " <<std::endl;

// m_composite->add(new_lens_box);
m_composite->add(new_lens_box);


std::cout<< "composit added" <<std::endl;
}


void LensApp::update(){


return;
}



void LensApp::draw(){



  test_lens.draw();
  lens2.draw();
  //test_lens.print();

return;
}




//initialize:

//
//
//
// Scene scene;
// std::map<std::string, std::shared_ptr<Shape>> tmpcomp;
//
//
//
//
//
// else if(firstWord == "shape")//##############-Shape
// {
//     ss>>firstWord;
//     std::cout << "Shape: ";
//
//     if(firstWord == "box") //##############-Box
//     {
//         std::cout << "Box\n";
//         std::string boxname;
//         glm::vec3 min;
//         glm::vec3 max;
//         std::string materialname;
//
//         ss >> boxname;
//         ss >> min.x;
//         ss >> min.y;
//         ss >> min.z;
//
//         ss >> max.x;
//         ss >> max.y;
//         ss >> max.z;
//
//         ss >> materialname;
//
//         //Einspeichern
//         std::shared_ptr<Material> material=(scene.m_materials.find(materialname)->second);
//
//         std::shared_ptr<Shape> box = std::make_shared<Box>(boxname, material, min, max);
//         tmpcomp.insert(std::pair<std::string, std::shared_ptr<Shape>>(box->name(), box));
