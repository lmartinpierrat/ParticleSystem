#ifndef     __PARTICLE_EXCEPTION_HPP__
# define    __PARTICLE_EXCEPTION_HPP__

#include    <string>
#include    "../ParticleSystemException.hpp"

namespace   ParticleSystem
{

    class       ParticleException : public ParticleSystemException
    {
        public:
            explicit ParticleException(const std::string &error) : ParticleSystemException("[Particle]" + error) { }
    };

}

#endif
