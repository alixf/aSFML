#ifndef ASFML_UI_SWITCH_HPP
#define ASFML_UI_SWITCH_HPP

#include "Element.hpp"
#include <boost/signals.hpp>
#include "../Shape.hpp"

namespace sf
{
    namespace ui
    {
        class Switch : public Element
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
                // Switch
                sf::Color               switchColor;
                float                   switchRoundness;
                sf::Color               switchGradientColor;
                sf::Orientation::Type   switchGradientOrientation;
                sf::Vector2f            switchMargin;
                sf::Color               switchBorderColor;
                float                   switchBorderThickness;
                sf::Color               switchBorderGradientColor;
                sf::Orientation::Type   switchBorderGradientOrientation;
                // On text
                float                   onTextSize;
                sf::Font&               onTextFont;
                sf::Color               onTextColor;
                sf::Color               onTextShadowColor;
                sf::Vector2f            onTextShadowOffset;
                sf::Vector2f            onTextMargin;
                // Off text
                float                   offTextSize;
                sf::Font&               offTextFont;
                sf::Color               offTextColor;
                sf::Color               offTextShadowColor;
                sf::Vector2f            offTextShadowOffset;
                sf::Vector2f            offTextMargin;
            };
            typedef std::map<State, StateSkin> Skin;

            Switch(bool value = false, sf::Vector2f position = sf::Vector2f(0.f, 0.f), sf::Vector2f size = sf::Vector2f(100.f, 30.f));
            ~Switch();

            sf::Vector2f GetPosition() const;
            sf::Vector2f GetSize() const;
            sf::FloatRect GetRect() const;
            bool GetValue() const;
            Skin GetSkin() const;

            void SetPosition(const sf::Vector2f& position);
            void SetSize(const sf::Vector2f& size);
            void SetValue(bool value);
            void SetSkin(const Skin& skin);

            void OnEvent(const sf::Event& event);

            void Draw(sf::RenderWindow& window);

            // Signals
            boost::signal<void ()> m_hoverSignal;
            boost::signal<void ()> m_leaveSignal;
            boost::signal<void ()> m_pressSignal;
            boost::signal<void ()> m_clickSignal;
            boost::signal<void ()> m_releaseSignal;
            boost::signal<void ()> m_disableSignal;
            boost::signal<void (bool)> m_valueChangeSignal;

        private :
            void ApplySkin();

            bool            m_value;
            sf::FloatRect   m_backgroundRect;
            sf::Shape       m_background;
            sf::Text        m_onText;
            sf::Text        m_offText;
            sf::Shape       m_switch;
            Skin            m_skin;
        };
    }
}

#endif // ASFML_UI_SWITCH_HPP
