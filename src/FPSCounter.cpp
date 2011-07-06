#include <aSFML/FPSCounter.hpp>
#include <sstream>

sf::FPSCounter::FPSCounter() :
    m_count(0),
    m_text("FPS : Wait ...", sf::Font::GetDefaultFont(), 11)
{
    m_text.SetColor(sf::Color::White);
}

void sf::FPSCounter::Draw(sf::RenderWindow& window)
{
    if(m_clock.GetElapsedTime() >= 1000)
    {
        std::stringstream ss;
        ss << "FPS : " << m_count;
        m_text.SetString(ss.str());
        m_count = 0;
        m_clock.Reset();
    }
    else
        m_count++;

    window.Draw(m_text);
}
