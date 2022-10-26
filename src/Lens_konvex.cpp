#include "Lens_konvex.hpp"

#include <catch.hpp>
// #include <limits>
#include <algorithm>

//KONSTRUTOREN----------------------------------------------------------------

  //Default
  Lens_konvex::Lens_konvex() :
  Lens {"Lens_konvex",{}}{}

  Lens_konvex::Lens_konvex(int mat_id) :
  Lens {"Lens_konvex", mat_id}{}

  Lens_konvex::Lens_konvex(std::string const& name, int mat_id) :
  Lens {name, mat_id}{}

  Lens_konvex::Lens_konvex(vec3 const& orig, float diameter, float width, float r1, float r2) :
  Lens {"Lens_konvex", 1},
  m_orig{orig},
  m_diameter{diameter},
  m_width{width},
  m_r1{r1},
  m_r2{r2}{}

  Lens_konvex::Lens_konvex(vec3 const& orig, float diameter, float width, float r1, float r2, int mat_id) :
  Lens {"Lens_konvex", mat_id},
  m_orig{orig},
  m_diameter{diameter},
  m_width{width},
  m_r1{r1},
  m_r2{r2}{}

  //Destruktor
  Lens_konvex::~Lens_konvex()
  {
    std::cout << "Lens_konvex-Destruction: " << Lens::name()<< std::endl;
  }

//FUNKTIONEN------------------------------------------------------------------


  std::ostream& Lens_konvex::print(std::ostream& os) const{
    Shape::print(os);

    os << "Im a Lens_konvex class."<< "\n"<< "Origin: (" << m_orig.x << ", "
    << m_orig.y << ", "
    << m_orig.z << ")" << "\n"

    << "Diameter: (" << m_diameter<< ")" << "\n"

    << "Width: (" << m_width<< ")" << "\n"

    << "R1: (" << m_r1<< ")" << "\n"

    << "R2: (" << m_r2<< ")" << "\n"

    << "Brechungsindex: (" << material()->n << ") ";

    return os;
  }

  Hit Lens_konvex::intersect(Ray &ray_in, int count_hits) const{

    // std::cout << "__________________________________________________________________________"<< std::endl;

    Hit input_hit;

    vec3 point0 = ray_in.m_orig;
    vec3 point1 = ray_in.m_orig + normalize(ray_in.m_direction)*100000;

    vec3 intsctPos1 = vec3{0,0,0};
    vec3 intsctNrml1 = vec3{0,0,0};
    vec3 intsctPos2 = vec3{0,0,0};
    vec3 intsctNrml2 = vec3{0,0,0};

    input_hit.m_hit = intersectLineSphere(point0, point1,	m_center_d1, m_diameter/2,
                                        intsctPos1, intsctNrml1,
                                        intsctPos2, intsctNrml2);

    if(input_hit.m_hit) {

      input_hit.m_hit = intersectLineSphere(point0, point1,	m_center_r1, m_r1,
        intsctPos1, intsctNrml1, intsctPos2, intsctNrml2);

        input_hit.m_ray = ray_in;
      if(length(m_orig-intsctPos1)<length(m_orig-intsctPos2)){
        // std::cout << "ifcondition"<<std::endl;
        input_hit.m_point = intsctPos1;
        input_hit.m_normal = intsctNrml1;
        input_hit.m_distance = length(ray_in.m_orig - intsctPos1);
      }
      else if(length(m_orig-intsctPos1)>length(m_orig-intsctPos2)){
        std::cout << "else if condition --------------------ERROR OCCURS"<<std::endl;
        input_hit.m_point = intsctPos2;
        input_hit.m_normal = intsctNrml2;
        input_hit.m_distance = length(ray_in.m_orig - intsctPos2);
      }
      else{
        std::cout << "else condition -----------------------ERROR OCCURS"<<std::endl;
        return input_hit;
      }

      // input_hit.Hit_print(count_hits);

      if(m_draw_rays){      input_hit.draw(ray_in.m_inv_direction); }
      if(m_draw_normals){   input_hit.draw_normals();               }

      vec3 angle_i1 = cacl_angle_ray_normal(-ray_in.m_direction, input_hit.m_normal );
      float angle_t1_x = snells_law(angle_i1.x, m_n_air, material()->n);
      //float angle_t_z = snells_law(angle_i1.z, m_n_air, m_n);
      fmat4 rot_mat_i = glm::rotate(angle_t1_x, fvec3{0.0f, 0.0f, 1.0f});
      //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
      // rot_mat_i = glm::rotate(rot_mat_i,angle_t_z, fvec3{0.0f, 1.0f, 0.0f});
      // std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
      fmat3 rot_mat_shrinked = fmat3(rot_mat_i);
      // std::cout<< "shrinked  Transform Matrix:  [ "<<rot_mat_shrinked<< " ]."<<std::endl;
      vec3 t1_ray = (input_hit.m_normal*-rot_mat_shrinked);

      vec3 angle_t1 = cacl_angle_ray_normal(t1_ray, -input_hit.m_normal );

      Ray t_ray = Ray{input_hit.m_point, t1_ray, ray_in.m_color};
      Hit t_hit;

      vec3 intsctPos3 = vec3{0,0,0};
      vec3 intsctNrml3 = vec3{0,0,0};
      vec3 intsctPos4 = vec3{0,0,0};
      vec3 intsctNrml4 = vec3{0,0,0};

      t_hit.m_hit = intersectLineSphere(input_hit.m_point, input_hit.m_point+t1_ray*1000,	m_center_d2, m_diameter/2,
                                          intsctPos3, intsctNrml3,
                                          intsctPos4, intsctNrml4);

      // t_hit.m_ray = ray_in;
      t_hit.m_ray = t_ray;
      if (t_hit.m_hit){
        t_hit.m_hit = intersectLineSphere(input_hit.m_point, input_hit.m_point+t1_ray*1000,	m_center_r2, m_r2,
          intsctPos3, intsctNrml3, intsctPos4, intsctNrml4);

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
        float angle_t1_x = snells_law(angle_i2.x,  material()->n, m_n_air);
        //float angle_t_z = snells_law(angle_i2.z, m_n_air, m_n);

        fmat4 rot_mat_t = glm::rotate(angle_t1_x, fvec3{0.0f, 0.0f, 1.0f});
        //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;

        fmat3 rot_mat_t_shrnkd = fmat3(rot_mat_t);

        vec3 t2_ray = (rot_mat_t_shrnkd*-t_hit.m_normal);

        vec3 angle_t2 = cacl_angle_ray_normal(t_hit.m_normal, -t2_ray);
        if(m_draw_rays){
        ofBeginShape();
          ofSetLineWidth(1);
          ofSetColor(t_hit.m_ray.m_color);
          ofDrawLine(t_hit.m_point, t_hit.m_point-t2_ray*1500);
        ofEndShape();
        }
      }
    }
    return input_hit;

    // // std::cout << "__________________________________________________________________________"<< std::endl;
    //
    // Hit input_hit;
    //
    // vec3 point0 = ray_in.m_orig;
    // vec3 point1 = ray_in.m_orig + normalize(ray_in.m_direction)*100000;
    //
    // vec3 intsctPos1 = vec3{0,0,0};
    // vec3 intsctNrml1 = vec3{0,0,0};
    // vec3 intsctPos2 = vec3{0,0,0};
    // vec3 intsctNrml2 = vec3{0,0,0};
    //
    // input_hit.m_hit = intersectLineSphere(point0, point1,	m_center_d1, m_diameter/2,
    //                                     intsctPos1, intsctNrml1,
    //                                     intsctPos2, intsctNrml2);
    //
    // if(input_hit.m_hit) {
    //
    //   input_hit.m_hit = intersectLineSphere(point0, point1,	m_center_r1, m_r1,
    //     intsctPos1, intsctNrml1, intsctPos2, intsctNrml2);
    //
    //     input_hit.m_ray = ray_in;
    //   if(length(m_orig-intsctPos1)<length(m_orig-intsctPos2)){
    //     // std::cout << "ifcondition"<<std::endl;
    //     input_hit.m_point = intsctPos1;
    //     input_hit.m_normal = intsctNrml1;
    //     input_hit.m_distance = length(ray_in.m_orig - intsctPos1);
    //   }
    //   else if(length(m_orig-intsctPos1)>length(m_orig-intsctPos2)){
    //     std::cout << "else if condition --------------------ERROR OCCURS"<<std::endl;
    //     input_hit.m_point = intsctPos2;
    //     input_hit.m_normal = intsctNrml2;
    //     input_hit.m_distance = length(ray_in.m_orig - intsctPos2);
    //   }
    //   else{
    //     std::cout << "else condition -----------------------ERROR OCCURS"<<std::endl;
    //     return input_hit;
    //   }
    //
    //   // input_hit.Hit_print(count_hits);
    //
    //   if(m_draw_rays){      input_hit.draw(ray_in.m_inv_direction); }
    //   if(m_draw_normals){   input_hit.draw_normals();               }
    //
    //   vec3 angle_i1 = cacl_angle_ray_normal(-ray_in.m_direction, input_hit.m_normal );
    //   float angle_t1_x = snells_law(angle_i1.x, m_n_air, material()->n);
    //   //float angle_t_z = snells_law(angle_i1.z, m_n_air, m_n);
    //   fmat4 rot_mat_i = glm::rotate(angle_t1_x, fvec3{0.0f, 0.0f, 1.0f});
    //   //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
    //   // rot_mat_i = glm::rotate(rot_mat_i,angle_t_z, fvec3{0.0f, 1.0f, 0.0f});
    //   // std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
    //   fmat3 rot_mat_shrinked = fmat3(rot_mat_i);
    //   // std::cout<< "shrinked  Transform Matrix:  [ "<<rot_mat_shrinked<< " ]."<<std::endl;
    //   vec3 t1_ray = (input_hit.m_normal*-rot_mat_shrinked);
    //
    //   vec3 angle_t1 = cacl_angle_ray_normal(t1_ray, -input_hit.m_normal );
    //
    //   Hit t_hit;
    //
    //   vec3 intsctPos3 = vec3{0,0,0};
    //   vec3 intsctNrml3 = vec3{0,0,0};
    //   vec3 intsctPos4 = vec3{0,0,0};
    //   vec3 intsctNrml4 = vec3{0,0,0};
    //
    //   t_hit.m_hit = intersectLineSphere(input_hit.m_point, input_hit.m_point+t1_ray*1000,	m_center_d2, m_diameter/2,
    //                                       intsctPos3, intsctNrml3,
    //                                       intsctPos4, intsctNrml4);
    //
    //   t_hit.m_ray = ray_in;
    //   if (t_hit.m_hit){
    //     t_hit.m_hit = intersectLineSphere(input_hit.m_point, input_hit.m_point+t1_ray*1000,	m_center_r2, m_r2,
    //       intsctPos3, intsctNrml3, intsctPos4, intsctNrml4);
    //
    //     if(length(m_center_d3-intsctPos3)<length(m_center_d3-intsctPos4)){
    //       // std::cout << "ifcondition"<<std::endl;
    //
    //       t_hit.m_point = intsctPos3;
    //       t_hit.m_normal = intsctNrml3;
    //       t_hit.m_distance = length(input_hit.m_point - intsctPos3);
    //       if(m_draw_rays){      t_hit.draw(-t1_ray); }
    //       if(m_draw_normals){   t_hit.draw_normals();}
    //     }
    //     else if(length(m_center_d3-intsctPos3)>length(m_center_d3-intsctPos4)){
    //       std::cout << "else if condition --------------------ERROR OCCURS"<<std::endl;
    //
    //       t_hit.m_point = intsctPos4;
    //       t_hit.m_normal = intsctNrml4;
    //       t_hit.m_distance = length(input_hit.m_point - intsctPos4);
    //       if(m_draw_rays){      t_hit.draw(-t1_ray); }
    //       if(m_draw_normals){   t_hit.draw_normals();}
    //     }
    //     else{
    //       std::cout << "else condition --------------------ERROR OCCURS"<<std::endl;
    //
    //       return t_hit;
    //     }
    //
    //
    //     vec3 angle_i2 = cacl_angle_ray_normal(-t1_ray, t_hit.m_normal );
    //     float angle_t1_x = snells_law(angle_i2.x,  material()->n, m_n_air);
    //     //float angle_t_z = snells_law(angle_i2.z, m_n_air, m_n);
    //
    //     fmat4 rot_mat_t = glm::rotate(angle_t1_x, fvec3{0.0f, 0.0f, 1.0f});
    //     //std::cout<< "Transform Matrix:  [ "<<rot_mat_i<< " ]."<<std::endl;
    //
    //     fmat3 rot_mat_t_shrnkd = fmat3(rot_mat_t);
    //
    //     vec3 t2_ray = (rot_mat_t_shrnkd*-t_hit.m_normal);
    //
    //     vec3 angle_t2 = cacl_angle_ray_normal(t_hit.m_normal, -t2_ray);
    //     if(m_draw_rays){
    //     ofBeginShape();
    //       ofSetLineWidth(1);
    //       //Drawing Normals
    //       ofSetColor(227, 227, 80);
    //       ofDrawLine(t_hit.m_point, t_hit.m_point-t2_ray*1500);
    //     ofEndShape();
    //     }
    //   }
    // }
    // return input_hit;
  }

  void Lens_konvex::update(){

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

  //
  //
  // std::cout <<"Die Brechkraft der vorderen Fläche beträgt"<<  m_D1 << std::endl;
  // std::cout <<"Brennweite der vorderen Fläche: "<<  1/m_D1 <<  std::endl;

  return;
}

  void Lens_konvex::update_path(){
    std::cout<< "Lens_konvex:update_path()" << std::endl;

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

  void Lens_konvex::draw() const{
    lens.draw();
    if(m_show_constr_lines||m_act_manipulated){ draw_construction();}
    if(m_draw_focalpoint){ draw_focalpoint();}
    return;
  }

  void Lens_konvex::draw_construction() const {
  // if(mode == 1){
    ofBeginShape();
      ofSetColor(0, 0, 255);
      ofFill();
      // ofDrawCircle(o_x, o_y, o_z, 3);
      ofDrawCircle(NULLPUNKT+m_orig, 3);
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

  void Lens_konvex::draw_focalpoint() const {
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
