#include "shape.hpp"


//KONSTRUTOREN----------------------------------------------------------------------
	Shape::Shape() :
	m_name {"Shape"},
	m_material {} {
		std::cout << "Shape-Construction" << m_name << std::endl;
	}

	Shape::Shape(std::string const& name, int mat_id) :
	m_name {name},
	m_material {mat_id} {
		std::cout <<":Shape-Construction: " << m_name << std::endl;
	}

	// Shape::Shape(std::string const& name, std::shared_ptr<Material> mat) :
	// m_name {name},
	// m_mat {mat}{std::cout <<":Shape-Construction: " << m_name << std::endl;}


	Shape::~Shape()
	{
	  std::cout << "Shape-Destruction: " << m_name << std::endl;
	}

//GETTER----------------------------------------------------------------------
	std::string Shape::name() const{
	  return m_name;
	}


	std::shared_ptr<Material> Shape::material() const{
		std::shared_ptr<Material> m_mat = std::make_shared<Material>(m_material); // overload (1)
		// m_mat.push_back(m_material);
	  return m_mat;
	}

//FUNKTIONEN---------------------------------------------------------------------
	// print 1
	std::ostream& Shape::print(std::ostream& os) const
	{
	  os << "Name: " << m_name << "\n"

	  << "Material: (" << m_mat<< std::endl;
	  return os;
	}

	// print 2
	std::ostream& operator << (std::ostream& os, Shape const& s)
	{
	  return s.print(os);
	}
