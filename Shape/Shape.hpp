#ifndef     __PARTICULE_SYSTEM_SHAPE_HPP__
# define    __PARTICULE_SYSTEM_SHAPE_HPP__

#include "../../../includes/glm/glm.hpp"

namespace   ParticleSystem
{
    class   Shape
    {

        public:
            enum    Type
            {
                BOX,
                SPHERE,
                HEMISPHERE,
                CONE
            };

        protected:
            Shape(bool randomDirection, bool isActive, Type);

        public:
            virtual void        apply(glm::vec3 &, glm::vec3 &) = 0;

        public:
            Type                getType(void) const { return this->_type; }
            bool                isActive(void) const { return this->_isActive; }
            bool                getRandomDirectionMode(void) const { return this->_randomDirection; }

        public:
            void                setRandomDirectionModeTo(bool randomDirection) { this->_randomDirection = randomDirection; }
            void                setActiveModeTo(bool activeMode) { this->_isActive = activeMode; }

        protected:
            bool                _isActive;
            bool                _randomDirection;
            Type                _type;

    };

    class   BoxShape : public Shape
    {
        public:
            BoxShape(const glm::vec3 & = glm::vec3(0.0f, 0.0f, 0.0f), bool = false, bool = true);
            ~BoxShape(void);

        public:
            void                apply(glm::vec3 &, glm::vec3 &);

        public:
            void                setBoxTo(const glm::vec3 &box) { this->_box = box; }

        public:
            const glm::vec3     &getBox(void) const { return this->_box; }

        private:
            glm::vec3           _box;
    };

    class   SphereShape : public Shape
    {
        public:
            SphereShape(float = 1.0f, bool = false, bool = false, bool = true);
            ~SphereShape(void);

        public:
            virtual void    apply(glm::vec3 &, glm::vec3 &);

        public:
            float           getRadius(void) const { return this->_radius; }
            bool            getEmitFromShell(void) const { return this->_emitFromShell; }

        public:
            void            setRadiusTo(float radius) { this->_radius = radius; }
            void            setEmitFromShellTo(bool emitFromShell) { this->_emitFromShell = emitFromShell; }

        protected:
            float           _radius;
            bool            _emitFromShell;
    };

    class   HemisphereShape : public SphereShape
    {
        public:
            HemisphereShape(float = 1.0f, bool = false, bool = false, bool = true);
            ~HemisphereShape(void);

        public:
            void    apply(glm::vec3 &, glm::vec3 &);
    };

    class   ConeShape : public Shape
    {
        public:
            enum    EmitFrom
            {
                BASE,
                BASESHELL,
                VOLUME,
                VOLUMESHELL
            };

        public:
            ConeShape(float = 0.01f, float = 1.0f, float = 0.0f, EmitFrom = BASE, bool = false, bool = true);
            ~ConeShape(void);

        public:
            void            apply(glm::vec3 &, glm::vec3 &);

        public:
            float           getAngle(void) const { return this->_angle; }
            float           getRadius(void) const { return this->_radius; }
            float           getLength(void) const { return this->_length; }
            EmitFrom        getEmitFromType(void) const { return this->_emitFrom; }

        public:
            void            setAngleTo(float angle) { this->_angle = angle; }
            void            setRadiusTo(float radius) { this->_radius = radius; }
            void            setLength(float length) { this->_length = length; }
            void            setEmitFromTypeTo(EmitFrom type) { this->_emitFrom = type; }

        private:
            float       _angle;
            float       _radius;
            float       _length;
            EmitFrom    _emitFrom;
    };

//    class   MeshShape : public Shape
//    {
//        public:
//            MeshShape(void);
//            ~MeshShape(void);
//
//        public:
//            void                apply(glm::vec3 &, glm::vec3 &);
//    }
}

#endif
