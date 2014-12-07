#ifndef		__PARTICLE_SYSTEM_RENDERER_HPP__
# define	__PARTICLE_SYSTEM_RENDERER_HPP__

#include	<glm/glm.hpp>
#include	<vector>
#include	"Shader.hpp"

namespace	ParticleSystem
{

  class		Renderer
  {
  public:
    Renderer(void) {}
    virtual ~Renderer(void) {}

  public:
    virtual void	draw(const glm::mat4 &projection, const glm::mat4 &modelview,
			     const std::vector<float> &vertex) = 0;

    virtual Shader	&getShader(void) = 0;

  private:
    
  };

}

#endif /* !__PARTICLE_SYSTEM_RENDERER_HPP__ */
