#ifndef     __PARTICLE_HPP__
# define    __PARTICLE_HPP__

#include "../../../includes/glm/gtc/matrix_transform.hpp"
#include "../../../includes/OpenGL.hh"
#include "../MinMaxValue/MinMaxValue.hpp"

namespace   ParticleSystem
{
  class   Particle
  {
  public:
    //----------------------------------------
    // Constructor
    //----------------------------------------
    Particle(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    //----------------------------------------
    // Destructor
    //----------------------------------------
    ~Particle(void);

  public:
    //----------------------------------------
    // 
    //----------------------------------------
    bool                    update(void);

    //----------------------------------------
    // 
    //----------------------------------------
    void                    draw(const glm::mat4 &, const glm::mat4 &);

  public:
    //----------------------------------------
    // Lifetime of a particle is used to represent is life duration on the screen.
    // lifetime of a particle is decremented over the  time when you call "update"
    //----------------------------------------
    void                    setLifetime(float lifetime)
    {
      this->_lifetime = lifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setSpeed(float speed)
    {
      this->_speed = speed;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setColor(const glm::vec4 &color)
    {
      this->_color = color;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setGravityMultiplier(float gravity)
    {
      this->_gravityMultiplier = gravity;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setForce(const glm::vec3 &force)
    {
      this->_force = force;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setColorOverLifetime(const MinMaxValueColor &colorOverLifetime)
    {
      this->_colorOverLifetime = colorOverLifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setSizeOverLifetime(const MinMaxValueFloat &sizeOverLifetime)
    {
      this->_sizeOverLifetime = sizeOverLifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void                    setRotationOverLifetime(const MinMaxValueFloat &rotationOverLifetime)
    {
      this->_rotationOverLifetime = rotationOverLifetime;
    }

  public:
    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec3         &getPosition(void) const
    {
      return this->_position;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec3         &getRotation(void) const
    {
      return this->_rotation;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec3         &getScale(void) const
    {
      return this->_scale;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec3         &getActualScale(void) const
    {
      return this->_scaleWithGrowth;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    float                   getLifetime(void) const
    {
      return this->_lifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    float                   getActualLifetime(void) const
    {
      return this->_actualLifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    float                   getSpeed(void) const
    {
      return this->_speed;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    float                   getGravityMultiplier(void) const
    {
      return this->_gravityMultiplier;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec4         &getColor(void) const
    {
      return this->_color;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec3         &getForce(void) const
    {
      return this->_force;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const MinMaxValueColor  &getColorOverLifetime(void) const
    {
      return this->_colorOverLifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const MinMaxValueFloat  &getSizeOverLifetime(void) const
    {
      return this->_sizeOverLifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const MinMaxValueFloat  &getRotationOverLifetime(void) const
    {
      return this->_rotationOverLifetime;
    }

  public:
    //----------------------------------------
    // 
    //----------------------------------------
    bool                isAlive(void) const
    {
      return this->_lifetime > this->_actualLifetime;
    }

  private:
    //----------------------------------------
    // 
    //----------------------------------------
    glm::mat4           lookAt(const glm::vec3 &, const glm::vec3 &);

  private:
    //----------------------------------------
    // 
    //----------------------------------------
    glm::vec3           _position;

    //----------------------------------------
    // 
    //----------------------------------------
    glm::vec3           _rotation;

    //----------------------------------------
    // 
    //----------------------------------------
    glm::vec3           _scale;

    //----------------------------------------
    // 
    //----------------------------------------
    glm::vec3           _actualScale;

    //----------------------------------------
    // 
    //----------------------------------------
    float               _lifetime;

    //----------------------------------------
    // 
    //----------------------------------------
    float               _actualLifetime;

    //----------------------------------------
    // 
    //----------------------------------------
    float               _speed;

    //----------------------------------------
    // 
    //----------------------------------------
    float               _gravityMultiplier;

    //----------------------------------------
    // 
    //----------------------------------------
    glm::vec4           _color;

    //----------------------------------------
    // 
    //----------------------------------------
    glm::vec3           _force;

    //----------------------------------------
    // 
    //----------------------------------------
    MinMaxValueColor    &_colorOverLifetime;

    //----------------------------------------
    // 
    //----------------------------------------
    MinMaxValueFloat    &_sizeOverLifetime;

    //----------------------------------------
    // 
    //----------------------------------------
    MinMaxValueFloat    &_rotationOverLifetime;

  private:

    //----------------------------------------
    // 
    //----------------------------------------
    gdl::Geometry       *_geometry;

    //----------------------------------------
    // 
    //----------------------------------------
    gdl::Texture        *_texture;

    //----------------------------------------
    // 
    //----------------------------------------
    gdl::BasicShader    *_shader;
  };
}

#endif

