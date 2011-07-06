#ifndef ASFML_UI_PROGRESSBAR_HPP
#define ASFML_UI_PROGRESSBAR_HPP

#include "Element.hpp"
#include <boost/signals.hpp>
#include "../Shape.hpp"

namespace sf
{
    namespace ui
    {
        class ProgressBar : public Element
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
                // Fill
                sf::Color               fillColor;
                float                   fillRoundness;
                sf::Color               fillGradientColor;
                sf::Orientation::Type   fillGradientOrientation;
                sf::FloatRect           fillMargin;
                sf::Color               fillBorderColor;
                float                   fillBorderThickness;
                sf::Color               fillBorderGradientColor;
                sf::Orientation::Type   fillBorderGradientOrientation;
                // Text
                float                   textSize;
                sf::Font&               textFont;
                sf::Color               textColor;
                sf::Color               textShadowColor;
                sf::Vector2f            textShadowOffset;
            };
            typedef std::map<State, StateSkin> Skin;

            ProgressBar(float progress = 0.f, const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), const sf::Vector2f& size = sf::Vector2f(200.f,20.f));
            ~ProgressBar();

            sf::Vector2f GetPosition() const;
            sf::Vector2f GetSize() const;
            sf::FloatRect GetRect() const;
            float GetProgress() const;
            Skin GetSkin() const;

            void SetPosition(const sf::Vector2f& position);
            void SetSize(const sf::Vector2f& size);
            void SetProgress(float progress);
            void SetSkin(const Skin& skin);

            void OnEvent(const sf::Event& event);

            void Draw(sf::RenderWindow& window);

            boost::signals::connection& OnValueChange(boost::signal<void (float)>::slot_type slot);

        private :
            void ApplySkin();

            float           m_progress;
            sf::FloatRect   m_backgroundRect;
            sf::FloatRect   m_fillRect;
            sf::Shape       m_background;
            sf::Shape       m_fill;
            Skin            m_skin;

            // Signals
            boost::signal<void (float)> m_valueChangeSignal;
        };
    }
}

#endif // ASFML_UI_PROGRESSBAR_HPP
