#pragma once

#include <ostream>
#include "color.hpp"
#include <string>

struct Material
{
//KONSTRUTOREN----------------------------------------------------------------------
//VARIABLEN

	  // std::string name;
		//category Index
		//refractive index
		//durchsichtigkeit
		//reflect
		//color of Material


	 	//Default
		Material():
		name 	{"Default"},
		id		{999999},
		n  		{0.0f},
		opac  {0.0f},
		r 		{0.0f},
		c  		{0.0f,0.0f,0.0f}{}

		// //LenseMaterial
		// Material(float n_in):
		// name	{"OPTIK"},
		// id 		{1},
		// n  		{n_in},
		// opac  {0.0f},
		// r 		{0.0f},
		// c  		{0.0f,0.0f,0.0f}{}


		//Custom
		Material(int id_in):
		name	{"Default"},
		id 		{id_in},
		n  		{0.0f},
		opac  {0.0f},
		r 		{0.0f},
		c  		{0.0f,0.0f,0.0f}{		if(id_in == 0){name="Luft"; n=1.000292f;opac=0.1f;opac=0.1f; c={75, 196, 213};}
															if(id_in == 1){name="Quarzglas"; n=1.46f;opac=0.1f;}
															if(id_in == 2){name="Fensterglas"; n=1.52f;opac=0.1f;}
															if(id_in == 3){name="Kronglas"; n=1.65f;opac=0.1f;}
															if(id_in == 4){name="Flintglas"; n=1.75f;opac=0.1f;}
															if(id_in == 5){name="Epoxidharz"; n=1.60f;opac=0.1f;}
															if(id_in == 6){name="Bleikristall"; n=1.93f;opac=0.1f;}
															if(id_in == 4){name="Diamant"; n=2.42f;opac=0.1f;}
															if(id_in == 100){name="Leinwand"; opac=1.0f;}}

		//Custom
		Material(std::string const& Name):
		name	{Name},
		id 		{9999},
		n  		{0.0f},
		opac  {0.0f},
		r 		{0.0f},
		c  		{0.0f,0.0f,0.0f}{}

		//Custom
		Material(std::string const& Name, int id_in):
		name	{Name},
		id 		{id_in},
		n  		{0.0f},
		opac  {0.0f},
		r 		{0.0f},
		c  		{0.0f,0.0f,0.0f}{}


		//Custom
		Material(std::string const& Name, int id_in, float n_in, float opac_in, float r_in ,Color const& c_in):
		name	{Name},
		id 		{id_in},
		n  		{n_in},
		opac  {opac_in},
		r 		{r_in},
		c  		{c_in}{}


	//FRIENDA-------------------------------------------------------------------------
		friend std::ostream& operator<<(std::ostream& os, Material const& mat )
		{
			os << "name: " << mat.name 
			<<"ID: "<< mat.id
			<<", refraction: "<< mat.n
			<<", opacity: "<< mat.opac
			<<", reflection: "<< mat.r<< " ";
			return os;
		}

	//VARIABLEN
		std::string name;
		int 	id; //category Index
		float n; //refractive index
		float opac; //durchsichtigkeit
		float r; //reflect
		Color c; //color of Material
};
