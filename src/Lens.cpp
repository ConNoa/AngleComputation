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
        // vec3 ray_v_normale = {1,0,0};
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

  // Hit Lens::depthtest(Ray const &ray_in) const{
  //   Hit input_hit;
  //
  //   vec3 point0 = ray_in.m_orig;
  //   vec3 point1 = ray_in.m_orig + normalize(ray_in.m_direction)*100000;
  //
  //   vec3 intsctPos1 = vec3{0,0,0};
  //   vec3 intsctNrml1 = vec3{0,0,0};
  //   vec3 intsctPos2 = vec3{0,0,0};
  //   vec3 intsctNrml2 = vec3{0,0,0};
  //
  //   // cout << "you are doing depthtest with "<<name()<<" the m_orig is at "<<m_orig<<std::endl;
  //   input_hit.m_hit = intersectLineSphere(point0, point1,	m_orig, m_diameter/2,
  //                                       intsctPos1, intsctNrml1,
  //                                       intsctPos2, intsctNrml2);
  //
  //   input_hit.m_ray = ray_in;
  //   input_hit.m_distance  =  length(m_orig- ray_in.m_orig);
  //
  //   return input_hit;
  //
  //
  // }


  void Lens::scale(float faktor){
    //Skaliere von min ausgehend!
  }

  void Lens::translate(vec3 const& vec){
      //update();
    }

  void Lens::rotate(float angle,vec3 const& vec){
    //NOT YET IMPLEMENTED
  }
