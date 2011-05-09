#include <aSFML/Shape.hpp>

void sf::ApplyGradient(sf::Shape& shape, Orientation::Type orientation, const sf::Color& color1, const sf::Color& color2, bool applyOnBorder)
{
    if(orientation != sf::Orientation::NONE)
    {
        sf::FloatRect shapeRect(shape.GetPointPosition(0), sf::Vector2f(0.f,0.f));
        sf::Vector2f rectRightBottomCorner(0.f,0.f);

        // Define left and top limits
        for(unsigned int i = 0; i < shape.GetPointsCount(); ++i)
        {
            sf::Vector2f pointPosition = shape.GetPointPosition(i);
            shapeRect.Left = (pointPosition.x < shapeRect.Left) ? pointPosition.x : shapeRect.Left;
            shapeRect.Top = (pointPosition.y < shapeRect.Top) ? pointPosition.y : shapeRect.Top;
            rectRightBottomCorner.x = (pointPosition.x > rectRightBottomCorner.x) ? pointPosition.x : rectRightBottomCorner.x;
            rectRightBottomCorner.y = (pointPosition.y > rectRightBottomCorner.y) ? pointPosition.y : rectRightBottomCorner.y;
        }
        shapeRect.Width = rectRightBottomCorner.x-shapeRect.Left;
        shapeRect.Height = rectRightBottomCorner.y-shapeRect.Top;

        // Apply gradient
        for(unsigned int i = 0; i < shape.GetPointsCount(); ++i)
        {
            float factor = 0.f;
            sf::Vector2f pointPosition = shape.GetPointPosition(i);
            switch(orientation)
            {
            case Orientation::TOPTOBOTTOM :
                factor = 1-(pointPosition.y-shapeRect.Top)/shapeRect.Height;
                break;

            case Orientation::BOTTOMTOTOP :
                factor = (pointPosition.y-shapeRect.Top)/shapeRect.Height;
                break;

            case Orientation::LEFTTORIGHT :
                factor = 1-(pointPosition.x-shapeRect.Left)/shapeRect.Width;
                break;

            case Orientation::RIGHTTOLEFT :
                factor = (pointPosition.x-shapeRect.Left)/shapeRect.Width;
                break;

            default :
                factor = 1;
                break;
            }
            if(applyOnBorder)
                shape.SetPointOutlineColor(i, sf::Color(factor*color1.r+(1-factor)*color2.r, factor*color1.g+(1-factor)*color2.g, factor*color1.b+(1-factor)*color2.b, factor*color1.a+(1-factor)*color2.a));
            else
                shape.SetPointColor(i, sf::Color(factor*color1.r+(1-factor)*color2.r, factor*color1.g+(1-factor)*color2.g, factor*color1.b+(1-factor)*color2.b, factor*color1.a+(1-factor)*color2.a));
        }
    }
}

float sf::GetPointsDistance(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return sqrt((point2.x-point1.x)*(point2.x-point1.x)+(point2.y-point1.y)*(point2.y-point1.y));
}

sf::Shape sf::RoundedRectangle(const sf::FloatRect& rectangle, const sf::Color& color, unsigned int roundness, float outline, const sf::Color& outlineColor)
{
    float pointsMinimalDistance = 1.1f;

    // Set the roundess to be less than or equal to the semi-size
    if(roundness > rectangle.Width/2)
        roundness = ceil(rectangle.Width/2);
    if(roundness > rectangle.Height/2)
        roundness = ceil(rectangle.Height/2);

    if(roundness == 0)
        return sf::Shape::Rectangle(rectangle, color, outline, outlineColor);

    sf::Shape shape;

    // Top-left corner
    for(unsigned int i = 0; i <= roundness+1; ++i)
    {
        sf::Vector2f pointPosition(cos(M_PI-i*M_PI/(roundness*2+2))*roundness+roundness+rectangle.Left, -sin(M_PI-i*M_PI/(roundness*2+2))*roundness+roundness+rectangle.Top);
        if(GetPointsDistance(shape.GetPointPosition(shape.GetPointsCount()-1), pointPosition)>=pointsMinimalDistance)
            shape.AddPoint(pointPosition, color, outlineColor);
    }
    // Top-right corner
    for(unsigned int i = 0; i <= roundness+1; ++i)
    {
        sf::Vector2f pointPosition(cos(0.5f*M_PI-(i*M_PI/(roundness*2+2)))*roundness+rectangle.Left+rectangle.Width-roundness, -sin(0.5f*M_PI-i*M_PI/(roundness*2+2))*roundness+roundness+rectangle.Top);
        if(GetPointsDistance(shape.GetPointPosition(shape.GetPointsCount()-1), pointPosition)>=pointsMinimalDistance)
            shape.AddPoint(pointPosition, color, outlineColor);
    }
    // Bottom-right corner
    for(unsigned int i = 0; i <= roundness+1; ++i)
    {
        sf::Vector2f pointPosition(cos(-(i*M_PI/(roundness*2+2)))*roundness+rectangle.Left+rectangle.Width-roundness, -sin(-(i*M_PI/(roundness*2+2)))*roundness+rectangle.Top+rectangle.Height-roundness);
        if(GetPointsDistance(shape.GetPointPosition(shape.GetPointsCount()-1), pointPosition)>=pointsMinimalDistance)
            shape.AddPoint(pointPosition, color, outlineColor);
    }
    // Bottom-left corner
    for(unsigned int i = 0; i <= roundness+1; ++i)
    {
        sf::Vector2f pointPosition(cos(-0.5f*M_PI-(i*M_PI/(roundness*2+2)))*roundness+roundness+rectangle.Left, -sin(-0.5f*M_PI-(i*M_PI/(roundness*2+2)))*roundness+rectangle.Top+rectangle.Height-roundness);
        if(GetPointsDistance(shape.GetPointPosition(shape.GetPointsCount()-1), pointPosition)>=pointsMinimalDistance && (i != roundness+1 || GetPointsDistance(shape.GetPointPosition(0), pointPosition)>=pointsMinimalDistance))
            shape.AddPoint(pointPosition, color, outlineColor);
    }

    shape.SetOutlineThickness(outline);

    return shape;
}
