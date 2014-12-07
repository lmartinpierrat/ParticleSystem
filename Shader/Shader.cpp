//
// Shader.cpp for Shader in /Utility/Shader
// 
// Made by Louis Martin-Pierrat
// Login   <mart_p@epitech.net>
// 
// Started on  Sat Sep 27 20:08:10 2014 Louis Martin-Pierrat
// Last update Mon Oct  6 17:21:41 2014 Louis Martin-Pierrat
//

#include	"Shader.hpp"
#include	<sstream>
#include	<fstream>

//------------------------------------------------------
//
//------------------------------------------------------
Shader::Shader(void) : _programID(0), _fragmentShaderID(0), _vertexShaderID(0)
{
}

//------------------------------------------------------
// Free Shaders and Program if they are alive yet.
//------------------------------------------------------
Shader::~Shader(void)
{
  if (this->_vertexShaderID != 0)
    {
      gl::glDetachShader(this->_programID, this->_vertexShaderID);
      gl::glDeleteShader(this->_vertexShaderID);
    }
  if (this->_fragmentShaderID != 0)
    {
      gl::glDetachShader(this->_programID, this->_fragmentShaderID);
      gl::glDeleteShader(this->_fragmentShaderID);
    }
  if (this->_programID != 0)
    {
      gl::glDeleteProgram(this->_programID);
    }
}

//------------------------------------------------------
// Open and check filename, and use loadFromMemory to import them.
//------------------------------------------------------
bool
Shader::loadFromFile(const std::string &filename, gl::GLenum type)
{
  std::ifstream		ifs(filename);
  std::stringstream	ss;

  if (!ifs) return (false);
  ss << ifs.rdbuf();
  return (this->loadFromMemory(ss.str(), type));
}

//------------------------------------------------------
// Open and check vertex & shader filename, and use loadFromMemory to import them.
//------------------------------------------------------
bool
Shader::loadFromFile(const std::string &vertexShaderFilename,
		     const std::string &fragmentShaderFilename)
{
  std::ifstream		ifs1(vertexShaderFilename);
  std::ifstream		ifs2(fragmentShaderFilename);
  std::stringstream	ss1;
  std::stringstream	ss2;

  if (!ifs1 || !ifs2) return (false);
  ss1 << ifs1.rdbuf();
  ss2 << ifs2.rdbuf();
  return (this->loadFromMemory(ss1.str(), ss2.str()));
}

//------------------------------------------------------
//
//------------------------------------------------------
bool
Shader::loadFromMemory(const std::string &shader, gl::GLenum type)
{
  const char	*shaderData = shader.c_str();
  gl::GLuint	&shaderID = (type == gl::GL_FRAGMENT_SHADER ?
			     this->_fragmentShaderID : this->_vertexShaderID);

  if (shaderID != 0) this->deleteShader(shaderID);
  shaderID = gl::glCreateShader(type);
  gl::glShaderSource(shaderID, 1, (const gl::GLchar**)&shaderData, NULL);
  gl::glCompileShader(shaderID);
  if (this->checkShaderCompilation(shaderID) == false)
    return (false);
  if (this->_programID == 0) this->_programID = gl::glCreateProgram();
  gl::glAttachShader(this->_programID, shaderID);
  gl::glLinkProgram(this->_programID);
  return (this->checkProgramLink());
}

//------------------------------------------------------
//
//------------------------------------------------------
bool
Shader::loadFromMemory(const std::string &vertexShader,
		       const std::string &fragmentShader)
{
  const char	*vertexData = vertexShader.c_str();
  const char	*fragmentData = fragmentShader.c_str();

  if (this->_fragmentShaderID != 0) this->deleteShader(this->_fragmentShaderID);
  if (this->_vertexShaderID != 0) this->deleteShader(this->_vertexShaderID);
  this->_vertexShaderID = gl::glCreateShader(gl::GL_VERTEX_SHADER);
  gl::glShaderSource(this->_vertexShaderID, 1, &vertexData, NULL);
  gl::glCompileShader(this->_vertexShaderID);
  if (this->checkShaderCompilation(this->_vertexShaderID) == false) return (false);
  this->_fragmentShaderID = gl::glCreateShader(gl::GL_FRAGMENT_SHADER);
  gl::glShaderSource(this->_fragmentShaderID, 1, &fragmentData, NULL);
  gl::glCompileShader(this->_fragmentShaderID);
  if (this->checkShaderCompilation(this->_fragmentShaderID) == false) return (false);
  if (this->_programID == 0) this->_programID = gl::glCreateProgram();
  gl::glAttachShader(this->_programID, this->_vertexShaderID);
  gl::glAttachShader(this->_programID, this->_fragmentShaderID);
  gl::glLinkProgram(this->_programID);
  return (this->checkProgramLink());
}

//------------------------------------------------------
//
//------------------------------------------------------
bool
Shader::checkShaderCompilation(gl::GLuint shaderID)
{
  gl::GLint isCompiled;

  gl::glGetShaderiv(shaderID, gl::GL_COMPILE_STATUS, &isCompiled);
  if (!isCompiled)
    {
      gl::GLint		logLength = 0;
      gl::glGetShaderiv(shaderID, gl::GL_INFO_LOG_LENGTH, &logLength);
      gl::GLchar	message[logLength];
      gl::glGetShaderInfoLog(shaderID, logLength, &logLength, message);
      std::cerr << "[ERROR SHADER COMPILATION]" << std::endl
		<< message << std::endl;
      return (false);
    }
  return (true);
}

//------------------------------------------------------
//
//------------------------------------------------------
bool
Shader::checkProgramLink(void)
{
  gl::GLint	programLinked;

  gl::glGetProgramiv(this->_programID, gl::GL_LINK_STATUS, &programLinked);
  if (!programLinked)
    {
      gl::GLint		logLength = 0;
      gl::glGetProgramiv(this->_programID, gl::GL_INFO_LOG_LENGTH, &logLength);
      gl::GLchar	message[logLength];
      gl::glGetProgramInfoLog(this->_programID, logLength, &logLength, message);
      std::cerr << "[ERROR PROGRAM LINKAGE]" << std::endl
		<< message << std::endl;
      return (false);
    }
  return (true);
}
