#include "Plane.hpp"

#include <catch.hpp>
// #include <limits>
#include <algorithm>

//KONSTRUTOREN----------------------------------------------------------------

  //Default
  Plane::Plane() :
  Shape {"Plane",{}}{}

  Plane::Plane(int mat_id) :
  Shape {"Plane", mat_id}{}

  Plane::Plane(std::string const& name, int mat_id) :
  Shape {name, mat_id}{}

  Plane::Plane(vec3 const& orig, vec3 const &direction) :
  Shape {"Plane", 1},
  m_orig{orig},
  m_direction{direction},
  m_draw_rays{true}{}

  Plane::Plane(vec3 const& orig, vec3 const &direction, int mat_id) :
  Shape {"Plane", mat_id},
  m_orig{orig},
  m_direction{direction},
  m_draw_rays{true}{}

  //Destruktor
  Plane::~Plane()
  {
    std::cout << "Plane-Destruction: " << Shape::name()<< std::endl;
  }

//FUNKTIONEN------------------------------------------------------------------

  std::ostream& Plane::print(std::ostream& os) const{
    Shape::print(os);

    os << "Im a Plane."<< "\n"<< "Origin: (" << m_orig.x << ", "
    << m_orig.y << ", "
    << m_orig.z << ")" << "\n"

    << "Direction: (" << m_direction<< ")" << std::endl;

    return os;
  }


  Ray Plane::intersect(Ray &ray_in) const{

        // Ray dummyray
        Ray output_ray;
        Hit hit_in;
        float inter_Dis;

        hit_in.m_hit = intersectRayPlane(ray_in.m_orig, ray_in.m_direction, m_orig, m_direction, inter_Dis);

        hit_in.m_ray = ray_in;
        hit_in.m_distance  =  inter_Dis;


        if(m_draw_rays){      hit_in.draw(ray_in.m_inv_direction); }
        // if(m_draw_normals){   hit_in.draw_normals();               }

        //
        // output_ray = Ray{vec3{hit_in.m_point}, vec3{t2_ray}};
        // std::cout<<"ray out of konkav : m_orig = ["<<hit_in.m_point<<" ]  and t2_ray = ["<<t2_ray<<"]" <<std::endl;
        // std::cout<<"output_ray of konkav : m_orig = ["<<output_ray.m_orig<<" ]  and t2_ray = ["<<output_ray.m_direction<<"]" <<std::endl;

        return output_ray;
      }


    Hit Plane::depthtest(Ray const &ray_in) const{
         Hit hit_in;
         float inter_Dis;
         hit_in.m_hit = intersectRayPlane(ray_in.m_orig, ray_in.m_direction, m_orig, m_direction, inter_Dis);

         hit_in.m_ray = ray_in;
         hit_in.m_distance  =  inter_Dis;

         return hit_in;
       }


  void Plane::draw() const{

    float x_pos = ofGetWidth()-10;
    float y_pos = ofGetHeight()-10;
    vec3 top = vec3{x_pos, 10, 0};
    vec3 bottom = vec3{x_pos,y_pos, 0};

    ofBeginShape();
      ofSetColor(255, 255, 255);
      ofFill();
      ofDrawLine(top, bottom);
    ofEndShape(false);

    return;
  }


  void Plane::update(){

    return;
  }

  void Plane::update_path(){
    std::cout<< "Plane:update_path()" << std::endl;

  }

  void Plane::scale(float faktor){
    //Skaliere von min ausgehend!
  }

  void Plane::translate(vec3 const& vec){
      //update();
    }

  void Plane::rotate(float angle,vec3 const& vec){
    //NOT YET IMPLEMENTED
  }
