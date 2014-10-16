#ifndef		__PARTICLE_SYSTEM_HEMISPHERE_SHAPE_HPP__
# define	__PARTICLE_SYSTEM_HEMISPHERE_SHAPE_HPP__

#include	"../SphereShape/SphereShape.hpp"

namespace	ParticleSystem
{
  class   HemisphereShape : public SphereShape
  {
  public:
    HemisphereShape(float = 1.0f, bool = false, bool = false, bool = true);
    ~HemisphereShape(void) {}

  public:
    virtual void    apply(glm::vec3 &, glm::vec3 &);
  };
}

#endif /* !__PARTICLE_SYSTEM_HEMISPHERE_SHAPE_HPP__ */
