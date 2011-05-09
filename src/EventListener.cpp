#include <aSFML/EventListener.hpp>
#include <aSFML/EventManager.hpp>

sf::EventListener::EventListener()
{
    sf::EventManager::GetInstance().AddListener(this);
}

sf::EventListener::~EventListener()
{
    sf::EventManager::GetInstance().RemoveListener(this);
}
