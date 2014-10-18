#ifndef		__PARTICLE_SYSTEM_ROTATION_BY_SPEED_HPP__
# define	__PARTICLE_SYSTEM_ROTATION_BY_SPEED_HPP__

namespace	ParticleSystem
{
  struct	RotationBySpeed
  {
    MinMaxValueFloat		_size;
    std::pair<float, float>	_speedRange;
  };

}

#endif /* !__PARTICLE_SYSTEM_ROTATION_BY_SPEED_HPP__ */
