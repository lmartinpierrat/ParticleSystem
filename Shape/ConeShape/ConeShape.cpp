#include	"ConeShape.hpp"

namespace	ParticleSystem
{
  ConeShape::ConeShape(float angle, float radius, float length,
		       ConeShape::EmitFrom emitFrom, bool randomDirection, bool isActive) :
    Shape(randomDirection, isActive, Shape::CONE),
    _angle(angle),
    _radius(radius),
    _length(length),
    _emitFrom(emitFrom)
  {
  }

  void
  ConeShape::apply(glm::vec3 &position, glm::vec3 &force)
  {
    glm::vec2       rand = this->_emitFrom == ConeShape::BASE || this->_emitFrom == ConeShape::VOLUME ? glm::diskRand(this->_radius) : glm::circularRand(this->_radius);
    glm::vec2       ratio(rand.x / this->_radius, rand.y / this->_radius);

    position.x += rand.x;
    position.y += rand.y;
    force.z = 1.0f;
    force += glm::vec3(glm::sin(glm::radians(ratio.x * this->_angle)),
		       glm::sin(glm::radians(ratio.y * this->_angle)),
		       glm::cos(glm::radians(ratio.x * this->_angle)));
    force = glm::normalize(force);
    if (this->_emitFrom == ConeShape::VOLUME || this->_emitFrom == ConeShape::VOLUMESHELL)
      position += force * glm::linearRand(0.0f, this->_length);
  }
}
