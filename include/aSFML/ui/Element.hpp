#ifndef ASFML_GUI_ELEMENT_HPP
#define ASFML_GUI_ELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <boost/signals.hpp>
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

            void OnHover(boost::signal<void ()>::slot_type slot);
            void OnLeave(boost::signal<void ()>::slot_type slot);
            void OnPress(boost::signal<void ()>::slot_type slot);
            void OnClick(boost::signal<void ()>::slot_type slot);
            void OnRelease(boost::signal<void ()>::slot_type slot);
            void OnEnable(boost::signal<void ()>::slot_type slot);
            void OnDisable(boost::signal<void ()>::slot_type slot);
            void OnActivate(boost::signal<void ()>::slot_type slot);
            void OnDesactivate(boost::signal<void ()>::slot_type slot);

        protected :
            State m_state;
            sf::Clock m_clock;

            // Signals
            boost::signal<void ()> m_hoverSignal;
            boost::signal<void ()> m_leaveSignal;
            boost::signal<void ()> m_pressSignal;
            boost::signal<void ()> m_clickSignal;
            boost::signal<void ()> m_releaseSignal;
            boost::signal<void ()> m_enableSignal;
            boost::signal<void ()> m_disableSignal;
            boost::signal<void ()> m_activateSignal;
            boost::signal<void ()> m_desactivateSignal;
        };
    }
}

#endif // ASFML_GUI_ELEMENT_HPP
