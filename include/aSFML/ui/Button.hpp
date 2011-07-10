#ifndef ASFML_UI_BUTTON_HPP
#define ASFML_UI_BUTTON_HPP

#include "Element.hpp"
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
                float                   textCharacterSize;
                sf::Font&               textFont;
                sf::Color               textColor;
                sf::Color               textShadowColor;
                sf::Vector2f            textShadowOffset;
                sf::FloatRect           textMargin;
            };
            typedef std::map<State, StateSkin> Skin;

            Button(const std::wstring& text = std::wstring(), const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), const sf::Vector2f& size = sf::Vector2f(-1.f, -1.f));
            ~Button();

            Skin GetSkin() const;
            sf::Vector2f GetSize() const;
            sf::FloatRect GetRect() const;
            std::wstring GetString() const;
            sf::Vector2f GetPosition() const;
            float GetRotation() const;
            sf::Vector2f GetScale() const;
            sf::Color GetColor() const;

            void SetState(State state);
            void SetSkin(Skin& skin);
            void SetSize(const sf::Vector2f& size);
            void SetString(const std::wstring& string);
            void SetPosition(const sf::Vector2f& position);
            void SetRotation(float angle);
            void SetScale(const sf::Vector2f& factor);
            void SetColor(const sf::Color& color);

            void Move(const sf::Vector2f& offset);
            void Rotate(float angle);
            void Scale(const sf::Vector2f& factor);

            bool OnEvent(const sf::Event& event);
            void Draw(sf::RenderWindow& window);

        private :
            void ApplySkin();
            void ApplySkin(const sf::Vector2f& buttonSize);

            std::wstring						m_string;
            Skin                    		    m_skin;
            std::map<State, sf::RenderImage*>	m_renderImages;
            std::map<State, sf::Sprite> 		m_sprites;
        };
    }
}

#endif // ASFML_UI_BUTTON_HPP
