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
    bool absorbed = false;
    std::list<EventListener*>::reverse_iterator it = m_listeners.rbegin();
    while(!absorbed && it != m_listeners.rend())
    {
        absorbed = (*it)->OnEvent(event);
        ++it;
    }
}

sf::EventManager::EventManager()
{
}
