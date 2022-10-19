#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"


class Shape
{
public:
	//constr./Destr
	Shape();
	Shape(std::string const& name, Material const& mtrl);
	Shape(std::string const& name, std::shared_ptr<Material> mtrl);
	virtual ~Shape();

	//getter
	std::shared_ptr<Material> material() const;
	std::string const& name() const;
	//###############################################################
	bool const& transf() const;
	glm::mat4x4 const& world_transformation() const;
	glm::mat4x4 const& world_transformation_inv() const;
	glm::mat4x4 const& world_transformation_inv_transp() const;
	/*
	virtual float area() const = 0;
	virtual float volume() const = 0;
	*/




	//Funktionen
	virtual std::ostream& print(std::ostream& os) const;
	virtual Hit intersect(Ray const& inray) const = 0;
	virtual void scale(glm::vec3 const& vec);
	virtual void rotate(float angle, glm::vec3 const& vec);
	virtual void translate(glm::vec3 const& vec);



private:
	std::string name_;
	std::shared_ptr<Material> material_;
	glm::mat4x4 world_transformation_;
	glm::mat4x4 world_transformation_inv_;
	glm::mat4x4 world_transformation_inv_transp_;
	bool m_transf;


};

//dingsoperator
std::ostream& operator <<(std::ostream& os, Shape const& s);


#endif
