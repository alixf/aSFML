#ifndef ASFML_ANIMATOR_HPP
#define ASFML_ANIMATOR_HPP

#include <SFML/Graphics.hpp>

//TODO : Implements the three following structures with templates
struct FloatAnimation
{
    FloatAnimation(sf::Drawable& p_drawable, float p_beginValue, float p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop = false);

    sf::Drawable* drawable;
    sf::Clock clock;
    float beginValue;
    float endValue;
    unsigned int beginTime;
    unsigned int duration;
    bool loop;
    bool finished;
};

struct ColorAnimation
{
    ColorAnimation(sf::Drawable& p_drawable, sf::Color p_beginValue, sf::Color p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop = false);

    sf::Drawable* drawable;
    sf::Clock clock;
    sf::Color beginValue;
    sf::Color endValue;
    unsigned int beginTime;
    unsigned int duration;
    bool loop;
    bool finished;
};

struct VectorAnimation
{
    VectorAnimation(sf::Drawable& p_drawable, sf::Vector2f p_beginValue, sf::Vector2f p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop = false);

    sf::Drawable* drawable;
    sf::Clock clock;
    sf::Vector2f beginValue;
    sf::Vector2f endValue;
    unsigned int beginTime;
    unsigned int duration;
    bool loop;
    bool finished;
};

class Animator
{
public :
    enum Type{MOVE, ROTATE, SCALE, COLOR};

    ~Animator();
    static Animator& GetInstance();

    FloatAnimation* AddAnimation(sf::Drawable& drawable, Animator::Type type, unsigned int beginTime, unsigned int duration, float beginValue, float endValue, bool loop = false);
    ColorAnimation* AddAnimation(sf::Drawable& drawable, Animator::Type type, unsigned int beginTime, unsigned int duration, sf::Color beginValue, sf::Color endValue, bool loop = false);
    VectorAnimation* AddAnimation(sf::Drawable& drawable, Animator::Type type, unsigned int beginTime, unsigned int duration, sf::Vector2f beginValue, sf::Vector2f endValue, bool loop = false);
    void RemoveAnimation(FloatAnimation* animation);
    void RemoveAnimation(ColorAnimation* animation);
    void RemoveAnimation(VectorAnimation* animation);

    void Apply();

private :
    Animator();

    std::vector<VectorAnimation*> m_moveAnimations;
    std::vector<FloatAnimation*> m_rotateAnimations;
    std::vector<VectorAnimation*> m_scaleAnimations;
    std::vector<ColorAnimation*> m_colorAnimations;
};

#endif // ASFML_ANIMATOR_HPP
