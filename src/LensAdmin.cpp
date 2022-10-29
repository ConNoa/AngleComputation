#include <fstream>
#include "Lens.hpp"



class LensAdmin{

  public:

    // void write_rpf(std::string const& name_of_rpf);
    void write_rpf(Lens const& new_lens);

  private:


  };

  void LensAdmin::write_rpf(Lens const& new_Lens){
    std::fstream f;
    f.open("Saved_Lenses", std::ios::out);
    f << "Saved Lenses"  << " " ;
    / for(auto mi = _mems_mirrors.begin(); mi!= _mems_mirrors.end(); ++mi){
    //   f << "m_id " << mi->id<< ";\n";
    //   f << "m_pos " << mi->_position.x<< " "<< mi->_position.y<< " "<< mi->_position.dis<< ";\n";
    //   f << "dis_sample " << mi->_displayed_sample.id<< " "<< mi->_displayed_sample.x<< " "<< mi->_displayed_sample.y<< " "<< mi->_displayed_sample.dis<< ";\n";
    //   f << "sample_amount " << mi->_ammount_of_matching_samples<< ";\n";
    //   for(auto sam = mi->_matching_samples.begin(); sam!=mi->_matching_samples.end(); ++sam){
    //     f << "s_pos " <<sam->x<< " "<< sam->y<< " "<< sam->dis<< ";\n";
    //   }
      f << "--- " << ";\n";

    f.close();

    }

    std::string m_name;
    std::shared_ptr<Material> m_mat;
     int mat_id;
    Material m_material;


    vec3  m_orig;           //Origin -  Mittelpunkt der Linse
    float m_diameter;       //Real-Durchmesser der Linse
    float m_width;          //Breite des Glaskörpers zwischen geschliffenen Linsenseiten
    float m_r1;             //Radius der theoretischen Kugel der vorderen Linsenseite
    float m_r2;             //Radius der theoretischen Kugel der hinteren Linsenseite
    int m_id;




    // void LensAdmin::write_rpf(Lens const& name_of_rpf){
    //   std::fstream f;
    //   f.open(name_of_rpf, std::ios::out);
    //   f << "Saved Lenses"  << " "  <<
    //   for(auto mi = _mems_mirrors.begin(); mi!= _mems_mirrors.end(); ++mi){
    //     f << "m_id " << mi->id<< ";\n";
    //     f << "m_pos " << mi->_position.x<< " "<< mi->_position.y<< " "<< mi->_position.dis<< ";\n";
    //     f << "dis_sample " << mi->_displayed_sample.id<< " "<< mi->_displayed_sample.x<< " "<< mi->_displayed_sample.y<< " "<< mi->_displayed_sample.dis<< ";\n";
    //     f << "sample_amount " << mi->_ammount_of_matching_samples<< ";\n";
    //     for(auto sam = mi->_matching_samples.begin(); sam!=mi->_matching_samples.end(); ++sam){
    //       f << "s_pos " <<sam->x<< " "<< sam->y<< " "<< sam->dis<< ";\n";
    //     }
    //     f << "--- " << ";\n";
    //   }
    //   f.close();
    //
    //   }
