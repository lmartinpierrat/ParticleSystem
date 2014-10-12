#include "MinMaxValue.hpp"
#include "../../../includes/glm/gtc/random.hpp"

#include <iostream>

namespace   ParticleSystem
{

    MinMaxValueFloat::MinMaxValueFloat(Type type, float value1, float value2) :
        _value1(value1),
        _value2(value2),
        _type(type)
    {

    }

    MinMaxValueFloat::MinMaxValueFloat(Type type, const std::vector<std::pair<float, float> > &curve1, const std::vector<std::pair<float, float> > &curve2) :
        _curve1(curve1),
        _curve2(curve2),
        _type(type)
    {

    }

    MinMaxValueFloat::~MinMaxValueFloat(void)
    {

    }

    MinMaxValueFloat &
    MinMaxValueFloat::operator=(const MinMaxValueFloat &a)
    {
        this->_value1 = a._value1;
        this->_value2 = a._value2;
        this->_curve1 = a._curve1;
        this->_curve2 = a._curve2;
        this->_type = a._type;
        return *this;
    }

    float
    MinMaxValueFloat::getValue(float percentage) const
    {
        if (this->_type == MinMaxValueFloat::CONSTANT)
        {
            return this->_value1;
        }
        else if (this->_type == MinMaxValueFloat::RANDOMBETWEENTWOCONSTANTS)
        {
            return glm::linearRand(this->_value1, this->_value2);
        }
        else if (this->_type == MinMaxValueFloat::CURVE)
        {
            for (std::vector<std::pair<float, float> >::const_iterator S = this->_curve1.begin(), P = S++ ; P != this->_curve1.end() && S != this->_curve1.end() ; ++S, ++P)
            {
                if (percentage >= (*P).first && percentage <= (*S).first)
                {
                    float tmp = (*S).first - percentage;
                    return glm::min((*P).second, (*S).second) + glm::abs((*P).second - (*S).second) * tmp;
                }
            }
        }
        else
        {
            float   value1 = 0.0f;
            float   value2 = 0.0f;

            for (std::vector<std::pair<float, float> >::const_iterator S = this->_curve1.begin(), P = S++ ; P != this->_curve1.end() && S != this->_curve1.end() ; ++S, ++P)
            {
                if (percentage >= (*P).first && percentage <= (*S).first)
                {
                    float tmp = (*S).first - percentage;
                    value1 = glm::min((*P).second, (*S).second) + glm::abs((*P).second - (*S).second) * tmp;
                }
            }
            for (std::vector<std::pair<float, float> >::const_iterator S = this->_curve2.begin(), P = S++ ; P != this->_curve2.end() && S != this->_curve2.end() ; ++S, ++P)
            {
                if (percentage >= (*P).first && percentage <= (*S).first)
                {
                    float tmp = (*S).first - percentage;
                    value2 = glm::min((*P).second, (*S).second) + glm::abs((*P).second - (*S).second) * tmp;
                }
            }
            return glm::linearRand(value1, value2);
        }
        return 0.0f;
    }


    MinMaxValueColor::MinMaxValueColor(Type type, const glm::vec4 &color1, const glm::vec4 &color2) :
        _color1(color1),
        _color2(color2),
        _type(type)
    {

    }

    MinMaxValueColor::MinMaxValueColor(Type type, const std::vector<std::pair<float, glm::vec4> > &gradiant1, const std::vector<std::pair<float, glm::vec4> > &gradiant2) :
        _gradiant1(gradiant1),
        _gradiant2(gradiant2),
        _type(type)
    {

    }

    MinMaxValueColor::~MinMaxValueColor(void)
    {

    }

    MinMaxValueColor &
    MinMaxValueColor::operator=(const MinMaxValueColor &a)
    {
        this->_gradiant1 = a._gradiant1;
        this->_gradiant2 = a._gradiant2;
        this->_color1 = a._color1;
        this->_color2 = a._color2;
        this->_type = a._type;
        return *this;
    }

    glm::vec4
    MinMaxValueColor::getValue(float percentage) const
    {
        // passer les fonctiosn getvalue en ptr fonction pour les types
        if (this->_type == MinMaxValueColor::COLOR)
        {
            return this->_color1;
        }
        else if (this->_type == MinMaxValueColor::GRADIANT)
        {
            for (std::vector<std::pair<float, glm::vec4> >::const_iterator S = this->_gradiant1.begin(), P = S++ ; P != this->_gradiant1.end() && S != this->_gradiant1.end() ; ++S, ++P)
            {
                if (percentage >= (*P).first && percentage <= (*S).first)
                {
                    float tmp = (*S).first - percentage;
                    return glm::vec4(   glm::min((*P).second.x, (*S).second.x) + glm::abs((*P).second.x - (*S).second.x) * tmp,
                                        glm::min((*P).second.y, (*S).second.y) + glm::abs((*P).second.y - (*S).second.y) * tmp,
                                        glm::min((*P).second.z, (*S).second.z) + glm::abs((*P).second.z - (*S).second.z) * tmp,
                                        glm::min((*P).second.w, (*S).second.w) + glm::abs((*P).second.w - (*S).second.w) * tmp);
                }
            }
        }
        else if (this->_type == MinMaxValueColor::RANDOMBETWEENTWOCOLORS)
        {
            float   tmp = glm::linearRand(0.0f, 1.0f);
            return glm::vec4(glm::min(this->_color1.x, this->_color2.x) + glm::abs(this->_color1.x - this->_color2.x) * tmp,
                    glm::min(this->_color1.y, this->_color2.y) + glm::abs(this->_color1.y - this->_color2.y) * tmp,
                    glm::min(this->_color1.z, this->_color2.z) + glm::abs(this->_color1.z - this->_color2.z) * tmp,
                    glm::min(this->_color1.w, this->_color2.w) + glm::abs(this->_color1.w - this->_color2.w) * tmp);
        }
        else
        {
            glm::vec4   colorGradiant1;
            glm::vec4   colorGradiant2;

            for (std::vector<std::pair<float, glm::vec4> >::const_iterator S = this->_gradiant1.begin(), P = S++ ; P != this->_gradiant1.end() && S != this->_gradiant1.end() ; ++S, ++P)
            {
                if (percentage >= (*P).first && percentage <= (*S).first)
                {
                    float tmp = (*S).first - percentage;
                    colorGradiant1 = glm::vec4(   glm::min((*P).second.x, (*S).second.x) + glm::abs((*P).second.x - (*S).second.x) * tmp,
                                        glm::min((*P).second.y, (*S).second.y) + glm::abs((*P).second.y - (*S).second.y) * tmp,
                                        glm::min((*P).second.z, (*S).second.z) + glm::abs((*P).second.z - (*S).second.z) * tmp,
                                        glm::min((*P).second.w, (*S).second.w) + glm::abs((*P).second.w - (*S).second.w) * tmp);
                }
            }
            for (std::vector<std::pair<float, glm::vec4> >::const_iterator S = this->_gradiant2.begin(), P = S++ ; P != this->_gradiant2.end() && S != this->_gradiant2.end() ; ++S, ++P)
            {
                if (percentage >= (*P).first && percentage <= (*S).first)
                {
                    float tmp = (*S).first - percentage;
                    colorGradiant2 = glm::vec4(   glm::min((*P).second.x, (*S).second.x) + glm::abs((*P).second.x - (*S).second.x) * tmp,
                                        glm::min((*P).second.y, (*S).second.y) + glm::abs((*P).second.y - (*S).second.y) * tmp,
                                        glm::min((*P).second.z, (*S).second.z) + glm::abs((*P).second.z - (*S).second.z) * tmp,
                                        glm::min((*P).second.w, (*S).second.w) + glm::abs((*P).second.w - (*S).second.w) * tmp);
                }
            }
            float   tmp = glm::linearRand(0.0f, 1.0f);
            return glm::vec4(   glm::min(colorGradiant1.x, colorGradiant2.x) + glm::abs(colorGradiant1.x - colorGradiant2.x) * tmp,
                                glm::min(colorGradiant1.y, colorGradiant2.y) + glm::abs(colorGradiant1.y - colorGradiant2.y) * tmp,
                                glm::min(colorGradiant1.z, colorGradiant2.z) + glm::abs(colorGradiant1.z - colorGradiant2.z) * tmp,
                                glm::min(colorGradiant1.w, colorGradiant2.w) + glm::abs(colorGradiant1.w - colorGradiant2.w) * tmp);

        }
        return this->_color1;
    }



}
