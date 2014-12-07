#define		GLM_FORCE_RADIANS
#include	<glm/gtx/transform.hpp>
#include	"Particle.hpp"

#include	<glm/common.hpp> // a supprimer
#include	<iostream> // a supprimer

namespace	ParticleSystem
{

  //----------------------------------------
  // Constructor
  //
  // @param :
  // position : represent the position of the particle in the world
  // rotation : represent the rotation of the particle in the world
  // scale : represent the size of the particle in XYZ axis.
  //----------------------------------------
  Particle::Particle(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) :
    _position(position),
    _rotation(rotation),
    _scale(scale)
  {

  }

  //----------------------------------------
  // Update is the function you need to call each frame with the time elapsed
  // between the two last frame for update the particle position in the scene.
  //
  // Thread safe
  //----------------------------------------
  void
  Particle::update(float elapsedTime)
  {
    this->_lifetime -= elapsedTime;
    this->_position += this->_force * elapsedTime;

    // this->_rotation.y = glm::mod(this->_rotation.y + 0.01f, 360.0f);
    this->_scale.x += 0.001f;
    this->_scale.y += 0.001f;
    this->_scale.z += 0.001f;
  }

  //----------------------------------------
  // draw is the function you need to call when you want to get vertex / uvs / color of the particle
  // in the scene.
  // 
  // @param:
  // modelview : represent the referencial matrix used to position the particle system in the world.
  //
  // Thread safe
  //----------------------------------------
  void
  Particle::draw(const glm::vec3 &camPosition, std::vector<float> &vertex)
  {
    glm::mat4   ModelView(1);

    ModelView = glm::translate(ModelView, this->_position);

    /* A REVOIR */
    ModelView *= lookAt(camPosition, glm::vec3(0.0f, 0.0f, 0.0f));
    ModelView = glm::rotate(ModelView, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    /* A REVOIR */

    ModelView = glm::rotate(ModelView, this->_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    ModelView = glm::scale(ModelView, this->_scale);

    glm::vec4	vector = ModelView * glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f);
    vertex.push_back(vector.x); vertex.push_back(vector.y); vertex.push_back(vector.z);
    vector = ModelView * glm::vec4(0.5f, 0.0f, -0.5f, 1.0f);
    vertex.push_back(vector.x); vertex.push_back(vector.y); vertex.push_back(vector.z);
    vector = ModelView * glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f);
    vertex.push_back(vector.x); vertex.push_back(vector.y); vertex.push_back(vector.z);
    vector = ModelView * glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);
    vertex.push_back(vector.x); vertex.push_back(vector.y); vertex.push_back(vector.z);
  }

  //----------------------------------------
  // A REVOIR
  //----------------------------------------
  glm::mat4
  Particle::lookAt(const glm::vec3 &targetPosition, const glm::vec3 &objectPosition)
  {
    glm::vec3 delta = targetPosition - objectPosition;
    glm::vec3 up;
    glm::vec3 direction(glm::normalize(delta));

    if (glm::abs(direction.x) < 0.00001 && glm::abs(direction.z) < 0.00001) {
      if (direction.y > 0) {
	up = glm::vec3(0.0, 0.0, -1.0); //if direction points in +y
      }
      else {
	up = glm::vec3(0.0, 0.0, 1.0); //if direction points in -y
      }
    }
    else {
      up = glm::vec3(0.0, 1.0, 0.0); //y-axis is the general up
    }

    up = glm::normalize(up);
    glm::vec3 right = glm::normalize(glm::cross(up,direction));
    up = glm::normalize(glm::cross(direction, right));
    return glm::mat4(right.x, right.y, right.z, 0.0f,
		     up.x, up.y, up.z, 0.0f,
		     direction.x, direction.y, direction.z, 0.0f,
		     objectPosition.x, objectPosition.y, objectPosition.z, 1.0f);
  }
  
}
