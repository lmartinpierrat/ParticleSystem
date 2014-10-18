#ifndef     __MIN_MAX_VALUE_HPP__
# define    __MIN_MAX_VALUE_HPP__

#include "../../../includes/glm/glm.hpp"
#include <vector>

namespace   ParticleSystem
{
  class   MinMaxValueFloat
  {
  public:
    enum    Type
      {
	CONSTANT,
	CURVE,
	RANDOMBETWEENTWOCONSTANTS,
	RANDOMBETWEENTWOCURVES
      };

  public:
    MinMaxValueFloat(Type, float, float = 0.0f);
    MinMaxValueFloat(Type, const std::vector<std::pair<float, float> > &,
		     const std::vector<std::pair<float, float> > & = std::vector<std::pair<float, float> >());
    ~MinMaxValueFloat(void) {}

  public:
    MinMaxValueFloat					&operator=(const MinMaxValueFloat &);

  public:
    void						setFloatTo(float value) { this->_value1 = value; }
    void						setFloat1To(float value) { this->_value1 = value; }
    void						setFloat2To(float value) { this->_value2 = value; }
    void						setCurveTo(const std::vector<std::pair<float, float> > &curve) { this->_curve1 = curve; }
    void						setCurve1To(const std::vector<std::pair<float, float> > &curve) { this->_curve1 = curve; }
    void						setCurve2To(const std::vector<std::pair<float, float> > &curve) { this->_curve2 = curve; }
    void						setTypeTo(Type type) { this->_type = type; }

  public:
    float						getFloat(void) const { return this->_value1; }
    float						getFloat1(void) const { return this->_value1; }
    float						getFloat2(void) const { return this->_value2; }
    const std::vector<std::pair<float, float> >		&getCurve(void) const { return this->_curve1; }
    const std::vector<std::pair<float, float> >		&getCurve1(void) const { return this->_curve1; }
    const std::vector<std::pair<float, float> >		&getCurve2(void) const { return this->_curve2; }
    Type						getType(void) const { return this->_type; }

  public:
    float						getValue(float percentage = 1.0f) const;

  protected:
    float						_value1;
    float						_value2;
    std::vector<std::pair<float, float> >		_curve1;
    std::vector<std::pair<float, float> >		_curve2;
    Type						_type;
  };

  class   MinMaxValueColor
  {
  public:
    enum    Type
      {
	COLOR,
	GRADIANT,
	RANDOMBETWEENTWOCOLORS,
	RANDOMBETWEENTWOGRADIANTS
      };

  public:
    MinMaxValueColor(void){}
    MinMaxValueColor(Type, const glm::vec4 &, const glm::vec4 & = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    MinMaxValueColor(Type, const std::vector<std::pair<float, glm::vec4> > &, const std::vector<std::pair<float, glm::vec4> > & = std::vector<std::pair<float, glm::vec4> >());
    ~MinMaxValueColor(void);

  public:
    MinMaxValueColor    &operator=(const MinMaxValueColor &);

  public:
    void                                            setGradiant(const std::vector<std::pair<float, glm::vec4> > &gradiant) { this->_gradiant1 = gradiant; }
    void                                            setGradiant1(const std::vector<std::pair<float, glm::vec4> > &gradiant) { this->_gradiant1 = gradiant; }
    void                                            setGradiant2(const std::vector<std::pair<float, glm::vec4> > &gradiant) { this->_gradiant2 = gradiant; }
    void                                            setColor(const glm::vec4 &color1) { this->_color1 = color1; }
    void                                            setColor1(const glm::vec4 &color1) { this->_color1 = color1; }
    void                                            setColor2(const glm::vec4 &color2) { this->_color2 = color2; }
    void                                            setType(Type type) { this->_type = type; }

  public:
    const glm::vec4                                 &getColor(void) const { return this->_color1; }
    const glm::vec4                                 &getColor1(void) const { return this->_color1; }
    const glm::vec4                                 &getColor2(void) const { return this->_color2; }
    const std::vector<std::pair<float, glm::vec4> > &getGradiant(void) const { return this->_gradiant1; }
    const std::vector<std::pair<float, glm::vec4> > &getGradiant1(void) const { return this->_gradiant1; }
    const std::vector<std::pair<float, glm::vec4> > &getGradiant2(void) const { return this->_gradiant2; }
    const Type                                      &getType(void) const { return this->_type; }

  public:
    glm::vec4                                       getValue(float percentage = 1.0f) const ;

  protected:
    std::vector<std::pair<float, glm::vec4> >   _gradiant1;
    std::vector<std::pair<float, glm::vec4> >   _gradiant2;
    glm::vec4                                   _color1;
    glm::vec4                                   _color2;
    Type                                        _type;
  };
}

#endif
