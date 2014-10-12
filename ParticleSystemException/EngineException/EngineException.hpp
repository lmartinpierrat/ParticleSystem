#ifndef     __ENGINE_EXCEPTION_HPP__
# define    __ENGINE_EXCEPTION_HPP__

#include    <string>
#include    "../ParticleSystemException.hpp"

namespace   ParticleSystem
{

    class   EngineException : public ParticleSystemException
    {
        public:
            explicit EngineException(const std::string &error) : ParticleSystemException("[Engine]" + error) { }
    };

}

#endif
