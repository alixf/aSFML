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

            virtual bool OnEvent(const sf::Event& event) = 0;
            virtual void Draw(sf::RenderWindow& window) = 0;

            boost::signals::connection& OnHover(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnLeave(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnPress(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnClick(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnRelease(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnEnable(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnDisable(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnActivate(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnDesactivate(boost::signal<void ()>::slot_type slot);

            void DisconnectSlot(boost::signals::connection& connection);
            void DisconnectSlots();

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

            std::vector<boost::signals::connection> m_connections;
        };
    }
}

#endif // ASFML_GUI_ELEMENT_HPP
