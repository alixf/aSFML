#ifndef ASFML_SHAPE_HPP
#define ASFML_SHAPE_HPP

#include <SFML/Graphics.hpp>

namespace sf
{
    namespace Orientation
    {
        enum Type {NONE, TOPTOBOTTOM, BOTTOMTOTOP, LEFTTORIGHT, RIGHTTOLEFT};
    }

    void ApplyGradient(sf::Shape& shape, Orientation::Type orientation, const sf::Color& color1, const sf::Color& color2, bool applyOnBorder = false);

    float GetPointsDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);

    sf::Shape RoundedRectangle(const sf::FloatRect& rectangle, const sf::Color& color, unsigned int roundness, float outline=0.f, const sf::Color& outlineColor = sf::Color(0,0,0));
}

#endif // ASFML_SHAPE_HPP
