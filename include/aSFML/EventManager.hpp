#ifndef ASFML_EVENTMANAGER_HPP
#define ASFML_EVENTMANAGER_HPP

#include <list>
#include "EventListener.hpp"

namespace sf
{
    class EventManager
    {
    public :
        static EventManager& GetInstance();

        void AddListener(EventListener* listener);

        void RemoveListener(EventListener* listener);

        void PostEvent(const sf::Event& event);

    private :
        EventManager();

        std::list<EventListener*> m_listeners;
    };
}

#endif // ASFML_EVENTMANAGER_HPP
