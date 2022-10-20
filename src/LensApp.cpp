#include "LensApp.hpp"



void LensApp::setup(){

    ofBackground(0, 250, 226);



    path.moveTo(200,200);
    path.lineTo(400,200);
    path.lineTo(400,400);
    path.lineTo(200,400);
    path.close();
    path.setStrokeColor(ofColor::blue);
    path.setFillColor(ofColor::red);
    path.setFilled(true);
    path.setStrokeWidth(2);



    // create a new ofSubPath
    path2.arc( 300, 300, 100, 100, 0, 180);
    path2.close();
    path2.setCircleResolution(720);
    path2.setStrokeColor(ofColor::blue);
    path2.setFillColor(ofColor::red);
    path2.setFilled(true);
    path2.setStrokeWidth(2);


    float px = mouseX;
    float py = mouseY;


    float scale = ofDist(100, 100, 100, 100);

    for( float theta = 0; theta < TWO_PI; theta += 0.1)
    {
        float r =  cos(theta * (scale/6)) * scale;
        path3.curveTo(100 + r * cos(theta), 200 + r * sin(theta));
    }
    path3.setCircleResolution(720);
    path3.setStrokeColor(ofColor::blue);
    path3.setFillColor(ofColor::red);
    path3.setFilled(true);
    path3.setStrokeWidth(2);
    px = mouseX;
    py = mouseY;


//  test_lens = Lens(p_x, p_y, p_z, d_in, r1,  r2,  brchzhl, breite);
test_lens = Lens(600, 600, 0 ,  300,  175, 160, 1.46f,   50);
lens2 = Lens(600, 200, 0 ,  200,  175, 160, 1.46f,   50);


    test_lens.print();
    test_lens.setup();
    lens2.setup();
    test_lens.print();

//    test_lens.setup();




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
