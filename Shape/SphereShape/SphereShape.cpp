#include	"SphereShape.hpp"

namespace	ParticleSystem
{
  SphereShape::SphereShape(float radius, bool emitFromShell,
			   bool randomDirection, bool isActive) :
    Shape(randomDirection, isActive, Shape::SPHERE),
    _radius(radius),
    _emitFromShell(emitFromShell)
  {
  }

  void
  SphereShape::apply(glm::vec3 &position, glm::vec3 &force)
  {
    glm::vec3   rand = this->_emitFromShell ? glm::sphericalRand(this->_radius) : glm::ballRand(this->_radius);

    position += rand;
    if (this->_randomDirection)
      {
	force.x += glm::linearRand(-1.0f, 1.0f);
	force.y += glm::linearRand(-1.0f, 1.0f);
	force.z += glm::linearRand(-1.0f, 1.0f);
      }
    else
      {
	force += rand;
      }
    force = glm::normalize(force);
  }

}
