#include "Composition.hpp"


//KONSTRUTOREN----------------------------------------------------------------------
	Composite::Composite() :
	m_name("default-comp"),
	m_shapes() {}

	Composite::Composite(std::string const& name ):
	m_name(name),
	m_shapes() {}

	Composite::~Composite() {}

//FUNKTIONEN-------------------------------------------------------------------------

	 /*ADD
	  ######################################
	  Fügt Shape hinzu! */
	void Composite::add(std::shared_ptr<Shape> shape)
	{
		m_shapes.push_back(shape);
   	}
      /*Fkt: ohit
	  ######################################
	  Gibt das durch einen Ray als erstes
	  getroffene Objekt mit DATA zurück! */
	Hit Composite::intersect(Ray ray) const
	{
		/*if (transf())
    	{
      		ray.m_origin-=transl();
    	}*/
		Hit hit;
		Hit temphit;
		for( auto &i : m_shapes)
		{
		  temphit= i->intersect(ray);
		  if(temphit.m_distance<hit.m_distance)
		  {
		    hit = temphit;
		  }
		}
		return hit;
	}

	void Composite::draw() const
	{
		return;
	}


	void Composite::update()
	{
		return;
	}


	void Composite::scale(float faktor)
	  {
	    for( auto &i : m_shapes)
		{
		  i->scale(faktor);
		}
	  }

  void Composite::translate(glm::vec3 const& vec)
    {
     	for( auto &i : m_shapes)
		{
		  i->translate(vec);
		}
    }

 void Composite::rotate(float angle,glm::vec3 const& vec)
  {
    //NOT YET IMPLEMENTED
  }
