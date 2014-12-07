#include	"Opengl3DRenderer.hpp"
#include	<iostream> // A SUPPRIMER

int debug	= 0;

namespace	ParticleSystem
{

  Opengl3DRenderer::Opengl3DRenderer(void) :
    _vertexBufferID(0)
  {
    gl::glGenBuffers(1, &this->_vertexBufferID);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->_vertexBufferID);
    gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(float) * 65536, NULL, gl::GL_DYNAMIC_DRAW);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
  }

  Opengl3DRenderer::~Opengl3DRenderer(void)
  {
    gl::glDeleteBuffers(1, &this->_vertexBufferID);
  }

  void
  Opengl3DRenderer::draw(const glm::mat4 &projection, const glm::mat4 &modelview,
			 const std::vector<float> &vertex)
  {
    // std::cout << "Nombre de vertices : " << vertex.size() << std::endl;

    if (debug == 0)
      {
	std::cout << vertex.size() << std::endl;
    for (int i = 0 ; i < 12 ; i += 3)
      {
	// std::cout << vertex[i] << std::endl;
	glm::vec4 gl_Position = projection * modelview * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1.0f);
	std::cout << "[" << gl_Position.x << "][" << gl_Position.y << "][" << gl_Position.z << "]" << std::endl;
      }
      }
    debug = 1;

    this->_shader.bind();

    this->_shader.setUniform("projection", projection);
    this->_shader.setUniform("modelview", modelview);

    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->_vertexBufferID);
    gl::glBufferSubData(gl::GL_ARRAY_BUFFER, 0, sizeof(float) * vertex.size(), vertex.data());
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);


    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->_vertexBufferID);

    gl::glEnableVertexAttribArray(this->_shader.getAttributeLocation("position"));
    gl::glVertexAttribPointer(this->_shader.getAttributeLocation("position"), 3, gl::GL_FLOAT, gl::GL_FALSE, 0, 0);
    gl::glDrawArrays(gl::GL_TRIANGLE_STRIP, 0, vertex.size() / 3);
    gl::glEnableVertexAttribArray(this->_shader.getAttributeLocation("position"));

    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);

    this->_shader.unbind();
  }

}
