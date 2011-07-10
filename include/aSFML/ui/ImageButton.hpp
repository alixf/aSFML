#ifndef ASFML_GUI_IMAGEBUTTON_HPP
#define ASFML_GUI_IMAGEBUTTON_HPP

#include "Element.hpp"
#include <boost/signals.hpp>

namespace sf
{
    namespace ui
    {
        class ImageButton : public Element
        {
        public :
            enum SplitOrientation {HORIZONTALLY, VERTICALLY};

            ImageButton(const sf::Image& image, const sf::Vector2f& position = sf::Vector2f());
            ~ImageButton();

            sf::Vector2f GetPosition() const;
            float GetRotation() const;
            sf::Vector2f GetScale() const;
            sf::Color GetColor() const;
            sf::FloatRect GetRect() const;

            void SetPosition(const sf::Vector2f& position);
            void SetRotation(float angle);
            void SetScale(const sf::Vector2f& factor);
            void SetColor(const sf::Color& color);
            void SetImage(const sf::Image& image, bool resetSpritesSubRects = false);

            void Move(const sf::Vector2f& offset);
            void Rotate(float angle);
            void Scale(const sf::Vector2f& factor);

            void SplitImage(SplitOrientation orientation, const std::vector<unsigned int>& states);

            bool OnEvent(const sf::Event& event);
            void Draw(sf::RenderWindow& window);

        private :
            std::map<State, sf::Sprite> m_sprites;
        };
    }
}

#endif // ASFML_GUI_IMAGEBUTTON_HPP
