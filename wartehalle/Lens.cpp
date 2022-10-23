#include "Lens.hpp"


Lens::Lens() {
    // std::cout << "Lens is being created" << std::endl;
}
Lens::~Lens() {
    // std::cout << "Lens is being deleted" << std::endl;
}
Lens::Lens(int orig_inx, int orig_iny, int orig_inz, float d_in, float r1_in, float r2_in, float n_in, float breite_in):
        o_x(orig_inx),
        o_y(orig_iny),
        o_z(orig_inz),
        d_(d_in),
        r1_(r1_in),
        r2_(r2_in),
        n_(n_in),
        breite_(breite_in){}

Lens::Lens(vec3 orig_in, float d_in, float r1_in, float r2_in, float n_in, float breite_in):
        orig_(orig_in),
        d_(d_in),
        r1_(r1_in),
        r2_(r2_in),
        n_(n_in),
        breite_(breite_in){std::cout << "Lens vec3 constr." << std::endl;}


void Lens::setup(){

    d_1 = vec3{o_x, o_y, o_z};
    d_2 = vec3{o_x, o_y, o_z};
    orig_ = vec3{o_x, o_y, o_z};
    normal_ = vec3{0, -1, 0};

    d_1.y = d_1.y + d_/2;
    d_2.y = d_2.y + d_/-2;

    r1_d = sqrt((r1_*r1_)-(d_/2)*(d_/2));
    r2_d = -sqrt((r2_*r2_)-(d_/2)*(d_/2));

    f1 = orig_;
    f1.x = orig_.x +r1_d -breite_/2;
    f2 = orig_;
    f2.x = orig_.x +r2_d + breite_/2;

    float r1_a = compute_lens_angle(r1_, d_);
    float r1_a1 = -180 - r1_a;
    float r1_a2 = -180 + r1_a;
    float r2_a = compute_lens_angle(r2_, d_);
    float r2_a1 = -0 - r2_a;
    float r2_a2 = -0 + r2_a;


    // path2.arc( f1, r1_, r1_, arc1, arc2);
    // path2.close();
    // path2.setCircleResolution(720);
    // path2.setStrokeColor(ofColor::blue);
    // path2.setFillColor(ofColor::red);
    // path2.setFilled(false);
    // angi = compute_lens_angle(r2_, d_);
    // arc1 = - angi;
    // arc2 =  angi;
    // path3.arc( f2, r2_, r2_, arc1, arc2);
    // path3.setCircleResolution(720);
    //
    // path3.setStrokeColor(ofColor::red);
    // path3.setFillColor(ofColor::grey);

    //--- new lens
    //lens1.translate(tr_in);

    lens1.arc(f1, r1_, r1_ ,r1_a1, r1_a2);
    lens1.close();
    lens1.arc(f2, r2_, r2_, r2_a1, r2_a2);
    lens1.close();
    vec3 len1_tr = orig_;
    len1_tr.x = len1_tr.x-breite_/2;
    len1_tr.y = len1_tr.y-d_/2;
    lens1.rectangle(len1_tr.x, len1_tr.y, breite_, d_);
    lens1.setCircleResolution(720);
    //   // float l1_r2_a = compute_lens_angle(r2_, d_);
    //   // vec3 F2 = vec3{0,0,0};
    //   // F2.x = F2.x + r2_d;
    //   // lens1.arc(F2, r2_, r2_, -l1_r2_a, l1_r2_a);
    //   //lens1.lineTo(0, d_);

    lens1.setStrokeWidth(1);
    lens1.setStrokeColor(ofColor::black);
    lens1.setFillColor(ofColor::grey);
    //   len1_trans.y = len1_trans.y-400;
    //   lens1.translate(len1_trans);
    lens1.close();



}


void Lens::draw(){
  lens1.draw();
  draw_construction();
  // path2.draw();
  // path3.draw();
}

void Lens::draw_construction(){
  ofBeginShape();

    ofSetColor(0, 0, 255);
    ofFill();
    // ofDrawCircle(o_x, o_y, o_z, 3);
    ofDrawCircle(orig_, 3);
    ofDrawLine(d_1, d_2);

    ofSetCircleResolution(720);
    ofNoFill();
    ofSetColor(0,0, 250);
    ofDrawCircle(f1, 3);
    ofDrawCircle(f1, r1_);
    //ofDrawCircle(f1, r1_);
    ofSetColor(255,0,0);
    ofDrawCircle(f2, 3);
    ofDrawCircle(f2, r2_);
  ofEndShape(false);

}


float Lens::compute_lens_angle(float radius_ , float diameter_lens_){
  float lr_x_atd = sqrt((radius_*radius_)-(diameter_lens_/2)*(diameter_lens_/2));
  vec3 f_ursp = vec3{0,0,0};
  vec3 l_ursp = f_ursp;
  l_ursp.x = radius_;

  vec3 l_edge = f_ursp;
  l_edge.x = lr_x_atd;
  l_edge.y = diameter_lens_/2;
  vec3 refx = vec3{1,0,0};

// DEBUG Couts

  // std::cout << "compute lens"<< std::endl;
  // std::cout << l_ursp<< std::endl;
  // std::cout << l_edge<< std::endl;
  // std::cout<<"--------------"<<std::endl;
        l_ursp = normalize(l_ursp);
        l_edge = normalize(l_edge);
 float  angle_ = orientedAngle(l_ursp, l_edge, refx) * (180.0 / 3.141592653589793238463);
  // std::cout << "compute angle"<< std::endl;
  // std::cout << angle_<< std::endl;

  return angle_;


}


void Lens::print(){

    std::cout<< " Lens parameters:"<< std::endl;
    std::cout<<" orig_oxoyoz"<<std::endl;
    std::cout<<o_x<<std::endl;
    std::cout<<o_y<<std::endl;
    std::cout<<o_z<<std::endl;
    std::cout<<" d"<<std::endl;
    std::cout<<d_<<std::endl;
    std::cout<<"r1"<<std::endl;
    std::cout<<r1_<<std::endl;
    std::cout<<"r2"<<std::endl;
    std::cout<<r2_<<std::endl;
    std::cout<<" n"<<std::endl;
    std::cout<<n_<<std::endl;

    std::cout<<"orig_"<<std::endl;
    std::cout<<orig_<<std::endl;
    std::cout<<"d_1"<<std::endl;
    std::cout<<d_1<<std::endl;
    std::cout<<"d_2"<<std::endl;
    std::cout<<d_2<<std::endl;

}

void Lens::translate(vec3 translation_in){
  orig_ = orig_+translation_in;
  return;
}
