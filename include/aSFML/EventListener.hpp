#ifndef ASFML_EVENTLISTENER_HPP
#define ASFML_EVENTLISTENER_HPP

#include <SFML/Window.hpp>

namespace sf
{
    class EventListener
    {
    public :
        EventListener();

        virtual ~EventListener();

        virtual bool OnEvent(const sf::Event& event) = 0;
    };
}

#endif // ASFML_EVENTLISTENER_HPP
