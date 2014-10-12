#include "Shape.hpp"
#include "../../../includes/glm/gtc/random.hpp"

#include <iostream>

namespace   ParticleSystem
{

    Shape::Shape(bool randomDirection, bool isActive, Shape::Type type) :
        _isActive(isActive),
        _randomDirection(randomDirection),
        _type(type)
    {

    }



    BoxShape::BoxShape(const glm::vec3 &box, bool randomDirection, bool isActive) :
        Shape(randomDirection, isActive, Shape::BOX),
        _box(box)
    {

    }

    BoxShape::~BoxShape(void)
    {

    }

    void
    BoxShape::apply(glm::vec3 &position, glm::vec3 &force)
    {

        position.x += glm::linearRand(-this->_box.x / 2.0f, this->_box.x / 2.0f);
        position.y += glm::linearRand(-this->_box.y / 2.0f, this->_box.y / 2.0f);
        position.z += glm::linearRand(-this->_box.z / 2.0f, this->_box.z / 2.0f);

        if (this->_randomDirection == true)
        {
            force.x += glm::linearRand(-1.0f, 1.0f);
            force.y += glm::linearRand(-1.0f, 1.0f);
            force.z += glm::linearRand(-1.0f, 1.0f);
        }
        else
        {
            force += glm::vec3(0.0f, 0.0f, 1.0f);
        }

        force = glm::normalize(force);

    }



    SphereShape::SphereShape(float radius, bool emitFromShell, bool randomDirection, bool isActive) :
        Shape(randomDirection, isActive, Shape::SPHERE),
        _radius(radius),
        _emitFromShell(emitFromShell)
    {

    }

    SphereShape::~SphereShape(void)
    {

    }

    void
    SphereShape::apply(glm::vec3 &position, glm::vec3 &force)
    {
        glm::vec3   rand = this->_emitFromShell ? glm::sphericalRand(this->_radius) : glm::ballRand(this->_radius);

        position += rand;

        if (this->_randomDirection)
        {
            force.x += glm::linearRand(-1.0f, 1.0f);
            force.y += glm::linearRand(-1.0f, 1.0f);
            force.z += glm::linearRand(-1.0f, 1.0f);
        }
        else
        {
            force += rand;
        }

        force = glm::normalize(force);
    }



    HemisphereShape::HemisphereShape(float radius, bool emitFromShell, bool randomDirection, bool isActive) :
        SphereShape(radius, emitFromShell, randomDirection, isActive)
    {
        this->_type = Shape::HEMISPHERE;
    }

    HemisphereShape::~HemisphereShape(void)
    {

    }

    void
    HemisphereShape::apply(glm::vec3 &position, glm::vec3 &force)
    {
        glm::vec3   tmpPos(0.0f, 0.0f, 0.0f);
        glm::vec3   tmpForce(0.0f, 0.0f, 0.0f);

        this->SphereShape::apply(tmpPos, tmpForce);

        tmpPos.z = glm::abs(tmpPos.z);
        tmpForce.z = glm::abs(tmpForce.z);

        position += tmpPos;
        force += tmpForce;

    }



    ConeShape::ConeShape(float angle, float radius, float length, ConeShape::EmitFrom emitFrom,  bool randomDirection, bool isActive) :
        Shape(randomDirection, isActive, Shape::CONE),
        _angle(angle),
        _radius(radius),
        _length(length),
        _emitFrom(emitFrom)
    {

    }

    ConeShape::~ConeShape(void)
    {

    }

    void
    ConeShape::apply(glm::vec3 &position, glm::vec3 &force)
    {

        glm::vec2       rand = this->_emitFrom == ConeShape::BASE || this->_emitFrom == ConeShape::VOLUME ? glm::diskRand(this->_radius) : glm::circularRand(this->_radius);
        glm::vec2       ratio(rand.x / this->_radius, rand.y / this->_radius);

        position.x += rand.x;
        position.y += rand.y;

        force.z = 1.0f;
        force += glm::vec3(glm::sin(glm::radians(ratio.x * this->_angle)), glm::sin(glm::radians(ratio.y * this->_angle)), glm::cos(glm::radians(ratio.x * this->_angle)));

        force = glm::normalize(force);

        if (this->_emitFrom == ConeShape::VOLUME || this->_emitFrom == ConeShape::VOLUMESHELL)
            position += force * glm::linearRand(0.0f, this->_length);

    }

}
