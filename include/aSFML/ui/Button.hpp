#ifndef ASFML_UI_BUTTON_HPP
#define ASFML_UI_BUTTON_HPP

#include "Element.hpp"
#include <boost/signals.hpp>
#include "../Shape.hpp"

namespace sf
{
    namespace ui
    {
        class Button : public sf::ui::Element
        {
        public :
            struct StateSkin
            {
                StateSkin();
                // Background
                sf::Color               backgroundColor;
                float                   backgroundRoundness;
                sf::Color               backgroundGradientColor;
                sf::Orientation::Type   backgroundGradientOrientation;
                sf::Color               backgroundBorderColor;
                float                   backgroundBorderThickness;
                sf::Color               backgroundBorderGradientColor;
                sf::Orientation::Type   backgroundBorderGradientOrientation;
                // Text
                float                   textSize;
                sf::Font&               textFont;
                sf::Color               textColor;
                sf::Color               textShadowColor;
                sf::Vector2f            textShadowOffset;
                sf::FloatRect           textMargin;
            };
            typedef std::map<State, StateSkin> Skin;

            Button(const std::wstring& text = std::wstring(), const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), const sf::Vector2f& size = sf::Vector2f(-1.f, -1.f));
            ~Button();

            sf::Vector2f GetPosition() const;
            sf::Vector2f GetSize() const;
            sf::FloatRect GetRect() const;
            std::wstring GetString() const;
            Skin GetSkin() const;

            void SetPosition(const sf::Vector2f& position);
            void SetSize(const sf::Vector2f& size);
            void SetString(const std::wstring& string);
            void SetSkin(Skin& skin);

            void OnEvent(const sf::Event& event);

            void Draw(sf::RenderWindow& window);

            // Signals
            boost::signal<void ()> m_hoverSignal;
            boost::signal<void ()> m_leaveSignal;
            boost::signal<void ()> m_pressSignal;
            boost::signal<void ()> m_clickSignal;
            boost::signal<void ()> m_releaseSignal;
            boost::signal<void ()> m_disableSignal;

            //TODO : make signal assignement methods

        private :
            void ApplySkin();

            sf::FloatRect   m_backgroundRect;
            sf::Vector2f    m_size;
            sf::Shape       m_background;
            sf::Text        m_text;
            Skin            m_skin;
        };
    }
}

#endif // ASFML_UI_BUTTON_HPP
