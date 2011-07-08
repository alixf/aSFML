#ifndef ASFML_UI_TEXTINPUT_HPP
#define ASFML_UI_TEXTINPUT_HPP

#include "Element.hpp"
#include <boost/signals.hpp>
#include "../Shape.hpp"

namespace sf
{
    namespace ui
    {
        class TextInput : public Element
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
                sf::Vector2f            textOffset;
                // Placeholder
                float                   placeholderSize;
                sf::Font&               placeholderFont;
                sf::Color               placeholderColor;
                sf::Color               placeholderShadowColor;
                sf::Vector2f            placeholderShadowOffset;
                sf::Vector2f            placeholderOffset;
                // Cursor
                sf::Color               cursorColor;
                float                   cursorWidth;
                sf::Color               cursorGradientColor;
                sf::Orientation::Type   cursorGradientOrientation;
            };
            typedef std::map<State, StateSkin> Skin;

            TextInput(const std::wstring& placeholder = std::wstring(), const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), const sf::Vector2f& size = sf::Vector2f(150.f, 30.f));
            ~TextInput();

            sf::Vector2f GetPosition() const;
            sf::Vector2f GetSize() const;
            sf::FloatRect GetRect() const;
            std::wstring GetText() const;
            Skin GetSkin() const;

            void SetPosition(const sf::Vector2f& position);
            void SetSize(const sf::Vector2f& size);
            void SetText(const std::wstring& string);
            void SetSkin(const Skin& skin);
            void SetState(State);

            bool OnEvent(const sf::Event& event);

            void Draw(sf::RenderWindow& window);

            boost::signals::connection& OnSwitch(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnSubmit(boost::signal<void ()>::slot_type slot);
            boost::signals::connection& OnValueChange(boost::signal<void (const std::wstring&)>::slot_type slot);

        private :
            void ApplySkin();
            void MoveCursor(int offset);

            sf::FloatRect   m_backgroundRect;
            sf::Clock       m_cursorClock;
            unsigned int    m_cursorBlinkTime;
            bool            m_drawCursor;
            unsigned int    m_cursorPosition;
            sf::Shape       m_background;
            sf::Shape       m_cursor;
            sf::Text        m_text;
            sf::Text        m_placeholder;
            Skin            m_skin;

            // Signals
            boost::signal<void ()> m_submitSignal;
            boost::signal<void ()> m_switchSignal;
            boost::signal<void (const std::wstring&)> m_valueChangeSignal;
        };
    }
}

#endif // ASFML_UI_TEXTINPUT_HPP
