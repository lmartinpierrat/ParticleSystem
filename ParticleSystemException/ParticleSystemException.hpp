#ifndef     __PARTICLE_SYSTEM_EXCEPTION_HPP__
# define    __PARTICLE_SYSTEM_EXCEPTION_HPP__

#include <string>
#include <stdexcept>

namespace   ParticleSystem
{

    class       ParticleSystemException : public runtime_error
    {
        public:
            explicit ParticleSystemException(const std::string &error) : runtime_error("[ParticleSystem]" + error) { }
    };

}

#endif

