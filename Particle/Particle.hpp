#ifndef		__PARTICLE_SYSTEM_PARTICLE_HPP__
# define	__PARTICLE_SYSTEM_PARTICLE_HPP__

#include	<glm/glm.hpp>
#include	<vector>

namespace	ParticleSystem
{

  //----------------------------------------
  //
  //----------------------------------------
  class		Particle
  {
  public:
    //----------------------------------------
    // Constructor
    //
    // @param :
    // position : represent the position of the particle in the world
    // rotation : represent the rotation of the particle in the world
    // scale : represent the size of the particle in XYZ axis.
    //----------------------------------------
    Particle(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
	     const glm::vec3 &rotation = glm::vec3(0.0f, 0.0f, 0.0f),
	     const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f));

    //----------------------------------------
    // Destructor
    //----------------------------------------
    ~Particle(void) {}

  public:
    //----------------------------------------
    // 
    //----------------------------------------
    float	getLifetime(void) const
    {
      return this->_lifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    bool	isAlive(void) const
    {
      return this->_lifetime > 0.0f;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    const glm::vec3	&getForce(void) const
    {
      return this->_force;
    }

  public:
    //----------------------------------------
    // 
    //----------------------------------------
    void	setLifetime(float newLifetime)
    {
      this->_lifetime = newLifetime;
    }

    //----------------------------------------
    // 
    //----------------------------------------
    void	setForce(const glm::vec3 &newForce)
    {
      this->_force = newForce;
    }

  public:
    //----------------------------------------
    // Update is the function you need to call each frame with the time elapsed
    // between the two last frame for update the particle position in the scene.
    //
    // Thread safe
    //----------------------------------------
    void	update(float timeElapsed);

    //----------------------------------------
    // draw is the function you need to call when you want to get vertex / uvs / color of the particle
    // in the scene.
    // 
    // @param:
    // camPosition : must contains the camera position in the scene.
    //
    // Thread safe
    //----------------------------------------
    void	draw(const glm::vec3 &camPosition, std::vector<float> &vertex);

    //----------------------------------------
    // 
    //----------------------------------------
    glm::mat4	lookAt(const glm::vec3 &, const glm::vec3 &);

  private:

    //----------------------------------------
    // This attribute is used to save the lifetime of the particle.
    //----------------------------------------
    float	_lifetime;

    //----------------------------------------
    // This attribute is used to save the 3D position of the Particle
    //----------------------------------------
    glm::vec3	_force;

    //----------------------------------------
    // This attribute is used to save the 3D position of the Particle
    //----------------------------------------
    glm::vec3	_position;

    //----------------------------------------
    // This attribute is used to save the 3D rotation of the Particle
    //----------------------------------------
    glm::vec3	_rotation;

    //----------------------------------------
    // This attribute is used to save the 3D scale of the Particle
    //----------------------------------------
    glm::vec3	_scale;

  };
}

#endif /* !__PARTICLE_SYSTEM_PARTICLE_HPP__ */
