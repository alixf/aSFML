#ifndef ASFML_FPSCOUNTER_HPP
#define ASFML_FPSCOUNTER_HPP

#include <SFML/Graphics.hpp>

namespace sf
{
    class FPSCounter
    {
    public :
        FPSCounter();

        void Draw(sf::RenderWindow& window);

    private :
        unsigned int m_count;
        sf::Text m_text;
        sf::Clock m_clock;
    };
}

#endif // ASFML_FPSCOUNTER_HPP
