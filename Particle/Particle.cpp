#include "Particle.hpp"
#include "../../Clock/Clock.hpp"
#include "../../Library/GeometryLibrary/GeometryLibrary.hpp"
#include "../../Library/ShaderLibrary/ShaderLibrary.hpp"
#include "../../Library/TextureLibrary/TextureLibrary.hpp"
#include "../../../includes/glm/gtc/constants.hpp"

#include "../ParticleSystemException/ParticleSystemException.hpp"

namespace   ParticleSystem
{

    Particle::Particle(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) :
        _position(position),
        _rotation(rotation),
        _scale(scale),
        _lifetime(0.0f),
    {
        this->_actualLifetime = 0.0f;
        this->_texture = TextureLibrary::getInstance()->getValue("./Assets/Textures/default-particle.tga");
        this->_shader = ShaderLibrary::getInstance()->getValue("./Shaders/basic.fp", "./Shaders/basic.vp");
        this->_geometry = GeometryLibrary::getInstance()->getValue("Plan");
    }

    Particle::~Particle(void)
    {
    }

    bool
    Particle::update(void)
    {
        float   elapsedTime = Clock::getInstance()->getElapsed();
        float   tmp = this->_sizeOverLifetime.getValue(this->_actualLifetime / this->_lifetime);

        if (elapsedTime <= 0.0f)
        {
            throw ParticleException("Elapsed time equal or lower than zero.");
        }

        this->_actualLifetime += elapsedTime;
        this->_position += this->_force * (this->_speed / (1.0f / elapsedTime));
        this->_color = this->_colorOverLifetime.getValue(this->_actualLifetime / this->_lifetime);
        this->_rotation.y += this->_rotationOverLifetime.getValue(this->_actualLifetime / this->_lifetime) / (1.0f / elapsedTime);
        this->_scaleWithGrowth = this->_scale * tmp;
        return true;
    }

    void
    Particle::draw(glm::mat4 &projection, glm::mat4 &modelview)
    {
        glm::mat4   transform(1);

        transform = glm::translate(transform, this->_position);
        transform *= this->lookAt(glm::vec3(-20.0f, -20.0f, 6.0f), glm::zero<glm::vec3>());
        transform = glm::rotate(transform, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, this->_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, this->_scaleWithGrowth);

        this->_shader->bind();
        this->_shader->setUniform("projection", projection);
        this->_shader->setUniform("view", modelview);
        this->_shader->setUniform("mvColor", this->_color);
        this->_texture->bind();
        this->_geometry->draw(*this->_shader, transform, GL_QUADS);
    }

    glm::mat4
    Particle::lookAt(const glm::vec3 &targetPosition, const glm::vec3 &objectPosition)
    {
        glm::vec3 delta = targetPosition - objectPosition;
        glm::vec3 up;
        glm::vec3 direction(glm::normalize(delta));

        if (glm::abs(direction.x) < 0.00001 && glm::abs(direction.z) < 0.00001)
        {
            if (direction.y > 0)
            {
                up = glm::vec3(0.0, 0.0, -1.0); //if direction points in +y
            }
            else
            {
                up = glm::vec3(0.0, 0.0, 1.0); //if direction points in -y
            }
        }
        else
        {
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


