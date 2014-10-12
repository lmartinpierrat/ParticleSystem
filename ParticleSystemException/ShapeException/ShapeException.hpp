#ifndef     __SHAPE_EXCEPTION_HPP__
# define    __SHAPE_EXCEPTION_HPP_

#include    <string>
#include    "../ParticleSystemException.hpp"

namespace   ParticleSystem
{

    class   ShapeException : public ParticleSystemException
    {
        public:
            ShapeException(const std::string &error) : ParticleSystemException("[Shape]" + error) { }
    };

}

#endif

