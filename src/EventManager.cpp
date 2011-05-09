#include <aSFML/EventManager.hpp>

sf::EventManager& sf::EventManager::GetInstance()
{
    static EventManager instance;
    return instance;
}

void sf::EventManager::AddListener(EventListener* listener)
{
    m_listeners.push_back(listener);
}

void sf::EventManager::RemoveListener(EventListener* listener)
{
    m_listeners.remove(listener);
}

void sf::EventManager::PostEvent(const sf::Event& event)
{
    for(std::list<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
        (*it)->OnEvent(event);
}

sf::EventManager::EventManager()
{
}
