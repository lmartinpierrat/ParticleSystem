#include "ParticleEngine.hpp"
#include "../Clock/Clock.hpp"


#include <cmath> // VALUEBETWEENTWOCONSTANTS
#include <algorithm>

#include <iostream>
#include "../Library/GeometryLibrary/GeometryLibrary.hpp"
#include "../Library/ShaderLibrary/ShaderLibrary.hpp"
#include "../Library/TextureLibrary/TextureLibrary.hpp"
#include <sys/time.h>

/*
 * Include limit ?
 * */

/* MIN MAX VALUE START  */

namespace   ParticleSystem
{

  /*
   *
   * */
  ParticleEngine::ParticleEngine(const glm::vec3 &position, const glm::vec3 &rotation,
				 const glm::vec3 &scale, unsigned int maxParticles) :
    GameObject(position, rotation, scale),
    _maxParticles(maxParticles)
  {
    this->_particles.reserve(this->_maxParticles);
    this->_totalTime = 0.0f;
    this->initialize();
  }

  ParticleEngine::~ParticleEngine(void)
  {
    while (!this->_particles.empty())
      {
	delete this->_particles.back();
	this->_particles.pop_back();
      }

    while (!this->_particleEnginesChild.empty())
      {
        delete this->_particleEnginesChild.back();
        this->_particleEnginesChild.pop_back();
      }
  }

  void
  ParticleEngine::clear(bool withChildren)
  {
    this->initialize();
    while (!this->_particles.empty())
      {
        delete this->_particles.back();
        this->_particles.pop_back();
      }
    if (withChildren == true)
      {
        for (std::list<ParticleEngine *>::iterator it = this->_particleEnginesChild.begin() ; it != this->_particleEnginesChild.end() ; ++it)
	  {
            (*it)->clear(true);
	  }

        while (!this->_particleEnginesChild.empty())
	  {
            delete this->_particleEnginesChild.back();
            this->_particleEnginesChild.pop_back();
	  }
      }
  }

  void
  ParticleEngine::pause
  (bool withChildren)
  {
    this->_isRunning = false;

    if (withChildren == true)
      {
        for (std::list<ParticleEngine *>::iterator it = this->_particleEnginesChild.begin() ; it != this->_particleEnginesChild.end() ; ++it)
	  {
            (*it)->pause(true);
	  }
      }
  }

  void
  ParticleEngine::play
  (bool withChildren)
  {
    this->_isRunning = true;
    if (withChildren == true)
      {
        for (std::list<ParticleEngine *>::iterator it = this->_particleEnginesChild.begin() ; it != this->_particleEnginesChild.end() ; ++it)
	  {
            (*it)->play(true);
	  }
      }
  }

  void
  ParticleEngine::stop(bool withChildren)
  {
    this->clear(withChildren);
    this->_isRunning = false;
  }

  bool
  ParticleEngine::isAlive(void) const
  {
    return !(this->_particles.empty() == true && this->_looping == false && this->_actualDuration > this->_duration);
  }

  bool
  ParticleEngine::initialize(void)
  {
    this->_isRunning = this->_playOnAwake;
    this->_actualDuration = 0.0f;
    this->_existDrawingElement = false;
    this->_lastTime = 0.0f;
    return true;
  }

  void
  ParticleEngine::emit(void)
  {
    float	elapsedTime = Clock::getInstance()->getElapsed();

    if (this->_emission._type == ParticleEngine::Emission::TIME)
      {
        this->_lastTime += elapsedTime;
        if (this->_emission._rate != 0.0f && this->_lastTime >= 1.0f / this->_emission._rate)
	  {
            this->emit(1);
            this->_lastTime = 0.0f;
	  }

        for (std::list<std::pair<float, int> >::iterator it = this->_emission._list.begin() ; it != this->_emission._list.end() ; )
	  {
            if (this->_actualDuration - elapsedTime < (*it).first && this->_actualDuration + elapsedTime > (*it).first)
	      {
                this->emit((*it).second);
                this->_emission._listTmp.push_back((*it));
                it = this->_emission._list.erase(it);
	      }
            else
	      {
                ++it;
	      }
	  }

        //
        // WORK HERE
        //
      }
    else
      {
      }
  }

  void
  ParticleEngine::emit(int count)
  {
    glm::vec3   position;
    glm::vec3   rotation;
    glm::vec3   scale;
    glm::vec3   force;
    float       tmp;

    for (int i = 0 ; i < count ; ++i)
      {
        if (this->_particles.size() >= this->_maxParticles)
	  break;
        if (this->_simulationSpace == ParticleEngine::WORLD)
	  {
            position = this->_position;
            rotation = this->_rotation;
            scale = this->_scale;
	  }
        else
	  {
            position = glm::vec3(0.0f, 0.0f, 0.0f);
            rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            scale = glm::vec3(0.0f, 0.0f, 0.0f);
	  }
        this->_shape->apply(position, force);
        rotation += glm::vec3(0.0f, this->_startRotation.getValue(), 0.0f);
        tmp = this->_startSize.getValue();
        scale = glm::vec3(tmp, tmp, tmp);
        this->_particles.push_back(new Particle(position, rotation, scale,
						this->_startLifetime.getValue(),
						this->_startSpeed.getValue(),
						this->_startColor.getValue(),
						this->_gravityMultiplier,
						force,
						this->_colorValueOverLifetime,
						this->_sizeOverLifetime,
						this->_rotationOverLifetime));
      }
  }


  bool
  ParticleEngine::update
  (void)
  {
    float       elapsedTime = Clock::getInstance()->getElapsed();

    if (this->_isRunning == true)
      {
        if (this->_startDelay <= 0.0f)
	  {
            if (this->_actualDuration > this->_duration && this->_looping == false)
	      {
                while (!this->_particles.empty())
		  {
                    delete this->_particles.back();
                    this->_particles.pop_back();
		  }
                this->_existDrawingElement = false;
                this->_isRunning = false;
                return true;
	      }
            else if (this->_actualDuration > this->_duration)
	      {
                this->_actualDuration = 0.0f;
                this->_emission._list.insert(this->_emission._list.begin(), this->_emission._listTmp.begin(), this->_emission._listTmp.end());
                this->_emission._listTmp.clear();
	      }
            if (this->_emitEnd < 0.0f || this->_emitEnd > this->_totalTime) this->emit();
            for (std::vector<Particle *>::iterator it = this->_particles.begin() ; it != this->_particles.end() ; )
	      {
                if (!(*it)->isAlive())
		  {
                    delete (*it);
                    it = this->_particles.erase(it);
		  }
                else
		  {
                    (*it)->update();
                    ++it;
		  }
	      }
            this->_actualDuration += elapsedTime;
            this->_totalTime += elapsedTime;
            this->_existDrawingElement = true;
	  }
        else
	  {
            this->_startDelay -= elapsedTime;
	  }
      }

    for (std::list<ParticleEngine *>::iterator it = this->_particleEnginesChild.begin() ; it != this->_particleEnginesChild.end() ; ++it)
      {
        (*it)->update();
      }

    return true;
  }

  void
  ParticleEngine::draw(glm::mat4 &projection, glm::mat4 &modelview)
  {
    glm::mat4   pmodelview = modelview;

    if (this->_simulationSpace == ParticleEngine::LOCAL)
      {
        modelview = glm::rotate(modelview, this->_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        modelview = glm::rotate(modelview, this->_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, this->_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        modelview = glm::translate(modelview, this->_position);
        modelview = glm::scale(modelview, this->_scale);
      }

    if (this->_existDrawingElement == true)
      {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glBlendEquation(GL_FUNC_ADD);

        for (std::vector<Particle *>::iterator it = this->_particles.begin() ; it != this->_particles.end() ; ++it)
	  {
            (*it)->draw(projection, modelview);
	  }

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

      }

    for (std::list<ParticleEngine *>::iterator it = this->_particleEnginesChild.begin() ; it != this->_particleEnginesChild.end() ; ++it)
      {
        (*it)->draw(projection, modelview);
      }

    modelview = pmodelview;
  }

}
