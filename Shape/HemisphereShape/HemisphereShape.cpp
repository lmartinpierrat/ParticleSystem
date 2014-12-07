#include	"HemisphereShape.hpp"

namespace	ParticleSystem
{
  HemisphereShape::HemisphereShape(float radius, bool emitFromShell,
				   bool randomDirection, bool isActive) :
    SphereShape(Shape::HEMISPHERE, radius, emitFromShell, randomDirection, isActive)
  {
  }

  void
  HemisphereShape::apply(glm::vec3 &position, glm::vec3 &force)
  {
    glm::vec3   tmpPos(0.0f, 0.0f, 0.0f);
    glm::vec3   tmpForce(0.0f, 0.0f, 0.0f);

    this->SphereShape::apply(tmpPos, tmpForce);
    tmpPos.z = glm::abs(tmpPos.z);
    tmpForce.z = glm::abs(tmpForce.z);
    position += tmpPos;
    force += tmpForce;
  }
}
