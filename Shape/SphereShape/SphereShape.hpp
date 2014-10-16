#ifndef		__PARTICLE_SYSTEM_SPHERE_SHAPE_HPP__
# define	__PARTICLE_SYSTEM_SPHERE_SHAPE_HPP__

#include	"../Shape.hpp"

namespace	ParticleSystem
{
  class   SphereShape : public ParticleSystem::Shape
  {
  public:
    SphereShape(float = 1.0f, bool = false, bool = false, bool = true);
    ~SphereShape(void);

  public:
    virtual void	apply(glm::vec3 &, glm::vec3 &);
    
  public:
    inline float	getRadius(void) const { return this->_radius; }
    inline bool		getEmitFromShell(void) const { return this->_emitFromShell; }
    
  public:
    inline void		setRadiusTo(float radius) { this->_radius = radius; }
    inline void		setEmitFromShellTo(bool emitFromShell) { this->_emitFromShell = emitFromShell; }

  protected:
    float	_radius;
    bool	_emitFromShell;
  };
}

#endif /* !__PARTICLE_SYSTEM_SPHERE_SHAPE_HPP__ */
