#ifndef		__PARTICLE_SYSTEM_VELOCITY_OVER_LIFETIME_HPP__
# define	__PARTICLE_SYSTEM_VELOCITY_OVER_LIFETIME_HPP__

#include	"MinMaxValueFloat.hpp"
#include	"SimulationSpace.hpp"

namespace	ParticleSystem
{
  //----------------------------------------
  // Controls the velocity of each particle during its lifetime.
  //----------------------------------------
  struct	VelocityOverLifetime
  {
    MinMaxValueFloat	x;
    MinMaxValueFloat	y;
    MinMaxValueFloat	z;
    SimulationSpace	space;
  };
};

#endif /* !__PARTICLE_SYSTEM_VELOCITY_OVER_LIFETIME_HPP__ */
