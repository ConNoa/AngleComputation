#include "Lens.hpp"

#include <cmath>
#include <catch.hpp>
// #include <limits>
#include <algorithm>

//KONSTRUTOREN----------------------------------------------------------------

  //Default
  Lens::Lens() :
  Shape {"Lens",{}}{}

  Lens::Lens(int mat_id) :
  Shape {"Lens", mat_id}{}

  Lens::Lens(std::string const& name, int mat_id) :
  Shape {name, mat_id}{}

  Lens::Lens(vec3 const& orig, float diameter, float width, float r1, float r2) :
  Shape {"Lens", 1},
  m_orig{orig},
  m_diameter{diameter},
  m_width{width},
  m_r1{r1},
  m_r2{r2}{}

  Lens::Lens(vec3 const& orig, float diameter, float width, float r1, float r2, int mat_id) :
  Shape {"Lens", mat_id},
  m_orig{orig},
  m_diameter{diameter},
  m_width{width},
  m_r1{r1},
  m_r2{r2}{}

  //Destruktor
  Lens::~Lens()
  {
    std::cout << "Lens-Destruction: " << Lens::name()<< std::endl;
  }

  //FUNKTIONEN------------------------------------------------------------------




  void Lens::update(){

    //relevant?
    //Top and BottomPoints von äußerem Linsendiameter
    m_O_d1 = NULLPUNKT+m_orig;
    m_O_d1.y = m_O_d1.y+ m_diameter/2;

    m_O_d2 = NULLPUNKT+m_orig;
    m_O_d2.y = m_O_d2.y- m_diameter/2;

    m_ankat_r1 =      sqrt((m_r1*m_r1)-(m_diameter/2)*(m_diameter/2));
    //m_ankat_r2 bekommt negatives Vorzeichen, da es den Radius der Gegenüberliegenden Linse darstellt
    m_ankat_r2 = -1*( sqrt((m_r2*m_r2)-(m_diameter/2)*(m_diameter/2)));

    m_center_r1 = NULLPUNKT+m_orig;
    m_center_r1.x = m_center_r1.x + m_ankat_r1 - m_width/2;
    m_center_r2 = NULLPUNKT+m_orig;
    m_center_r2.x = m_center_r2.x + m_ankat_r2 + m_width/2;
    m_center_d1 = m_orig;
    m_center_d1.x = m_center_d1.x-m_width/2;
    m_center_d2 = m_orig;
    m_center_d2.x = m_center_d2.x+m_width/2;
    m_D1 = (m_n-m_n_air)/m_r1;
    m_D2 = (m_n_air-m_n)/m_r2;
    m_center_d0 = m_center_r1;
    m_center_d0.x = m_center_d0.x-m_r1;
    m_center_d3 = m_center_r2;
    m_center_d3.x = m_center_d3.x+m_r2;
    m_f1 = m_center_d0;
    m_f1.x -= 1/m_D1;
    m_f2 = m_center_d3;
    m_f2.x = m_f2.x + 1/m_D2;

    //d_1 = (n_t1-n_i1)/R_1;



    std::cout <<"Die Brechkraft der vorderen Fläche beträgt"<<  m_D1 << std::endl;
    std::cout <<"Brennweite der vorderen Fläche: "<<  1/m_D1 <<  std::endl;

    return;
  }











  std::ostream& Lens::print(std::ostream& os) const{
    Shape::print(os);

    os << "Im a Lens Base class."<< "\n" <<"Origin: (" << m_orig.x << ", "
    << m_orig.y << ", "
    << m_orig.z << ")" << "\n"

    << "Diameter: (" << m_diameter<< ")" << "\n"

    << "Width: (" << m_width<< ")" << "\n"

    << "R1: (" << m_r1<< ")" << "\n"

    << "R2: (" << m_r2<< ")" << "\n"

    << "Brechungsindex ergibt sich aus Material: (" << material() << ")" << std::endl;

    return os;
  }

  void Lens::draw_construction() const {
    // if(mode == 1){
      ofBeginShape();
        ofSetColor(0, 0, 255);
        ofFill();
        // ofDrawCircle(o_x, o_y, o_z, 3);
        ofDrawCircle(NULLPUNKT+m_orig+m_trans_vec, 3);
        ofDrawLine(m_O_d1, m_O_d2);

        ofSetCircleResolution(720);
        ofNoFill();
        ofSetColor(0,0, 250);
        ofDrawCircle(m_center_r1, 3);
        ofDrawCircle(m_center_r1, m_r1);
        //ofDrawCircle(f1, r1_);
        ofSetColor(255,0,0);
        ofDrawCircle(m_center_r2, 3);
        ofDrawCircle(m_center_r2, m_r2);

        ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
        ofSetColor(40,40,40);
        ofDrawRectangle(m_orig, m_width, m_diameter);
        ofSetRectMode(OF_RECTMODE_CORNER); //set rectangle mode to the center
      ofEndShape(false);
      return;
    }

  void Lens::draw_focalpoint() const {
    ofBeginShape();
      ofSetColor(86, 174, 53);
      ofFill();
      // ofDrawCircle(o_x, o_y, o_z, 3);
      ofDrawCircle(m_center_d0, 3);
      ofDrawCircle(m_center_d3, 3);
      ofSetColor(ofColor::white);
      ofDrawCircle(m_f1, 3);
      ofDrawCircle(m_f2, 3);
    ofEndShape();
  }


  float Lens::snells_law(float alpha_i, float n_i, float n_t)const {
    // std::cout<<"--> snells_law() :"<< std::endl;
    float sin_alph_in = sin(alpha_i);
    // std::cout<<"alph_in DEG :"<<  alpha_i* 180.0/3.141592653589793238463 << std::endl;
    // std::cout<<"alph_in  RAD :"<<  alpha_i << std::endl;
    // std::cout<<"sin_alph_in  :"<<  sin_alph_in << std::endl;
    float n_it = n_i/n_t;
    // std::cout<<"\n n_i :"<<  n_i << std::endl;
    // std::cout<<" n_t :"<<  n_t << std::endl;
    // std::cout<<" n_it :"<<  n_it << std::endl;
    float alp_n_it = sin_alph_in*n_it;
    // std::cout<<" alp_n_it :"<< alp_n_it << std::endl;
    float alpha_t = asin(sin(alpha_i)*n_i/n_t);
    // std::cout<<" Angle t out is RAD: "<< alpha_t << std::endl;
    // std::cout<<" Angle t out is DEG : "<< alpha_t * 180.0/3.141592653589793238463 << std::endl;
    // std::cout<<"\n"<<std::endl;
    return alpha_t;
  }

  vec3 Lens::cacl_angle_ray_normal(vec3 const &ray_in, vec3 const &normal_in ) const{

        vec3 angles;
        vec3 mulx_vec = {1,1,0}; //mulx_vec for displaying only one direction of ray
        vec3 muly_vec = {0,1,1};
        vec3 mulz_vec = {1,0,1};
        vec3 sr_x = normalize(ray_in*mulx_vec);
        vec3 sr_y = normalize(ray_in*muly_vec);
        vec3 sr_z = normalize(ray_in*mulz_vec);
        vec3 ray_v_normale = {1,0,0};
        vec3 rotrefy = {1,0,0};
        vec3 rotrefx = {0,0,1};
        vec3 rotrefz = {0,1,0};
        float r_angle_x = orientedAngle(sr_x, normal_in, rotrefx);
        float r_angle_y = orientedAngle(sr_y, normal_in, rotrefy);
        float r_angle_z = orientedAngle(sr_z, normal_in, rotrefz);

        // angles[0] = r_angle_x* 180.0/3.141592653589793238463;
        // angles[1] = r_angle_y* 180.0/3.141592653589793238463;
        // angles[2] = r_angle_z* 180.0/3.141592653589793238463;
        // std::cout<< " Angle rayNormale  x, y, z["<< angles.x <<"   "<< angles.y <<"  "<< angles.z <<"   ]"  <<std::endl;

        angles[0] = r_angle_x;
        angles[1] = r_angle_y; //Ist nicht relevant   -> vec2 daraus machen?
        angles[2] = r_angle_z;
        return  angles;
      }

  float Lens::compute_lens_angle(float radius_ , float diameter_lens_)const{

    float lr_x_atd = sqrt((radius_*radius_)-(diameter_lens_/2)*(diameter_lens_/2));
    vec3 f_ursp = vec3{0,0,0};
    vec3 l_ursp = f_ursp;
    l_ursp.x = radius_;

    vec3 l_edge = f_ursp;
    l_edge.x = lr_x_atd;
    l_edge.y = diameter_lens_/2;
    vec3 refx = vec3{1,0,0};

    l_ursp = normalize(l_ursp);
    l_edge = normalize(l_edge);
    float  angle_ = orientedAngle(l_ursp, l_edge, refx) * (180.0 / 3.141592653589793238463);
    // std::cout << "compute angle"<< std::endl;
    // std::cout << angle_<< std::endl;

    return angle_;
  }


  void Lens::scale(float faktor){
    //Skaliere von min ausgehend!
    // vec3 diff=m_max-m_min;
    // m_max=m_min+(diff*faktor);
    //translate(XXX); Damit Zentrum bleibt?
  }

  void Lens::translate(vec3 const& vec){
      m_trans_vec = vec;
      //update();
    }

  void Lens::rotate(float angle,vec3 const& vec){
    //NOT YET IMPLEMENTED
  }
