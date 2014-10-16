#ifndef     __PARTICULE_SYSTEM_SHAPE_HPP__
# define    __PARTICULE_SYSTEM_SHAPE_HPP__

#include <glm/glm.hpp>

namespace   ParticleSystem
{
  class   Shape
  {
  public:
    enum    Type
      {
	BOX,
	SPHERE,
	HEMISPHERE,
	CONE
      };

  protected:
    Shape(bool randomDirection, bool isActive, Type);
    ~Shape(void);

  public:
    virtual void	apply(glm::vec3 &, glm::vec3 &) = 0;

  public:
    inline Type		getType(void) const { return this->_type; }
    inline bool		isActive(void) const { return this->_isActive; }
    inline bool		getRandomDirectionMode(void) const { return this->_randomDirection; }

  public:
    inline void		setRandomDirectionModeTo(bool randomDirection) { this->_randomDirection = randomDirection; }
    inline void		setActiveModeTo(bool activeMode) { this->_isActive = activeMode; }

  protected:
    bool		_isActive;
    bool		_randomDirection;
    Type		_type;
  };
}

#endif
