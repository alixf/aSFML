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
                sf::FloatRect           textMargin;
                // Placeholder
                float                   placeholderSize;
                sf::Font&               placeholderFont;
                sf::Color               placeholderColor;
                sf::Color               placeholderShadowColor;
                sf::Vector2f            placeholderShadowOffset;
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

            void OnEvent(const sf::Event& event);

            void Draw(sf::RenderWindow& window);

            // Signals
            boost::signal<void ()> m_hoverSignal;
            boost::signal<void ()> m_leaveSignal;
            boost::signal<void ()> m_pressSignal;
            boost::signal<void ()> m_clickSignal;
            boost::signal<void ()> m_releaseSignal;
            boost::signal<void ()> m_disableSignal;
            boost::signal<void ()> m_activateSignal;
            boost::signal<void ()> m_desactivateSignal;
            boost::signal<void ()> m_submitSignal;
            boost::signal<void ()> m_switchSignal;

            boost::signal<void (const std::wstring&)> m_valueChangeSignal;

        private :
            void ApplySkin();
            void MoveCursor(int offset);

            sf::FloatRect   m_backgroundRect;
            sf::Clock       m_cursorClock;
            float           m_cursorBlinkTime;
            bool            m_drawCursor;
            unsigned int    m_cursorPosition;
            sf::Shape       m_background;
            sf::Shape       m_cursor;
            sf::Text        m_text;
            sf::Text        m_placeholder;
            Skin            m_skin;
        };
    }
}

#endif // ASFML_UI_TEXTINPUT_HPP
