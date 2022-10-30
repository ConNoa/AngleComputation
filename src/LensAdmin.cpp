#pragma once



#include <fstream>
#include "Lens.hpp"



class LensAdmin{

  public:

    // void write_rpf(std::string const& name_of_rpf);
    // void write_rpf(std::shared_ptr<Lens> const& new_Lenses);


  void write_rpf(std::shared_ptr<Lens> const& l){
    std::fstream f;
    f.open("Saved_Lenses.save", std::ios::app);
    f << "-----------"  << "\n " ;
    // for(anew_Lenses){
      f << "m_name: " << l->name()<< ";\n";
      f << "mat_id: " << l->material()->id<< ";\n";
      f << "m_id: " << l->m_id<< ";\n";
      f << "m_orig: " << l->m_orig.x<< " "<<l->m_orig.y<< " "<<l->m_orig.z<< ";\n";
      // f << "m_direc " << l->m_direc.x<< " "<<l->m_direc.y<< " "<<l->m_direc.z<< ";\n";
      f << "m_diameter: " << l->m_diameter<< ";\n";
      f << "m_width: " << l->m_width<< ";\n";
      f << "m_r1: " << l->m_r1<< ";\n";
      f << "m_r2: " << l->m_r2<< ";\n";
    //   f << "dis_sample " << mi->_displayed_sample.id<< " "<< mi->_displayed_sample.x<< " "<< mi->_displayed_sample.y<< " "<< mi->_displayed_sample.dis<< ";\n";
    //   f << "sample_amount " << mi->_ammount_of_matching_samples<< ";\n";
    //   for(auto sam = mi->_matching_samples.begin(); sam!=mi->_matching_samples.end(); ++sam){
    //     f << "s_pos " <<sam->x<< " "<< sam->y<< " "<< sam->dis<< ";\n";
    //   }
      // f << "--- " << ";\n";
    // }
     f << ".........." << "\n";

    f.close();

    }



    //
    //
    // std::string m_name;
    // std::shared_ptr<Material> m_mat;
    //  int mat_id;
    // Material m_material;
    //
    //
    // vec3  m_orig;           //Origin -  Mittelpunkt der Linse
    // float m_diameter;       //Real-Durchmesser der Linse
    // float m_width;          //Breite des Glaskörpers zwischen geschliffenen Linsenseiten
    // float m_r1;             //Radius der theoretischen Kugel der vorderen Linsenseite
    // float m_r2;             //Radius der theoretischen Kugel der hinteren Linsenseite
    // int m_id;

    // #include <fstream>
    //
    // std::ofstream out;
    //
    // // std::ios::app is the open mode "append" meaning
    // // new data will be written to the end of the file.
    // out.open("myfile.txt", std::ios::app);
    //
    // std::string str = "I am here.";
    // out << str;
    //
    //
    //
    //
    //
    // // writing on a text file
    // #include <iostream>
    // #include <fstream>
    // using namespace std;
    //
    // int main () {
    //   ofstream myfile ("example.txt");
    //   if (myfile.is_open())
    //   {
    //     myfile << "This is a line.\n";
    //     myfile << "This is another line.\n";
    //     myfile.close();
    //   }
    //   else cout << "Unable to open file";
    //   return 0;
    // }
    //
    //
    //
    //
    // // void LensAdmin::write_rpf(Lens const& name_of_rpf){
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

  };
