#ifndef		__PARTICLE_SYSTEM_BOX_SHAPE_HPP__
# define	__PARTICLE_SYSTEM_BOX_SHAPE_HPP__

#include	"Shape.hpp"

namespace	ParticleSystem
{
  class	BoxShape : public ParticleSystem::Shape
  {
  public:
    BoxShape(const glm::vec3 & = glm::vec3(0.0f, 0.0f, 0.0f), bool = false, bool = true);
    ~BoxShape(void) {}

  public:
    virtual void	apply(glm::vec3 &, glm::vec3 &);

  public:
    void		setBoxTo(const glm::vec3 &box) { this->_box = box; }

  public:
    const glm::vec3	&getBox(void) const { return this->_box; }

  protected:
    glm::vec3           _box;
  };
}

#endif /* !__PARTICLE_SYSTEM_BOX_SHAPE_HPP__ */
