#ifndef		__PARTICLE_SYSTEM_CONE_SHAPE_HPP__
# define	__PARTICLE_SYSTEM_CONE_SHAPE_HPP__

#include	"Shape.hpp"

namespace	ParticleSystem
{
  class   ConeShape : public ParticleSystem::Shape
  {
  public:
    enum    EmitFrom
      {
	BASE,
	BASESHELL,
	VOLUME,
	VOLUMESHELL
      };

  public:
    ConeShape(float = 0.01f, float = 1.0f, float = 0.0f, EmitFrom = BASE, bool = false, bool = true);
    ~ConeShape(void) {}

  public:
    virtual void	apply(glm::vec3 &, glm::vec3 &);

  public:
    float		getAngle(void) const { return this->_angle; }
    float		getRadius(void) const { return this->_radius; }
    float		getLength(void) const { return this->_length; }
    EmitFrom		getEmitFromType(void) const { return this->_emitFrom; }

  public:
    void		setAngleTo(float angle) { this->_angle = angle; }
    void		setRadiusTo(float radius) { this->_radius = radius; }
    void		setLengthTo(float length) { this->_length = length; }
    void		setEmitFromTypeTo(EmitFrom type) { this->_emitFrom = type; }

  protected:
    float		_angle;
    float		_radius;
    float		_length;
    EmitFrom		_emitFrom;
  };
}

#endif /* __PARTICLE_SYSTEM_CONE_SHAPE_HPP__ */
