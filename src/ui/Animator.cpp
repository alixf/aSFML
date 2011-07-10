#include <aSFML/ui/Animator.hpp>
#include <iostream>

sf::ui::FloatAnimation::FloatAnimation(sf::ui::Element& p_element, float p_beginValue, float p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop) :
    element(&p_element),
    beginValue(p_beginValue),
    endValue(p_endValue),
    beginTime(p_beginTime),
    duration(p_duration),
    loop(p_loop),
    finished(false)
{
}

sf::ui::ColorAnimation::ColorAnimation(sf::ui::Element& p_element, sf::Color p_beginValue, sf::Color p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop) :
    element(&p_element),
    beginValue(p_beginValue),
    endValue(p_endValue),
    beginTime(p_beginTime),
    duration(p_duration),
    loop(p_loop),
    finished(false)
{
}

sf::ui::VectorAnimation::VectorAnimation(sf::ui::Element& p_element, sf::Vector2f p_beginValue, sf::Vector2f p_endValue, unsigned int p_beginTime, unsigned int p_duration, bool p_loop) :
    element(&p_element),
    beginValue(p_beginValue),
    endValue(p_endValue),
    beginTime(p_beginTime),
    duration(p_duration),
    loop(p_loop),
    finished(false)
{
}

sf::ui::Animator::Animator()
{
}

sf::ui::Animator::~Animator()
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

sf::ui::Animator& sf::ui::Animator::GetInstance()
{
    static Animator instance;
    return instance;
}

sf::ui::FloatAnimation* sf::ui::Animator::AddAnimation(sf::ui::Element& element, Animator::Type type, unsigned int beginTime, unsigned int duration, float beginValue, float endValue, bool loop)
{
    switch(type)
    {
    case Animator::ROTATE :
        m_rotateAnimations.push_back(new FloatAnimation(element, beginValue, endValue, beginTime, duration, loop));
        return m_rotateAnimations.back();
        break;

    default :
        std::cerr << "sf::Animator::AddAnimation : Animation Type is not compatible with parameters." << std::endl;
        break;
    }

    return 0;
}

sf::ui::ColorAnimation* sf::ui::Animator::AddAnimation(sf::ui::Element& element, Animator::Type type, unsigned int beginTime, unsigned int duration, sf::Color beginValue, sf::Color endValue, bool loop)
{
    switch(type)
    {
    case Animator::COLOR :
        m_colorAnimations.push_back(new ColorAnimation(element, beginValue, endValue, beginTime, duration, loop));
        return m_colorAnimations.back();
        break;

    default :
        std::cerr << "sf::Animator::AddAnimation : Animation Type is not compatible with parameters." << std::endl;
        break;
    }

    return 0;
}

sf::ui::VectorAnimation* sf::ui::Animator::AddAnimation(sf::ui::Element& element, Animator::Type type, unsigned int beginTime, unsigned int duration, sf::Vector2f beginValue, sf::Vector2f endValue, bool loop)
{
    switch(type)
    {
    case Animator::MOVE :
        m_moveAnimations.push_back(new VectorAnimation(element, beginValue, endValue, beginTime, duration, loop));
        return m_moveAnimations.back();
        break;

    case Animator::SCALE :
        m_scaleAnimations.push_back(new VectorAnimation(element, beginValue, endValue, beginTime, duration, loop));
        return m_scaleAnimations.back();
        break;

    default :
        std::cerr << "sf::Animator::AddAnimation : Animation Type is not compatible with parameters." << std::endl;
        break;
    }

    return 0;
}

void sf::ui::Animator::Remove(sf::ui::FloatAnimation* animation)
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

void sf::ui::Animator::Remove(sf::ui::ColorAnimation* animation)
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

void sf::ui::Animator::Remove(sf::ui::VectorAnimation* animation)
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

void sf::ui::Animator::Clear()
{
    m_moveAnimations.clear();
    m_rotateAnimations.clear();
    m_scaleAnimations.clear();
    m_colorAnimations.clear();
}

void sf::ui::Animator::Apply()
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
                (*it)->element->SetPosition((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->element->SetPosition(factor*((*it)->endValue)+(1-factor)*((*it)->beginValue));
        }
    }
    for(std::vector<FloatAnimation*>::iterator it = m_rotateAnimations.begin(); it != m_rotateAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                //TODO : SUBSTRACT TIME TO CLOCK
                (*it)->element->SetRotation((*it)->endValue);
                (*it)->finished = true;
            }
            else
            {
                (*it)->element->SetRotation((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->element->SetRotation(factor*((*it)->endValue)+(1-factor)*((*it)->beginValue));
        }
    }
    for(std::vector<VectorAnimation*>::iterator it = m_scaleAnimations.begin(); it != m_scaleAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                //TODO : SUBSTRACT TIME TO CLOCK
                (*it)->element->SetScale((*it)->endValue);
                (*it)->finished = true;
            }
            else
            {
                (*it)->element->SetScale((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->element->SetScale(factor*((*it)->endValue)+(1-factor)*((*it)->beginValue));
        }
    }
    for(std::vector<ColorAnimation*>::iterator it = m_colorAnimations.begin(); it != m_colorAnimations.end(); ++it)
    {
        while((*it)->clock.GetElapsedTime() > (*it)->beginTime+(*it)->duration && !(*it)->finished)
        {
            if((*it)->loop)
            {
                //TODO : SUBSTRACT TIME TO CLOCK
                (*it)->element->SetColor((*it)->endValue);
                (*it)->finished = true;
            }
            else
            {
                (*it)->element->SetColor((*it)->endValue);
                (*it)->finished = true;
            }
        }
        if((*it)->clock.GetElapsedTime() >= (*it)->beginTime && !(*it)->finished)
        {
            float factor = ((*it)->clock.GetElapsedTime()-(*it)->beginTime)/static_cast<float>((*it)->duration);
            (*it)->element->SetColor(sf::Color(factor*((*it)->endValue.r)+(1-factor)*((*it)->beginValue.r),
                                               factor*((*it)->endValue.g)+(1-factor)*((*it)->beginValue.g),
                                               factor*((*it)->endValue.b)+(1-factor)*((*it)->beginValue.b),
                                               factor*((*it)->endValue.a)+(1-factor)*((*it)->beginValue.a)));
        }
    }
}
