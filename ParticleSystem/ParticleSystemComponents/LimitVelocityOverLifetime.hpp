#ifndef		__PARTICLE_SYSTEM_LIMIT_VELOCITY_OVER_LIFETIME_HPP__
# define	__PARTICLE_SYSTEM_LIMIT_VELOCITY_OVER_LIFETIME_HPP__

namespace	ParticleSystem
{
  //----------------------------------------
  // Controls the velocity limit and damping of each particle during its lifetime.
  //----------------------------------------
  struct	LimitVelocityOverLifetime
  {
    //----------------------------------------
    // If enabled, you can control the velocity limit separately for each axis.
    //----------------------------------------
    bool		separateAxis;

    //----------------------------------------
    // The speed limit of particles over the particle lifetime.
    //----------------------------------------
    MinMaxValueFloat	speed;

    //----------------------------------------
    // Controls how much the velocity that exceeds the velocity limit should be dampened.
    // A value of 0.5 will dampen the exceeding velocity by 50%.
    //----------------------------------------
    float		dampen;
  };
}

#endif
