#include "Shape.hpp"

namespace   ParticleSystem
{
  Shape::Shape(bool randomDirection, bool isActive, Shape::Type type) :
    _isActive(isActive),
    _randomDirection(randomDirection),
    _type(type)
  {
  }
}
