#ifndef ASFML_UI_SLIDER_HPP
#define ASFML_UI_SLIDER_HPP

#include "Element.hpp"
#include <boost/signals.hpp>
#include "../Shape.hpp"

namespace sf
{
    namespace ui
    {
        class Slider : public Element
        {
        public :
            struct StateSkin
            {
                StateSkin();
                // Range
                float                   rangeHeight;
                float                   rangeRoundness;
                sf::Color               rangeColor;
                sf::Color               rangeGradientColor;
                sf::Orientation::Type   rangeGradientOrientation;
                float                   rangeBorderThickness;
                sf::Color               rangeBorderColor;
                sf::Color               rangeBorderGradientColor;
                sf::Orientation::Type   rangeBorderGradientOrientation;
                // Cursor
                float                   cursorWidth;
                float                   cursorRoundness;
                sf::Color               cursorColor;
                sf::Color               cursorGradientColor;
                sf::Orientation::Type   cursorGradientOrientation;
                float                   cursorBorderThickness;
                sf::Color               cursorBorderColor;
                sf::Color               cursorBorderGradientColor;
                sf::Orientation::Type   cursorBorderGradientOrientation;
            };
            typedef std::map<State, StateSkin> Skin;

            Slider(float value = 0.f, const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), const sf::Vector2f& size = sf::Vector2f(200.f,20.f));
            ~Slider();

            sf::Vector2f GetPosition() const;
            sf::Vector2f GetSize() const;
            sf::FloatRect GetRect() const;
            float GetValue() const;
            Skin GetSkin() const;

            void SetPosition(const sf::Vector2f& position);
            void SetSize(const sf::Vector2f& size);
            void SetValue(float value);
            void SetSkin(const Skin& skin);
            void SetState(State);

            bool OnEvent(const sf::Event& event);

            void Draw(sf::RenderWindow& window);

            boost::signals::connection& OnValueChange(boost::signal<void (float)>::slot_type slot);

        private :
            void ApplySkin();

            float           m_value;
            float           m_cursorMouseOffset;
            bool            m_dragAndDrop;
            sf::FloatRect   m_boundingRect;
            sf::FloatRect   m_rangeRect;
            sf::FloatRect   m_cursorRect;
            sf::Shape       m_range;
            sf::Shape       m_cursor;
            Skin            m_skin;

            // Signals
            boost::signal<void (float)> m_valueChangeSignal;
        };
    }
}

#endif // ASFML_UI_SLIDER_HPP
