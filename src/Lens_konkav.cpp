#include "Lens_konkav.hpp"

#include <cmath>
#include <catch.hpp>
// #include <limits>
#include <algorithm>

//KONSTRUTOREN----------------------------------------------------------------

  // //Default
  Lens_konkav::Lens_konkav() :
  Lens {"Lens_konkav",{}}{}
  //
  // // Custom 1
  // Lens_konkav::Lens_konkav(vec3 const& min, vec3 const& max) :
  // Shape {"Lens_konkav",{}},
  // m_min {min},
  // m_max {max} {}
  //
  // // Constructor for LensSystem
  // Lens_konkav::Lens_konkav(vec3 const& orig, float diameter, float width, float r1, float r2, float n) :
  // Shape {"Lens_konkav",{}},
  // m_min {0.0f, 0.0f, 0.0f},
  // m_max {1.0f, 1.0f, 1.0f},
  // m_orig {orig},
  // m_diameter {diameter},
  // m_width {width},
  // m_rot_z {0},
  // m_type_r1 {1},
  // m_r1 {r1},
  // m_type_r2 {1},
  // m_r2 {r2},
  // m_n {n},
  // m_n_air{1.000272f}{}
  //
  // Constructor for LensSystem
  Lens_konkav::Lens_konkav(vec3 const& orig, float diameter, float width, int t_r1, float r1, int t_r2, float r2, float n) :
  Lens {"Lens_konkav",{}},
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
  Lens_konkav::Lens_konkav(std::string const& name, std::shared_ptr<Material> mat) :
  Lens {name, mat}{}

  //Destruktor
  Lens_konkav::~Lens_konkav()
  {
    std::cout << "Lens_konkav-Destruction: " << Shape::name()<< std::endl;
  }

//FUNKTIONEN------------------------------------------------------------------

  std::ostream& Lens_konkav::print(std::ostream& os) const{
    Shape::print(os);

    os<< "Origin: (" << m_orig.x << ", "
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
  die Lens_konkav trifft(bool).
  In welcher Entfernung, boxhit.m_distance
  wird geschnitten?
  Übergabe per Pointer der Lens_konkav in
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
  Hit Lens_konkav::intersect(Ray &ray_in, int count_hits) const{
    // std::cout << "__________________________________________________________________________"<< std::endl;
    std::cout<<"\n"<< count_hits<< "----------- Hit!  ------------------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<"    ray_in.m_direction: [" << ray_in.m_direction << "]"<<std::endl;

    Hit input_hit;

    vec3 point0 = ray_in.m_orig;
    vec3 point1 = ray_in.m_orig + normalize(ray_in.m_direction)*100000;

    vec3 intsctPos1 = vec3{0,0,0};
    vec3 intsctNrml1 = vec3{0,0,0};
    vec3 intsctPos2 = vec3{0,0,0};
    vec3 intsctNrml2 = vec3{0,0,0};

    input_hit.m_hit = intersectLineSphere(point0, point1,	m_center_d1, m_radius,
                                        intsctPos1, intsctNrml1,
                                        intsctPos2, intsctNrml2);

    if(input_hit.m_hit) {

      input_hit.m_hit = intersectLineSphere(point0, point1,	m_center_r1, m_r1,
        intsctPos1, intsctNrml1, intsctPos2, intsctNrml2);

        std::cout<< "         with ray from: [" << ray_in.m_orig << "]"<<std::endl;
        std::cout<< "At              Pos 1 : ["<< intsctPos1<<"]" << std::endl;
        std::cout <<"Intersection-normal 1 : ["<< intsctNrml1<<"]" <<std::endl;

      if(length(m_orig-intsctPos1)<length(m_orig-intsctPos2)){
        // std::cout << "ifcondition"<<std::endl;

        input_hit.m_point = intsctPos1;
        input_hit.m_normal = intsctNrml1;
        input_hit.m_distance = length(ray_in.m_orig - intsctPos1);
        if(m_draw_rays){      input_hit.draw(ray_in.m_inv_direction); }
        if(m_draw_normals){   input_hit.draw_normals();               }
      }
      else if(length(m_orig-intsctPos1)>length(m_orig-intsctPos2)){
        std::cout << "else if condition --------------------ERROR OCCURS"<<std::endl;

        input_hit.m_point = intsctPos2;
        input_hit.m_normal = intsctNrml2;
        input_hit.m_distance = length(ray_in.m_orig - intsctPos2);
        if(m_draw_rays){      input_hit.draw(ray_in.m_inv_direction); }
        if(m_draw_normals){   input_hit.draw_normals();               }
      }
      else{
        std::cout << "else condition --------------------ERROR OCCURS"<<std::endl;

        return input_hit;
      }
      std::cout<<"i_hit distance  :"<< input_hit.m_distance << std::endl;
      // ray_in.m_distance_hit = input_hit.m_distance;
      vec3 angle_i1 = cacl_angle_ray_normal(-ray_in.m_direction, input_hit.m_normal );
      float angle_t1_x = snells_law(angle_i1.x, m_n_air, m_n);
      //float angle_t_z = snells_law(angle_i1.z, m_n_air, m_n);
      fmat4 rot_mat_i = glm::rotate(angle_t1_x, fvec3{0.0f, 0.0f, 1.0f});
      //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
      // rot_mat_i = glm::rotate(rot_mat_i,angle_t_z, fvec3{0.0f, 1.0f, 0.0f});
      // std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
      fmat3 rot_mat_shrinked = fmat3(rot_mat_i);
      std::cout<< "shrinked  Transform Matrix:  [ "<<rot_mat_shrinked<< " ]."<<std::endl;
      vec3 t1_ray = (input_hit.m_normal*-rot_mat_shrinked);

      vec3 angle_t1 = cacl_angle_ray_normal(t1_ray, -input_hit.m_normal );

      Hit t_hit;

      vec3 intsctPos3 = vec3{0,0,0};
      vec3 intsctNrml3 = vec3{0,0,0};
      vec3 intsctPos4 = vec3{0,0,0};
      vec3 intsctNrml4 = vec3{0,0,0};

      t_hit.m_hit = intersectLineSphere(input_hit.m_point, input_hit.m_point+t1_ray*1000,	m_center_d2, m_radius,
                                          intsctPos3, intsctNrml3,
                                          intsctPos4, intsctNrml4);

      if (t_hit.m_hit){
        t_hit.m_hit = intersectLineSphere(input_hit.m_point, input_hit.m_point+t1_ray*1000,	m_center_r2, m_r2,
          intsctPos3, intsctNrml3, intsctPos4, intsctNrml4);

          std::cout<< "         with ray from: [" << input_hit.m_point << "]"<<std::endl;
          std::cout<< "At              Pos 3 : ["<< intsctPos3<<"]" << std::endl;
          std::cout <<"Intersection-normal 3 : ["<< intsctNrml3<<"]" <<std::endl;
          std::cout<< "At              Pos 4 : ["<< intsctPos4<<"]" << std::endl;
          std::cout <<"Intersection-normal 4 : ["<< intsctNrml4<<"]" <<std::endl;

        if(length(m_center_d3-intsctPos3)<length(m_center_d3-intsctPos4)){
          // std::cout << "ifcondition"<<std::endl;

          t_hit.m_point = intsctPos3;
          t_hit.m_normal = intsctNrml3;
          t_hit.m_distance = length(input_hit.m_point - intsctPos3);
          if(m_draw_rays){      t_hit.draw(-t1_ray); }
          if(m_draw_normals){   t_hit.draw_normals();}
        }
        else if(length(m_center_d3-intsctPos3)>length(m_center_d3-intsctPos4)){
          std::cout << "else if condition --------------------ERROR OCCURS"<<std::endl;

          t_hit.m_point = intsctPos4;
          t_hit.m_normal = intsctNrml4;
          t_hit.m_distance = length(input_hit.m_point - intsctPos4);
          if(m_draw_rays){      t_hit.draw(-t1_ray); }
          if(m_draw_normals){   t_hit.draw_normals();}
        }
        else{
          std::cout << "else condition --------------------ERROR OCCURS"<<std::endl;

          return t_hit;
        }


        vec3 angle_i2 = cacl_angle_ray_normal(-t1_ray, t_hit.m_normal );
        float angle_t1_x = snells_law(angle_i2.x, m_n, m_n_air);
        //float angle_t_z = snells_law(angle_i2.z, m_n_air, m_n);

        fmat4 rot_mat_t = glm::rotate(angle_t1_x, fvec3{0.0f, 0.0f, 1.0f});
        //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;

        fmat3 rot_mat_t_shrnkd = fmat3(rot_mat_t);

        vec3 t2_ray = (rot_mat_t_shrnkd*-t_hit.m_normal);

        vec3 angle_t2 = cacl_angle_ray_normal(t_hit.m_normal, -t2_ray);
        if(m_draw_rays){
        ofBeginShape();
          ofSetLineWidth(1);
          //Drawing Normals
          ofSetColor(227, 227, 80);
          ofDrawLine(t_hit.m_point, t_hit.m_point-t2_ray*1500);
        ofEndShape();
        }
      }
    }
    return input_hit;
  }

  // float Lens_konkav::snells_law(float alpha_i, float n_i, float n_t)const {
  //   // std::cout<<"--> snells_law() :"<< std::endl;
  //   float sin_alph_in = sin(alpha_i);
  //   // std::cout<<"alph_in DEG :"<<  alpha_i* 180.0/3.141592653589793238463 << std::endl;
  //   // std::cout<<"alph_in  RAD :"<<  alpha_i << std::endl;
  //   // std::cout<<"sin_alph_in  :"<<  sin_alph_in << std::endl;
  //   float n_it = n_i/n_t;
  //   // std::cout<<"\n n_i :"<<  n_i << std::endl;
  //   // std::cout<<" n_t :"<<  n_t << std::endl;
  //   // std::cout<<" n_it :"<<  n_it << std::endl;
  //   float alp_n_it = sin_alph_in*n_it;
  //   // std::cout<<" alp_n_it :"<< alp_n_it << std::endl;
  //   float alpha_t = asin(sin(alpha_i)*n_i/n_t);
  //   // std::cout<<" Angle t out is RAD: "<< alpha_t << std::endl;
  //   // std::cout<<" Angle t out is DEG : "<< alpha_t * 180.0/3.141592653589793238463 << std::endl;
  //   // std::cout<<"\n"<<std::endl;
  //   return alpha_t;
  // }
  //
  //
  // vec3 Lens_konkav::cacl_angle_ray_normal(vec3 const &ray_in, vec3 const &normal_in ) const{
  //
  //   vec3 angles;
  //   vec3 mulx_vec = {1,1,0}; //mulx_vec for displaying only one direction of ray
  //   vec3 muly_vec = {0,1,1};
  //   vec3 mulz_vec = {1,0,1};
  //   vec3 sr_x = normalize(ray_in*mulx_vec);
  //   vec3 sr_y = normalize(ray_in*muly_vec);
  //   vec3 sr_z = normalize(ray_in*mulz_vec);
  //   vec3 ray_v_normale = {1,0,0};
  //   vec3 rotrefy = {1,0,0};
  //   vec3 rotrefx = {0,0,1};
  //   vec3 rotrefz = {0,1,0};
  //   float r_angle_x = orientedAngle(sr_x, normal_in, rotrefx);
  //   float r_angle_y = orientedAngle(sr_y, normal_in, rotrefy);
  //   float r_angle_z = orientedAngle(sr_z, normal_in, rotrefz);
  //
  //   // angles[0] = r_angle_x* 180.0/3.141592653589793238463;
  //   // angles[1] = r_angle_y* 180.0/3.141592653589793238463;
  //   // angles[2] = r_angle_z* 180.0/3.141592653589793238463;
  //   // std::cout<< " Angle rayNormale  x, y, z["<< angles.x <<"   "<< angles.y <<"  "<< angles.z <<"   ]"  <<std::endl;
  //
  //   angles[0] = r_angle_x;
  //   angles[1] = r_angle_y;
  //   angles[2] = r_angle_z;
  //   return  angles;
  // }
  //

  void Lens_konkav::draw() const{
    lens.draw();
    if(m_show_constr_lines||m_act_manipulated){ draw_construction();}
    if(m_draw_focalpoint){ draw_focalpoint();}
    return;
  }

//   void Lens_konkav::draw_construction() const {
//       ofBeginShape();
//         ofSetColor(0, 0, 255);
//         ofFill();
//         // ofDrawCircle(o_x, o_y, o_z, 3);
//         ofDrawCircle(NULLPUNKT+m_orig+m_trans_vec, 3);
//         ofDrawLine(m_O_d1, m_O_d2);
//
//         ofSetCircleResolution(720);
//         ofNoFill();
//         ofSetColor(0,0, 250);
//         ofDrawCircle(m_center_r1, 3);
//         ofDrawCircle(m_center_r1, m_r1);
//         //ofDrawCircle(f1, r1_);
//         ofSetColor(255,0,0);
//         ofDrawCircle(m_center_r2, 3);
//         ofDrawCircle(m_center_r2, m_r2);
//
//         ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
//         ofSetColor(40,40,40);
//         ofDrawRectangle(m_orig, m_width, m_diameter);
//         ofSetRectMode(OF_RECTMODE_CORNER); //set rectangle mode to the center
//       ofEndShape(false);
//       return;
// }

  // void Lens_konkav::draw_focalpoint() const {
  //   ofBeginShape();
  //     ofSetColor(86, 174, 53);
  //     ofFill();
  //     // ofDrawCircle(o_x, o_y, o_z, 3);
  //     ofDrawCircle(m_center_d0, 3);
  //     ofDrawCircle(m_center_d3, 3);
  //     ofSetColor(ofColor::white);
  //     ofDrawCircle(m_f1, 3);
  //     ofDrawCircle(m_f2, 3);
  //   ofEndShape();
  // }

  void Lens_konkav::update(){

    m_radius = m_diameter/2;

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

  void Lens_konkav::update_path(){

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
  //
  //
  //
  // float Lens_konkav::compute_lens_angle(float radius_ , float diameter_lens_){
  //   float lr_x_atd = sqrt((radius_*radius_)-(diameter_lens_/2)*(diameter_lens_/2));
  //   vec3 f_ursp = vec3{0,0,0};
  //   vec3 l_ursp = f_ursp;
  //   l_ursp.x = radius_;
  //
  //   vec3 l_edge = f_ursp;
  //   l_edge.x = lr_x_atd;
  //   l_edge.y = diameter_lens_/2;
  //   vec3 refx = vec3{1,0,0};
  //
  //   l_ursp = normalize(l_ursp);
  //   l_edge = normalize(l_edge);
  //   float  angle_ = orientedAngle(l_ursp, l_edge, refx) * (180.0 / 3.141592653589793238463);
  //   // std::cout << "compute angle"<< std::endl;
  //   // std::cout << angle_<< std::endl;
  //
  //   return angle_;
  // }
  //
