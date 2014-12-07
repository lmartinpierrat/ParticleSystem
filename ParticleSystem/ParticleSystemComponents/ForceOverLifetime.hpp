#ifndef		__PARTICLE_SYSTEM_FORCE_OVER_LIFETIME_HPP__
# define	__PARTICLE_SYSTEM_FORCE_OVER_LIFETIME_HPP__

namespace	ParticleSystem
{
  //----------------------------------------
  // Controls the force of each particle during its lifetime.
  //----------------------------------------
  struct	ForceOverLifetime
  {
    //----------------------------------------
    // The force applied to the X axis during the lifetime of each particles.
    //----------------------------------------
    MinMaxValueFloat	x;

    //----------------------------------------
    // The force applied to the Y axis during the lifetime of each particles.
    //----------------------------------------
    MinMaxValueFloat	y;

    //----------------------------------------
    // The force applied to the Z axis during the lifetime of each particles.
    //----------------------------------------
    MinMaxValueFloat	z;

    //----------------------------------------
    // 
    //----------------------------------------
    bool		randomize;

    //----------------------------------------
    // Specifies if the force values are in local space (rotated with the transform) or world space.
    //----------------------------------------
    SimulationSpace	space;
  };
}

#endif /* !__PARTICLE_SYSTEM_FORCE_OVER_LIFETIME_HPP__ */
