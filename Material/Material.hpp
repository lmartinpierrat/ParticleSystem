#ifndef		__PARTICLE_SYSTEM_MATERIAL_HPP__
# define	__PARTICLE_SYSTEM_MATERIAL_HPP__

namespace	ParticleSystem
{

  class		Material
  {
  public:
    Material(void);
    ~Material(void);

  public:
    Shader	&getShader(void);

  private:
    Shader	_shader;
  };

}

#endif /* !__PARTICLE_SYSTEM_MATERIAL_HPP__ */
