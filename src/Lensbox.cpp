#include "Lensbox.hpp"

#include <cmath>
#include <catch.hpp>
// #include <limits>
#include <algorithm>

//KONSTRUTOREN----------------------------------------------------------------

  //Default
  Lensbox::Lensbox() :
  Shape {"Lensbox",{}},
  m_min {0.0f, 0.0f, 0.0f},
  m_max {1.0f, 1.0f, 1.0f} {}

  // Custom 1
  Lensbox::Lensbox(vec3 const& min, vec3 const& max) :
  Shape {"Lensbox",{}},
  m_min {min},
  m_max {max} {}

  // Constructor for LensSystem
  Lensbox::Lensbox(vec3 const& orig, float diameter, float width, float r1, float r2, float n) :
  Shape {"Lensbox",{}},
  m_min {0.0f, 0.0f, 0.0f},
  m_max {1.0f, 1.0f, 1.0f},
  m_orig {orig},
  m_diameter {diameter},
  m_width {width},
  m_rot_z {0},
  m_type_r1 {1},
  m_r1 {r1},
  m_type_r2 {1},
  m_r2 {r2},
  m_n {n},
  m_n_air{1.000272f}{}

  // Constructor for LensSystem
  Lensbox::Lensbox(vec3 const& orig, float diameter, float width, int t_r1, float r1, int t_r2, float r2, float n) :
  Shape {"Lensbox",{}},
  m_min {0.0f, 0.0f, 0.0f},
  m_max {1.0f, 1.0f, 1.0f},
  m_orig {orig},
  m_diameter {diameter},
  m_width {width},
  m_rot_z {0},
  m_type_r1 {t_r1},
  m_r1 {r1},
  m_type_r2 {t_r2},
  m_r2 {r2},
  m_n {n},
  m_n_air{1.000272f}{}

  // Custom 3
  Lensbox::Lensbox(std::string const& name, std::shared_ptr<Material> mat, vec3 const& min, vec3 const& max) :
  Shape {name, mat},
  m_min {min},
  m_max {max} {}

  //Destruktor
  Lensbox::~Lensbox()
  {
    std::cout << "Lensbox-Destruction: " << Shape::name()<< std::endl;
  }

//GETTER----------------------------------------------------------------------

  vec3 const& Lensbox::max() const
  {
    return m_max;
  }

  vec3 const& Lensbox::min() const
  {
    return m_min;
  }

//SETTER----------------------------------------------------------------------

  void Lensbox::max(vec3 const& max)
  {
    m_max = max;
  }

  void Lensbox::min(vec3 const& min)
  {
    m_min = min;
  }

//FUNKTIONEN------------------------------------------------------------------

  std::ostream& Lensbox::print(std::ostream& os) const{
    Shape::print(os);

    os << "Minimum: (" << m_min.x << ", "
    << m_min.y << ", "
    << m_min.z << ")" << "\n"

    << "Maximum: (" << m_max.x << ", "
    << m_max.y << ", "
    << m_max.z << ")" << "\n"

    << "Origin: (" << m_orig.x << ", "
    << m_orig.y << ", "
    << m_orig.z << ")" << "\n"

    << "Diameter: (" << m_diameter<< ")" << "\n"

    << "Width: (" << m_width<< ")" << "\n"

    << "R1: (" << m_r1<< ")" << "\n"

    << "R2: (" << m_r2<< ")" << "\n"

    << "Brechungsindex: (" << m_n << ")" << std::endl;

    return os;
  }

  /*Întersect
  ######################################
  Prüft in Hit boxhit.m_hit ob der Strahl
  die Lensbox trifft(bool).
  In welcher Entfernung, boxhit.m_distance
  wird geschnitten?
  Übergabe per Pointer der Lensbox in
  boxhit.m_shape.
  Der Śchnittpunkt liegt in
  boxhit.m_point.

  Grund-Verfahren-Source:
  http://www.scratchapixel.com/
  lessons/3d-basic-rendering/
  minimal-ray-tracer-rendering
  -simple-shapes/ray-box-intersection

  Hit Sphere::intersect(Ray ray) const
    {

      Hit spherehit;

      spherehit.m_hit = intersectRaySphere
        (
          ray.m_orig, ray.m_direction,
          m_center, m_radius,
          spherehit.m_point, spherehit.m_normal //Indirekte param.
        );

      if (spherehit.m_hit) //=true ->extra Info
      {
        spherehit.m_distance = distance(ray.m_orig, spherehit.m_point);
        spherehit.m_shape = this;


         if(distance(spherehit.m_point-0.001f*ray.m_direction, m_center) < m_radius)
        {
          spherehit.m_normal = -spherehit.m_normal;
        }

      }

      return spherehit;
    }

   */
  Hit Lensbox::intersect(Ray const &ray_in) const{
    std::cout<< "Lensbox::intersect exec. "<< std::endl;

    Hit l_hit;

    vec3 point0 = ray_in.m_orig;
    vec3 point1 = ray_in.m_orig + normalize(ray_in.m_direction)*100000;

    float m_radius = m_diameter/2;

    vec3 intsctPos1 = vec3{0,0,0};
    vec3 intsctNrml1 = vec3{0,0,0};
    vec3 intsctPos2 = vec3{0,0,0};
    vec3 intsctNrml2 = vec3{0,0,0};

    l_hit.m_hit = intersectLineSphere(point0, point1,	m_center_d1, m_radius,
                                        intsctPos1, intsctNrml1,
                                        intsctPos2, intsctNrml2);

    if(l_hit.m_hit == true) {

      // std::cout<< "Lenshit! with ray_in "<< ray_in.m_orig << std::endl;
      // std::cout << " At Pos 1 :"<< intsctPos1<< std::endl;
      // std::cout << " with Intersection-normal 1 :"<< intsctNrml1<< std::endl;
      // std::cout << " At Pos 2 :"<< intsctPos2<< std::endl;
      // std::cout << " with Intersection-normal 2 :"<< intsctNrml2<< std::endl;

      l_hit.m_hit = intersectLineSphere(point0, point1,	m_center_r1, m_r1,
        intsctPos1, intsctNrml1, intsctPos2, intsctNrml2);

      if(length(m_orig-intsctPos1)<length(m_orig-intsctPos2)){
        l_hit.m_point = intsctPos1;
        l_hit.m_normal = intsctNrml1;
        l_hit.m_distance = length(ray_in.m_orig - intsctPos1);
        l_hit.draw();
      }
      else if(length(m_orig-intsctPos1)>length(m_orig-intsctPos2)){
        l_hit.m_point = intsctPos2;
        l_hit.m_normal = intsctNrml2;
        l_hit.m_distance = length(ray_in.m_orig - intsctPos2);
        l_hit.draw();
      }

    }




    return l_hit;
  }

  void Lensbox::draw() const{
    lens.draw();
    if(m_show_constr_lines == true || m_act_manipulated == true){
      draw_construction();
    }
    return;
  }

  void Lensbox::draw_construction() const {
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

  }

  void Lensbox::update(){

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

    std::cout <<"Die Brechkraft der vorderen Fläche beträgt"<<  m_D1 << std::endl;
    std::cout <<"Brennweite der vorderen Fläche: "<<  1/m_D1 << "/n "<< std::endl;

    return;
  }

  void Lensbox::update_path(){

    lens.clear();

    m_ankat_angle_r1 = compute_lens_angle(m_r1, m_diameter);
    float r1_a1 = -180  - m_ankat_angle_r1;
    float r1_a2 = -180  + m_ankat_angle_r1;

    m_ankat_angle_r2 = compute_lens_angle(m_r2, m_diameter);
    float r2_a1 = -0    - m_ankat_angle_r2;
    float r2_a2 = -0    + m_ankat_angle_r2;


    lens.arc(m_center_r1, m_r1, m_r1 ,r1_a1, r1_a2);
    lens.close();
    lens.arc(m_center_r2, m_r2, m_r2, r2_a1, r2_a2);
    lens.close();

    vec3 pos_lrect = NULLPUNKT+m_orig;     //Position des Rechtecks (dicker Glasteil in der Linse)
    pos_lrect.x = pos_lrect.x-m_width/2;
    pos_lrect.y = pos_lrect.y-m_diameter/2;
    lens.rectangle(pos_lrect.x, pos_lrect.y, m_width, m_diameter);
    lens.setCircleResolution(720);
    lens.setStrokeWidth(1);
    lens.setStrokeColor(ofColor::black);
    lens.setFillColor(ofColor::grey);
    lens.close();
  }

  void Lensbox::scale(float faktor){
    //Skaliere von min ausgehend!
    // vec3 diff=m_max-m_min;
    // m_max=m_min+(diff*faktor);
    //translate(XXX); Damit Zentrum bleibt?
  }

  void Lensbox::translate(vec3 const& vec){
      m_trans_vec = vec;
      //update();
    }

  void Lensbox::rotate(float angle,vec3 const& vec){
    //NOT YET IMPLEMENTED
  }

  float Lensbox::compute_lens_angle(float radius_ , float diameter_lens_){
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
