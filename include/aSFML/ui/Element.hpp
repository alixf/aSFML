#ifndef ASFML_GUI_ELEMENT_HPP
#define ASFML_GUI_ELEMENT_HPP

#include <SFML/Graphics.hpp>
#include "../EventManager.hpp"

namespace sf
{
    namespace ui
    {
        class Element : public EventListener, sf::NonCopyable
        {
        public :
            enum State {NORMAL = 1 << 0,
                        HOVER = 1 << 1,
                        PRESSED = 1 << 2,
                        CLICKED = 1 << 3,
                        ACTIVE = 1 << 4,
                        DISABLED = 1 << 5
                       };

            Element();

            virtual ~Element();

            virtual void OnEvent(const sf::Event& event) = 0;
            virtual void Draw(sf::RenderWindow& window) = 0;

        protected :
            State m_state;
            sf::Clock m_clock;
        };
    }
}

#endif // ASFML_GUI_ELEMENT_HPP
