#ifndef     __PARTICULE_SYSTEM_SHAPE_HPP__
# define    __PARTICULE_SYSTEM_SHAPE_HPP__

#include <glm/glm.hpp>

namespace	ParticleSystem
{
  class		Shape
  {
  public:
    enum	Type
      {
	BOX,
	SPHERE,
	HEMISPHERE,
	CONE
      };

  protected:
    //----------------------------------------------
    //
    //----------------------------------------------
    Shape(bool randomDirection, bool isActive, Type);

    //----------------------------------------------
    //
    //----------------------------------------------
    ~Shape(void) {}

  public:
    //----------------------------------------------
    //
    //----------------------------------------------
    virtual void	apply(glm::vec3 &, glm::vec3 &) = 0;

  public:
    //----------------------------------------------
    //
    //----------------------------------------------
    Type		getType(void) const
    {
      return this->_type;
    }

    //----------------------------------------------
    //
    //----------------------------------------------
    bool		isActive(void) const
    {
      return this->_isActive;
    }

    //----------------------------------------------
    //
    //----------------------------------------------
    bool		getRandomDirectionMode(void) const
    {
      return this->_randomDirection;
    }

  public:

    //----------------------------------------------
    //
    //----------------------------------------------
    void		setRandomDirectionModeTo(bool randomDirection)
    {
      this->_randomDirection = randomDirection;
    }

    //----------------------------------------------
    //
    //----------------------------------------------
    void		setActiveModeTo(bool activeMode)
    {
      this->_isActive = activeMode;
    }

  protected:
    bool		_isActive;
    bool		_randomDirection;
    Type		_type;
  };
}


#endif
