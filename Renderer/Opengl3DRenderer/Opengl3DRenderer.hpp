#ifndef		__PARTICLE_SYSTEM_OPENGL_3D_RENDERER_HPP__
# define	__PARTICLE_SYSTEM_OPENGL_3D_RENDERER_HPP__

#include	"Renderer.hpp"
#include	<glbinding/gl/gl.h>

namespace	ParticleSystem
{

  class	Opengl3DRenderer : public Renderer
  {

  public:
    Opengl3DRenderer(void);
    ~Opengl3DRenderer(void);

  public:
    void	draw(const glm::mat4 &projection, const glm::mat4 &modelview,
		     const std::vector<float> &vertex);

  public:
    // Material	&getMaterial(void)
    // {
    //   return this->_material;
    // }

    Shader	&getShader(void)
    {
      return this->_shader;
    }

  private:
    gl::GLuint	_vertexBufferID;
    // Material	_material;
    Shader	_shader;

  };
}

#endif /* !__PARTICLE_SYSTEM_OPENGL_3D_RENDERER_HPP__ */
