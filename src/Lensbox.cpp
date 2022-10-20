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
  Lensbox::Lensbox(glm::vec3 const& min, glm::vec3 const& max) :
  Shape {"Lensbox",{}},
  m_min {min},
  m_max {max} {}

  // Constructor for LensSystem
  Lensbox::Lensbox(glm::vec3 const& orig, float diameter, float width, float r1, float r2, float n) :
  Shape {"Lensbox",{}},
  m_min {0.0f, 0.0f, 0.0f},
  m_max {1.0f, 1.0f, 1.0f},
  m_orig {orig},
  m_diameter {diameter},
  m_width {width},
  m_r1 {r1},
  m_r2 {r2},
  m_n {n}{}


  // Custom 3
  Lensbox::Lensbox(std::string const& name, std::shared_ptr<Material> mat, glm::vec3 const& min, glm::vec3 const& max) :
  Shape {name, mat},
  m_min {min},
  m_max {max} {}

  //Destruktor
  Lensbox::~Lensbox()
  {
    std::cout << "Lensbox-Destruction: " << Shape::name()<< std::endl;
  }

//GETTER----------------------------------------------------------------------

  glm::vec3 const& Lensbox::max() const
  {
    return m_max;
  }

  glm::vec3 const& Lensbox::min() const
  {
    return m_min;
  }

//SETTER----------------------------------------------------------------------

  void Lensbox::max(glm::vec3 const& max)
  {
    m_max = max;
  }

  void Lensbox::min(glm::vec3 const& min)
  {
    m_min = min;
  }

//FUNKTIONEN------------------------------------------------------------------

  std::ostream& Lensbox::print(std::ostream& os) const
  {
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
   */
  Hit Lensbox::intersect(Ray ray) const
  {
    Hit boxhit;

    double t1 = (m_min.x - ray.m_origin.x)*ray.m_inv_direction.x;
    double t2 = (m_max.x - ray.m_origin.x)*ray.m_inv_direction.x;
    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);

    t1 = (m_min.y - ray.m_origin.y)*ray.m_inv_direction.y;
    t2 = (m_max.y - ray.m_origin.y)*ray.m_inv_direction.y;
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    t1 = (m_min.z - ray.m_origin.z)*ray.m_inv_direction.z;
    t2 = (m_max.z - ray.m_origin.z)*ray.m_inv_direction.z;
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    if (tmax > std::max(0.0, tmin)) //Hit?
    {
        boxhit.m_hit = true;
        boxhit.m_distance = sqrt(tmin*tmin*(
                                ray.m_direction.x*ray.m_direction.x +
                                ray.m_direction.y*ray.m_direction.y +
                                ray.m_direction.z*ray.m_direction.z));

        boxhit.m_shape = this;

        boxhit.m_point =
        glm::vec3{tmin*ray.m_direction.x, tmin*ray.m_direction.y, tmin*ray.m_direction.z}
        +ray.m_origin;

        if ((boxhit.m_point.x)==Approx(m_max.x))
        {
           boxhit.m_normal=glm::vec3(1.0f,0.0f,0.0f); // right
        }else if ((boxhit.m_point.x)==Approx(m_min.x))
        {
          boxhit.m_normal=glm::vec3(-1.0f,0.0f,0.0f); //left
        }else if ((boxhit.m_point.y)==Approx(m_max.y))
        {
          boxhit.m_normal=glm::vec3(0.0f,1.0f,0.0f); //fup
        }else if ((boxhit.m_point.y)==Approx(m_min.y))
        {
          boxhit.m_normal=glm::vec3(0.0f,-1.0f,0.0f); //down
        }else if ((boxhit.m_point.z)==Approx(m_max.z))
        {
          boxhit.m_normal=glm::vec3(0.0f,0.0f,1.0f); //front
        }else
        {
          boxhit.m_normal=glm::vec3(0.0f,0.0f,-1.0f); //back
        }
    }
    return boxhit;
  }
  //
  void Lensbox::scale(float faktor)
  {
    //Skaliere von min ausgehend!
    glm::vec3 diff=m_max-m_min;
    m_max=m_min+(diff*faktor);
    //translate(XXX); Damit Zentrum bleibt?
  }

  void Lensbox::translate(glm::vec3 const& vec)
    {
      m_min+=vec;
      m_max+=vec;
    }

  void Lensbox::rotate(float angle,glm::vec3 const& vec)
  {
    //NOT YET IMPLEMENTED
  }
