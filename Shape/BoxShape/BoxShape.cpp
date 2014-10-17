#include	"BoxShape.hpp"
#include	<glm/gtc/random.hpp>

namespace	ParticleSystem
{
  BoxShape::BoxShape(const glm::vec3 &box, bool randomDirection, bool isActive) :
    Shape(randomDirection, isActive, Shape::BOX),
    _box(box)
  {

  }

  void
  BoxShape::apply(glm::vec3 &position, glm::vec3 &force)
  {
    position.x += glm::linearRand(-this->_box.x / 2.0f, this->_box.x / 2.0f);
    position.y += glm::linearRand(-this->_box.y / 2.0f, this->_box.y / 2.0f);
    position.z += glm::linearRand(-this->_box.z / 2.0f, this->_box.z / 2.0f);
    if (this->_randomDirection == true)
      {
	force.x += glm::linearRand(-1.0f, 1.0f);
	force.y += glm::linearRand(-1.0f, 1.0f);
	force.z += glm::linearRand(-1.0f, 1.0f);
      }
    else
      {
	force += glm::vec3(0.0f, 0.0f, 1.0f);
      }
    force = glm::normalize(force);
  }
}
