#pragma once



#include <fstream>
#include "Lens.hpp"
#include "Lens_konkav.hpp"
#include "Lens_konvex.hpp"
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4


class LensAdmin{

  public:

    // void write_rpf(std::string const& name_of_rpf);
    // void write_rpf(std::shared_ptr<Lens> const& new_Lenses);


  void write_rpf(std::shared_ptr<Lens> const& l){
    if (std::shared_ptr<Lens_konkav> lk = boost::dynamic_pointer_cast<Lens_konkav>(l)){
      std::fstream f;
      f.open("Saved_Lenses.save", std::ios::app);
      f << "-----------"  << "\n " ;
      // for(anew_Lenses){
        f << "m_name: " << lk->name()<< ";\n";
        f << "mat_id: " << lk->material()->id<< ";\n";
        f << "m_id: " << lk->m_id<< ";\n";
        f << "m_orig: " << lk->m_orig.x<< " "<<lk->m_orig.y<< " "<<lk->m_orig.z<< ";\n";
        // f << "m_direc " << lk->m_direc.x<< " "<<lk->m_direc.y<< " "<<lk->m_direc.z<< ";\n";
        f << "m_diameter: " << lk->m_diameter<< ";\n";
        f << "m_width: " << lk->m_width<< ";\n";
        f << "m_r1: " << lk->m_r1<< ";\n";
        f << "m_r2: " << lk->m_r2<< ";\n";
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
    if (std::shared_ptr<Lens_konvex> lk = boost::dynamic_pointer_cast<Lens_konvex>(l)){
      std::fstream f;
      f.open("Saved_Lenses.save", std::ios::app);
      f << "-----------"  << "\n " ;
      // for(anew_Lenses){
        f << "m_name: " << lk->name()<< ";\n";
        f << "mat_id: " << lk->material()->id<< ";\n";
        f << "m_id: " << lk->m_id<< ";\n";
        f << "m_orig: " << lk->m_orig.x<< " "<<lk->m_orig.y<< " "<<lk->m_orig.z<< ";\n";
        // f << "m_direc " << lk->m_direc.x<< " "<<lk->m_direc.y<< " "<<lk->m_direc.z<< ";\n";
        f << "m_diameter: " << lk->m_diameter<< ";\n";
        f << "m_width: " << lk->m_width<< ";\n";
        f << "m_r1: " << lk->m_r1<< ";\n";
        f << "m_r2: " << lk->m_r2<< ";\n";
      //   f << "dis_sample " << mi->_displayed_sample.id<< " "<< mi->_displayed_sample.x<< " "<< mi->_displayed_sample.y<< " "<< mi->_displayed_sample.dis<< ";\n";
      //   f << "sample_amount " << mi->_ammount_of_matching_samples<< ";\n";
      //   for(auto sam = mi->_matching_samples.begin(); sam!=mi->_matching_samples.end(); ++sam){
      //     f << "s_pos " <<sam->x<< " "<< sam->y<< " "<< sam->dis<< ";\n";
      //   }
        // f << "--- " << ";\n";
      // }
       f << ".........." << "\n";

      f.close();    }
    }

  std::vector<Lens>load_rpf(std::string const& file_to_read){

    std::ifstream file_in;
    std::string line;
    std::vector<Lens> loadedLenses;
    // std::vector<Point_d> sampled_positions;
    // Point_d m_position;
    // Point_d sample_position;

    file_in.open(file_to_read);
    if (!file_in) {
        std::cerr << "Unable to open file "<<file_to_read;
        exit(1);   // call system to stop
    }
    else{
      while(std::getline(file_in, line)){

        std::stringstream ss;
        std::string keyword;
        ss << line;
        ss >> keyword;
        std::string name;
        if(keyword == "m_name:"){
          ss >> name;
        }
        int mat_id;
        if(keyword == "mat_id:"){
          ss >> mat_id;
        }
        int m_id;
        if(keyword == "m_id:"){
          ss >> m_id;
        }
        glm::vec3 orig;
        if(keyword == "m_orig:"){
          ss >> orig.x;
          ss >> orig.y;
          ss >> orig.z;
        }
        float dia;
        if(keyword == "m_diameter:"){
          ss >> dia;
        }
        float width;
        if(keyword == "m_width:"){
          ss >> dia;
        }
        float r1;
        if(keyword == "m_r1:"){
          ss >> r1;
        }
        float r2;
        if(keyword == "m_r2:"){
          ss >> r2;
        }
        if(keyword == "-----------"){
          // if(name == "Lens_konkav"){
          //
          //
          //   Lens_konkav incomming_lens = Lens_konkav{name, m_id};
          //   //
          //   // Lens_konkav incomming_lens;
          //   // Material newMat{mat_id};
          //   // incomming_lens.name() = name;
          //   // //incomming_lens.m_id = mat_id;
          //   // incomming_lens.m_id = m_id;
          //   incomming_lens.m_orig = orig;
          //   incomming_lens.m_diameter = dia;
          //   incomming_lens.m_width = width;
          //   incomming_lens.m_r1 = r1;
          //   incomming_lens.m_r2 = r2;
          //   loadedLenses.push_back(incomming_lens);
          // }
          // if(name == "Lens_konvex"){
          //
          //   // Material newMat{mat_id};
          //   // incomming_lens.name() = name;
          //   // //incomming_lens.m_id = mat_id;
          //   // incomming_lens.m_id = m_id;
          //   Lens_konvex incomming_lens = Lens_konvex{name, m_id};
          //   incomming_lens.m_orig = orig;
          //   incomming_lens.m_diameter = dia;
          //   incomming_lens.m_width = width;
          //   incomming_lens.m_r1 = r1;
          //   incomming_lens.m_r2 = r2;
          //   loadedLenses.push_back(incomming_lens);
          // }
        }
      }
    }
    return loadedLenses;
  }
};

  //
  // class RPF_reader{
  //
  //   public:
  //
  //     std::vector<Lens>load_rpf(std::string const& file_to_read);
  //
  //     std::vector<Lens>load_rpf_2(std::string const& file_to_read);
  //
  //   private:
  //
  //
  //   };
  //
  //   std::vector<Lens> RPF_reader::load_rpf(std::string const& file_to_read){
  //     std::ifstream file_in;
  //     std::string line;
  //     std::vector<Lens> loadedLenses;
  //     std::vector<Point_d> sampled_positions;
  //     Point_d m_position;
  //     Point_d sample_position;
  //
  //
  //     file_in.open(file_to_read);
  //     if (!file_in) {
  //         std::cerr << "Unable to open file "<<file_to_read;
  //         exit(1);   // call system to stop
  //     }
  //     else{
  //       while(std::getline(file_in, line)){
  //
  //         std::stringstream ss;
  //         std::string keyword;
  //
  //         ss << line;
  //         ss >> keyword;
  //
  //
  //         int id;
  //
  //         if(keyword == "m_id"){
  //           ss >> id;
  //
  //         }
  //
  //         if(keyword == "m_pos"){
  //
  //           ss >> m_position.x;
  //           ss >> m_position.y;
  //           ss >> m_position.dis;
  //
  //         }
  //
  //         Point_d displayed_sample;
  //         bool displayed = true;
  //
  //         if(keyword == "dis_sample"){
  //
  //
  //           ss >> displayed_sample.id;
  //           ss >> displayed_sample.x;
  //           ss >> displayed_sample.y;
  //           ss >> displayed_sample.dis;
  //           if(displayed_sample.dis == 99999){
  //             displayed = false;
  //           }
  //         }
  //
  //         int sample_amount;
  //
  //         if(keyword == "sample_amount"){
  //
  //
  //           ss >> sample_amount;
  //         }
  //
  //         if(keyword == "pos"){
  //
  //           ss >> sample_position.id;
  //           ss >> sample_position.x;
  //           ss >> sample_position.y;
  //           ss >> sample_position.dis;
  //
  //           sampled_positions.push_back(sample_position);
  //
  //         }
  //
  //         if(keyword == "---"){
  //
  //           Lens incomming_mirror;
  //
  //           incomming_mirror.id = id;
  //           incomming_mirror._position = m_position;
  //           incomming_mirror._displayed_sample = displayed_sample;
  //           incomming_mirror._ammount_of_matching_samples = sample_amount;
  //           incomming_mirror._matching_samples = sampled_positions;
  //           incomming_mirror.has_sample = displayed;
  //
  //           loadedLenses.push_back(incomming_mirror);
  //
  //         }
  //       }
  //     }
  //     return loadedLenses;
  //   }
  //
  //
  //
  //
  //   std::vector<Lens> RPF_reader::load_rpf_2(std::string const& file_to_read){
  //     std::ifstream file_in;
  //     std::string line;
  //     std::vector<Lens> loadedLenses;
  //     Point_d m_position;
  //     Point_d displayed_sample;
  //     std::vector<Point_d> sampled_positions;
  //     Point_d sample_position;
  //
  //
  //     file_in.open(file_to_read);
  //     if (!file_in) {
  //         std::cerr << "Unable to open file "<<file_to_read;
  //         exit(1);   // call system to stop
  //     }
  //     else{
  //       while(std::getline(file_in, line)){
  //
  //         std::stringstream ss;
  //         std::string keyword;
  //
  //         ss << line;
  //         ss >> keyword;
  //
  //
  //         int id;
  //
  //         if(keyword == "id"){
  //       //  std::cout <<"keyword: m_id " << '\n';
  //           ss >> id;
  //
  //         }
  //
  //
  //         if(keyword == "pos"){
  //
  //           ss >> m_position.x;
  //           ss >> m_position.y;
  //           ss >> m_position.dis;
  //
  //         }
  //
  //         bool displayed = true;
  //
  //         if(keyword == "dis_sample"){
  //           ss >> displayed_sample.x;
  //           ss >> displayed_sample.y;
  //           ss >> displayed_sample.dis;
  //           if(displayed_sample.dis == 99999){
  //             displayed = false;
  //           }
  //         }
  //
  //         if(keyword == "---"){
  //     //      std::cout <<"keyword: --- " << '\n';
  //
  //           Lens incomming_mirror;
  //
  //           incomming_mirror.id = id;
  //           incomming_mirror._position = m_position;
  //           incomming_mirror._displayed_sample = displayed_sample;
  //
  //           loadedLenses.push_back(incomming_mirror);
  //
  //         }
  //       }
  //     }
  //     return loadedLenses;
  //   }
  //
  //
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
