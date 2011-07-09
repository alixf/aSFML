#include <aSFML/Animator.hpp>
#include <iostream>

FloatAnimation::FloatAnimation(sf::Drawable& p_drawable, float p_beginValue, float p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop) :
    drawable(&p_drawable),
    beginValue(p_beginValue),
    endValue(p_endValue),
    beginTime(p_beginTime),
    duration(p_duration),
    loop(p_loop),
    finished(false)
{
}
ColorAnimation::ColorAnimation(sf::Drawable& p_drawable, sf::Color p_beginValue, sf::Color p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop) :
    drawable(&p_drawable),
    beginValue(p_beginValue),
    endValue(p_endValue),
    beginTime(p_beginTime),
    duration(p_duration),
    loop(p_loop),
    finished(false)
{
}
VectorAnimation::VectorAnimation(sf::Drawable& p_drawable, sf::Vector2f p_beginValue, sf::Vector2f p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop) :
    drawable(&p_drawable),
    beginValue(p_beginValue),
    endValue(p_endValue),
    beginTime(p_beginTime),
    duration(p_duration),
    loop(p_loop),
    finished(false)
{
}

Animator::Animator()
{
}

Animator::~Animator()
{
    for(std::vector<VectorAnimation*>::iterator it = m_moveAnimations.begin(); it != m_moveAnimations.end(); ++it)
        delete *it;
    for(std::vector<FloatAnimation*>::iterator it = m_rotateAnimations.begin(); it != m_rotateAnimations.end(); ++it)
        delete *it;
    for(std::vector<VectorAnimation*>::iterator it = m_scaleAnimations.begin(); it != m_scaleAnimations.end(); ++it)
        delete *it;
    for(std::vector<ColorAnimation*>::iterator it = m_colorAnimations.begin(); it != m_colorAnimations.end(); ++it)
        delete *it;
}

Animator& Animator::GetInstance()
{
    static Animator instance;
    return instance;
}

FloatAnimation* Animator::AddAnimation(sf::Drawable& drawable, Animator::Type type, unsigned int beginTime, unsigned int duration, float beginValue, float endValue, bool loop)
{
    switch(type)
    {
    case Animator::ROTATE :
        m_rotateAnimations.push_back(new FloatAnimation(drawable, beginValue, endValue, beginTime, duration, loop));
        return m_rotateAnimations.back();
        break;

    default :
        std::cerr << "Animator::AddAnimation : Animation Type is not compatible with parameters." << std::endl;
        break;
    }

    return 0;
}

ColorAnimation* Animator::AddAnimation(sf::Drawable& drawable, Animator::Type type, unsigned int beginTime, unsigned int duration, sf::Color beginValue, sf::Color endValue, bool loop)
{
    switch(type)
    {
    case Animator::COLOR :
        m_colorAnimations.push_back(new ColorAnimation(drawable, beginValue, endValue, beginTime, duration, loop));
        return m_colorAnimations.back();
        break;

    default :
        std::cerr << "Animator::AddAnimation : Animation Type is not compatible with parameters." << std::endl;
        break;
    }

    return 0;
}

VectorAnimation* Animator::AddAnimation(sf::Drawable& drawable, Animator::Type type, unsigned int beginTime, unsigned int duration, sf::Vector2f beginValue, sf::Vector2f endValue, bool loop)
{
    switch(type)
    {
    case Animator::MOVE :
        m_moveAnimations.push_back(new VectorAnimation(drawable, beginValue, endValue, beginTime, duration, loop));
        return m_moveAnimations.back();
        break;

    case Animator::SCALE :
        m_scaleAnimations.push_back(new VectorAnimation(drawable, beginValue, endValue, beginTime, duration, loop));
        return m_scaleAnimations.back();
        break;

    default :
        std::cerr << "Animator::AddAnimation : Animation Type is not compatible with parameters." << std::endl;
        break;
    }

    return 0;
}

void Animator::RemoveAnimation(FloatAnimation* animation)
{
    for(std::vector<FloatAnimation*>::iterator it = m_rotateAnimations.begin(); it != m_rotateAnimations.end(); ++it)
    {
        if(animation == *it)
        {
            delete *it;
            m_rotateAnimations.erase(it);
            return;
        }
    }
}

void Animator::RemoveAnimation(ColorAnimation* animation)
{
    for(std::vector<ColorAnimation*>::iterator it = m_colorAnimations.begin(); it != m_colorAnimations.end(); ++it)
    {
        if(animation == *it)
        {
            delete *it;
            m_colorAnimations.erase(it);
            return;
        }
    }
}

void Animator::RemoveAnimation(VectorAnimation* animation)
{
    for(std::vector<VectorAnimation*>::iterator it = m_moveAnimations.begin(); it != m_moveAnimations.end(); ++it)
    {
        if(animation == *it)
        {
            delete *it;
            m_moveAnimations.erase(it);
            return;
        }
    }
    for(std::vector<VectorAnimation*>::iterator it = m_scaleAnimations.begin(); it != m_scaleAnimations.end(); ++it)
    {
        if(animation == *it)
        {
            delete *it;
            m_scaleAnimations.erase(it);
            return;
        }
    }
}

void Animator::Apply()
{
    for(std::vector<VectorAnimation*>::iterator it = m_moveAnimations.begin(); it != m_moveAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                // TODO : SUBSTRACT TIME TO CLOCK
            }
            else
            {
                (*it)->drawable->SetPosition((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->drawable->SetPosition(factor*((*it)->endValue)+(1-factor)*((*it)->beginValue));
        }
    }
    for(std::vector<FloatAnimation*>::iterator it = m_rotateAnimations.begin(); it != m_rotateAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                //TODO : SUBSTRACT TIME TO CLOCK
                (*it)->drawable->SetRotation((*it)->endValue);
                (*it)->finished = true;
            }
            else
            {
                (*it)->drawable->SetRotation((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->drawable->SetRotation(factor*((*it)->endValue)+(1-factor)*((*it)->beginValue));
        }
    }
    for(std::vector<VectorAnimation*>::iterator it = m_scaleAnimations.begin(); it != m_scaleAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                //TODO : SUBSTRACT TIME TO CLOCK
                (*it)->drawable->SetScale((*it)->endValue);
                (*it)->finished = true;
            }
            else
            {
                (*it)->drawable->SetScale((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->drawable->SetScale(factor*((*it)->endValue)+(1-factor)*((*it)->beginValue));
        }
    }
    for(std::vector<ColorAnimation*>::iterator it = m_colorAnimations.begin(); it != m_colorAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                //TODO : SUBSTRACT TIME TO CLOCK
                (*it)->drawable->SetColor((*it)->endValue);
                (*it)->finished = true;
            }
            else
            {
                (*it)->drawable->SetColor((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->drawable->SetColor(sf::Color(factor*((*it)->endValue.r)+(1-factor)*((*it)->beginValue.r),
                                             factor*((*it)->endValue.g)+(1-factor)*((*it)->beginValue.g),
                                             factor*((*it)->endValue.b)+(1-factor)*((*it)->beginValue.b),
                                             factor*((*it)->endValue.a)+(1-factor)*((*it)->beginValue.a)));
        }
    }
}
