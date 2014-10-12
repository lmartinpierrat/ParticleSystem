#ifndef     __MINMAXVALUE_EXCEPTION_HPP__
# define    __MINMAXVALUE_EXCEPTION_HPP__

namespace   ParticleSystem
{
    class   MinMaxValueException : public ParticleSystemException
    {
        public:
            MinMaxValueException(const std::string &error) : ParticleSystemException("[MinMaxValue]" + error) { }
    };
}

#endif

