#ifndef         __PARTICLE_ENGINE_HPP__
# define        __PARTICLE_ENGINE_HPP__

#include <vector>
#include "../GameObject/GameObject.hpp"
#include "../../includes/glm/glm.hpp"

#include "../../includes/GDL/BasicShader.hh"
#include "../../includes/GDL/Texture.hh"
#include "../../includes/GDL/Geometry.hh"

#include "../../includes/glm/gtx/random.hpp"

#include "./Shape/Shape.hpp"
#include "./MinMaxValue/MinMaxValue.hpp"
#include "./Particle/Particle.hpp"

namespace   ParticleSystem
{
  enum    SimulationSpace
    {
      LOCAL,
      WORLD
    };

  struct  VelocityOverLifetime
  {
    MinMaxValueFloat    _x;
    MinMaxValueFloat    _y;
    MinMaxValueFloat    _z;
    SimulationSpace     _space;
  };

  struct      LimitVelocityOverLifetime
  {
    bool                _separateAxis;
    MinMaxValueFloat    _speed;
    float               _dampen;
  };

  struct      ForceOverLifetime
  {
    MinMaxValueFloat    _x;
    MinMaxValueFloat    _y;
    MinMaxValueFloat    _z;
    bool                _randomize;
    SimulationSpace     _space;
  };

  struct      ColorBySpeed
  {
    MinMaxValueColor            _color;
    std::pair<float, float>     _speedRange;
  };

  struct      SizeBySpeed
  {
    MinMaxValueFloat            _size;
    std::pair<float, float>     _speedRange;
  };

  struct      TextureSheetAnimation
  {
    std::pair<int, int>         _tiles;
    MinMaxValueFloat            _frameOverTimes;
  };

  class   ParticleEngine : public GameObject
  {

  public:
    enum    SimulationSpaceType
      {
	LOCAL,
	WORLD
      };

  private:
    struct      Emission
    {
      enum        Type
	{
	  DISTANCE,
	  TIME
	};
      /// Type of emission, DISTANCE or TIME
      Type                                    _type;
      /// number of emission per TIME or DISTANCE
      float                                   _rate;
      /// Emission is active ?
      bool                                    _actif;
      /// list of TIME
      std::list<std::pair<float, int> >       _list;
      std::list<std::pair<float, int> >       _listTmp;
      Emission(Emission::Type type = DISTANCE, float rate = 0.0f) : _type(type), _rate(rate), _actif(true) {}
    };

  public:
    ParticleEngine(const glm::vec3 &position,
		   const glm::vec3 &rotation,
		   const glm::vec3 &scale, unsigned int maxParticles);
    ~ParticleEngine(void);

  public:
    bool                                        initialize(void);
    bool                                        update(void);
    void                                        draw(glm::mat4 &, glm::mat4 &);


  public:
    float                                       getDuration(void) const { return this->_duration; }
    bool                                        isLooping(void) const { return this->_looping; }
    bool                                        getPrewarm(void) const { return this->_prewarm; }
    float                                       getStartDelay(void) const { return this->_startDelay; }
    const MinMaxValueFloat                      &getStartLifetime(void) const { return this->_startLifetime; }
    const MinMaxValueFloat                      &getStartSpeed(void) const { return this->_startSpeed; }
    const MinMaxValueFloat                      &getStartSize(void) const { return this->_startSize; }
    const MinMaxValueFloat                      &getStartRotation(void) const { return this->_startRotation; }
    const MinMaxValueColor                      &getStartColor(void) const { return this->_startColor; }
    unsigned int                                getMaxParticles(void) const { return this->_maxParticles; }

  public:
    void                                        setDuration(float duration) { this->_duration = duration; }
    void                                        setLooping(bool looping) { this->_looping = looping; }
    void                                        setPrewarm(bool prewarm) { this->_prewarm = prewarm; }
    void                                        setStartDelay(float startDelay) { this->_startDelay = startDelay; }
    void                                        setStartLifetime(const MinMaxValueFloat &startLifetime) { this->_startLifetime = startLifetime; }
    void                                        setStartSpeed(const MinMaxValueFloat &startSpeed) { this->_startSpeed = startSpeed; }
    void                                        setStartSize(const MinMaxValueFloat &startSize) { this->_startSize = startSize; }
    void                                        setStartRotation(const MinMaxValueFloat &startRotation) { this->_startRotation = startRotation; }
    void                                        setStartColor(const MinMaxValueColor &startColor) { this->_startColor = startColor; }
    void                                        setGravityMultiplier(float value) { this->_gravityMultiplier = value; }
    void                                        setInheritVelocity(float value) { this->_inheritVelocity = value; }
    void                                        setSimulationSpace(SimulationSpaceType type) { this->_simulationSpace = type; }
    void                                        setPlayOnAwake(bool value) { this->_playOnAwake = value; }
    void                                        setMaxParticles(unsigned int maxParticles) { this->_maxParticles = maxParticles; }
    void                                        setEmission(const Emission &emission) { this->_emission = emission; }
    void                                        setShape(Shape *shape) { this->_shape = shape; }
    void                                        setColorValueOverLifetime(const MinMaxValueColor &colorValueOverLifetime) { this->_colorValueOverLifetime = colorValueOverLifetime; }
    void                                        setSizeValueOverLifetime(const MinMaxValueFloat &sizeValueOverLifetime) { this->_sizeOverLifetime = sizeValueOverLifetime; }
    void                                        setRotationOverLifetime(const MinMaxValueFloat &rotationOverLifetime) { this->_rotationOverLifetime = rotationOverLifetime; }

  public:
    /// Remove all particles in the particle system.
    /// Parameters : boolean -> Clear all child particle systems as well.
    void                                        clear(bool = true);

    /// Pauses playing the particle system.
    /// Parameters : boolean -> Pause all child particle as well.
    void                                        pause(bool = true);

    /// Play the particle system.
    /// Parameters : boolean -> Play all child particle systems as well.
    void                                        play(bool = true);

    /// Stops playing the particle system.
    /// Parameters : boolean -> Stop all child particle systems as well.
    void                                        stop(bool = true);

    /// Return false if the particle system is done emitting particle and all particle are dead.
    bool                                        isAlive(void) const;

    /// Emit count particle in the particle system
    void                                        emit(int);

  private:
    void                                        emit(void);

  private:

    /// The length of time the Particle System is emitting particles, if the system is looping, this indicates the length of one cycle.
    float                                       _duration;

    /// If true, the emission cycle will repeat after the duration.
    bool                                        _looping;

    /// When played a prewarmed system will be in a state as if it had emitted one loop cycle. Can only be used if the system is looping.
    /// TODO
    bool                                        _prewarm;

    /// Delay in seconds that this Particle System will wait before emitting particles. Cannot be used together with a prewarmed looping system.
    float                                       _startDelay;

    /// Start lifetime in seconds, particle will die when its lifetime reaches 0.
    MinMaxValueFloat                            _startLifetime;

    /// The start speed of particles, applied in the starting direction.
    MinMaxValueFloat                            _startSpeed;

    /// The start size of particles.
    MinMaxValueFloat                            _startSize;

    /// The start rotation of particles in degrees.
    MinMaxValueFloat                            _startRotation;

    /// The start color of particles.
    MinMaxValueColor                            _startColor;

    /// Scales the gravity defined in Physics Manager
    float                                       _gravityMultiplier;

    /// Applies the current directional velocity of the Transform to newly emitted particles.
    float                                       _inheritVelocity;

    /// Makes particle positions simulate in worldspace or local space. In local space they stay relative to the Transfor Makes particle positions simulate in worldspace or local space. In local space they stay relative to the TTansform.
    SimulationSpaceType                         _simulationSpace;

    /// If enabled, the system will start playing automatically.
    bool                                        _playOnAwake;

    /// The number of particles in the system will be limited by this number. Emission will be temporarily halted if this is reached.
    unsigned int                                _maxParticles;

  private:
    Emission                                    _emission;
    Shape                                       *_shape;

    MinMaxValueColor                            _colorValueOverLifetime;
    MinMaxValueFloat                            _sizeOverLifetime;
    MinMaxValueFloat                            _rotationOverLifetime;
    TextureSheetAnimation                       _textureSheetAnimation;

  private:
    bool                                        _isRunning;
    float                                       _emitEnd;
    float                                       _totalTime;
    float                                       _actualDuration;
    float                                       _lastTime;
    bool                                        _existDrawingElement;
    glm::vec3                                   _lastPosition;
    std::vector<Particle *>                       _particles;
    std::list<ParticleEngine *>                 _particleEnginesChild;

  };
}
#endif
