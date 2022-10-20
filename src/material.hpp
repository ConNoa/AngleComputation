#pragma once

#include <ostream>
#include "color.hpp"
#include <string>

struct Material
{
//KONSTRUTOREN----------------------------------------------------------------------
 	//Default
	Material():
	name 	{"Default"},
	ka  	{0.0f,0.0f,0.0f},
	kd  	{0.0f,0.0f,0.0f},
	ks  	{0.0f,0.0f,0.0f},
	kr 		{0.0f},
	opac	{0.0f},
	eta		{0.0f},
 	m   	{0.0f}{}
 	//Custom
	Material(std::string const& Name, Color const& k1, Color const& k2, Color const& k3, float k4, float k5, float k6, float M):
	name	{Name},
	ka 		{k1},
	kd 		{k2},
	ks 		{k3},
	kr   	{k4},
	opac	{k5},
	eta		{k6},
	m 		{M}{}

//FRIENDA-------------------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream& os, Material const& mat )
	{
		os << "name: " << mat.name << "\n"
		<<"ka: "<< mat.ka
		<<",kd: "<< mat.kd
		<<",ks: "<< mat.ks
		<<",kr: "<<mat.kr
		<<",m: " << mat.m << "\n";
		return os;
	}

//VARIABLEN
	std::string name;

	Color ka; //ambient
	Color kd; //diffuse
	Color ks; //specular
	float kr; //reflect
	float opac; //durchsichtigkeit
	float eta; //refractive index
	float m;
};
