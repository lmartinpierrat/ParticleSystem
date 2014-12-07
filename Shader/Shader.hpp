//
// Shader.hpp for Shader in /Utility/Shader
// 
// Made by Louis Martin-Pierrat
// Login   <mart_p@epitech.net>
// 
// Started on  Sat Sep 27 19:56:32 2014 Louis Martin-Pierrat
// Last update Mon Oct  6 17:21:45 2014 Louis Martin-Pierrat
//

#ifndef		__SHADER_HPP__
# define	__SHADER_HPP__

#include	<string>
#include	<glbinding/gl/gl.h>
#define		GLM_FORCE_RADIANS
#include	<glm/gtc/type_ptr.hpp>
#include	<glm/vec2.hpp>
#include	<glm/vec3.hpp>

class	Shader
{

public:

  //------------------------------------------------------
  // Default constructor
  //------------------------------------------------------
  Shader(void);

  //------------------------------------------------------
  // destructor
  //------------------------------------------------------
  ~Shader(void);

public:

  //------------------------------------------------------
  // Bind the shader.
  //------------------------------------------------------
  void			bind(void)
  {
    gl::glUseProgram(this->_programID);
  }

  //------------------------------------------------------
  // Unbind the shader.
  //------------------------------------------------------
  void			unbind(void)
  {
    gl::glUseProgram(0);
  }

  int			getAttributeLocation(const std::string &name)
  {
    return (gl::glGetAttribLocation(this->_programID, name.c_str()));
  }

  //------------------------------------------------------
  // Load either the vertex or fragment shader from a file.
  //------------------------------------------------------
  bool			loadFromFile(const std::string &filename, gl::GLenum type);

  //------------------------------------------------------
  // Load both the vertex and fragment shaders from files.
  //------------------------------------------------------
  bool			loadFromFile(const std::string &vertexShaderFilename,
				     const std::string &fragmentShaderFilename);

  //------------------------------------------------------
  // Load either the vertex or fragment shader from a source code in memory.
  //------------------------------------------------------
  bool			loadFromMemory(const std::string &shader, gl::GLenum type);

  //------------------------------------------------------
  // Load both the vertex and fragment shaders from source codes in memory. 
  //------------------------------------------------------
  bool			loadFromMemory(const std::string &vertexShader, const std::string &fragmentShader);

  //------------------------------------------------------
  // Change a float parameter of the shader. 
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLfloat x)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform1f(location, x);
  }

  //------------------------------------------------------
  // Change a 2 float components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLfloat x, gl::GLfloat y)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform2f(location, x, y);
  }

  //------------------------------------------------------
  // Change a 3 float components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform3f(location, x, y, z);
  }

  //------------------------------------------------------
  // Change a 4 float components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat w)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform4f(location, x, y, z, w);
  }

  //------------------------------------------------------
  // Change a int parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLint x)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform1i(location, x);
  }

  //------------------------------------------------------
  // Change a 2 int components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLint x, gl::GLint y)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform2i(location, x, y);
  }

  //------------------------------------------------------
  // Change a 3 int components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLint x, gl::GLint y, gl::GLint z)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform3i(location, x, y, z);
  }

  //------------------------------------------------------
  // Change a 4 int components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLint x, gl::GLint y, gl::GLint z, gl::GLint w)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform4i(location, x, y, z, w);
  }

  //------------------------------------------------------
  // Change a uint parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLuint x)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform1ui(location, x);
  }

  //------------------------------------------------------
  // Change a 2 uint components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLuint x, gl::GLuint y)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform2ui(location, x, y);
  }

  //------------------------------------------------------
  // Change a 3 uint components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLuint x, gl::GLuint y, gl::GLuint z)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform3ui(location, x, y, z);
  }

  //------------------------------------------------------
  // Change a 4 uint components vector parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, gl::GLuint x, gl::GLuint y, gl::GLuint z, gl::GLuint w)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniform4ui(location, x, y, z, w);
  }

  //------------------------------------------------------
  // Change a mat2 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat2 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix2fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat3 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat3 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix3fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat4 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat4 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix4fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat2x3 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat2x3 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix2x3fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat3x2 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat3x2 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix3x2fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat2x4 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat2x4 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix2x4fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat4x2 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat4x2 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix4x2fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat4x2 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat3x4 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix3x4fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

  //------------------------------------------------------
  // Change a mat4x2 uniform parameter of the shader.
  //------------------------------------------------------
  void			setUniform(const std::string &name, const glm::mat4x3 &matrix)
  {
    gl::GLint location = gl::glGetUniformLocation(this->_programID, name.c_str());
    gl::glUniformMatrix4x3fv(location, 1, gl::GL_FALSE, glm::value_ptr(matrix));
  }

private:

  //------------------------------------------------------
  //
  //------------------------------------------------------
  void			deleteShader(gl::GLuint shaderID)
  {
    gl::glDetachShader(this->_programID, shaderID);
    gl::glDeleteShader(shaderID);
  }

  //------------------------------------------------------
  //
  //------------------------------------------------------
  bool			checkShaderCompilation(gl::GLuint shaderID);

  //------------------------------------------------------
  //
  //------------------------------------------------------
  bool			checkProgramLink(void);

private:
  //------------------------------------------------------
  //
  //------------------------------------------------------
  gl::GLuint	_programID;

  //------------------------------------------------------
  // 
  //------------------------------------------------------
  gl::GLuint	_fragmentShaderID;

  //------------------------------------------------------
  // 
  //------------------------------------------------------
  gl::GLuint	_vertexShaderID;

};

#endif /* __SHADER_HPP__ */
