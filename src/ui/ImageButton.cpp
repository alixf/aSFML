#include <aSFML/ui/ImageButton.hpp>

sf::ui::ImageButton::ImageButton(const sf::Image& image, const sf::Vector2f& position)
{
    // We iterate manually though all state enumeration values once to fill the map
    m_sprites[NORMAL].SetPosition(position);
    m_sprites[HOVER].SetPosition(position);
    m_sprites[PRESSED].SetPosition(position);
    m_sprites[CLICKED].SetPosition(position);
    m_sprites[DISABLED].SetPosition(position);

    for(std::map<State, sf::Sprite>::iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
        it->second.SetImage(image);
}

sf::ui::ImageButton::~ImageButton()
{
}

sf::Vector2f sf::ui::ImageButton::GetPosition()
{
    return m_sprites[m_state].GetPosition();
}

sf::FloatRect sf::ui::ImageButton::GetRect()
{
    sf::IntRect subRect = m_sprites[m_state].GetSubRect();
    return sf::FloatRect(GetPosition(), sf::Vector2f(subRect.Width, subRect.Height));
}

void sf::ui::ImageButton::SetPosition(const sf::Vector2f& position)
{
    for(std::map<State, sf::Sprite>::iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
        it->second.SetPosition(position);
}

void sf::ui::ImageButton::SplitImage(sf::ui::ImageButton::SplitOrientation orientation, const std::vector<unsigned int>& states)
{
    for(unsigned int i = 0; i < states.size(); ++i)
    {
        sf::IntRect subRect;
        if(orientation == HORIZONTALLY)
            subRect = sf::IntRect(i*m_sprites[NORMAL].GetImage()->GetWidth()/states.size(), 0, m_sprites[NORMAL].GetImage()->GetWidth()/states.size(), m_sprites[NORMAL].GetImage()->GetHeight());
        else
            subRect = sf::IntRect(0, i*m_sprites[NORMAL].GetImage()->GetHeight()/states.size(), m_sprites[NORMAL].GetImage()->GetWidth(), m_sprites[NORMAL].GetImage()->GetHeight()/states.size());

        if(states[i] & NORMAL)
            m_sprites[NORMAL].SetSubRect(subRect);
        if(states[i] & HOVER)
            m_sprites[HOVER].SetSubRect(subRect);
        if(states[i] & PRESSED)
            m_sprites[PRESSED].SetSubRect(subRect);
        if(states[i] & CLICKED)
            m_sprites[CLICKED].SetSubRect(subRect);
        if(states[i] & DISABLED)
            m_sprites[DISABLED].SetSubRect(subRect);
    }
}

bool sf::ui::ImageButton::OnEvent(const sf::Event& event)
{
    if(m_state != DISABLED)
    {
        switch(event.Type)
        {
        case sf::Event::MouseMoved :
            if(GetRect().Contains(event.MouseMove.X, event.MouseMove.Y))
            {
                if(m_state == NORMAL)
                {
                    m_state = HOVER;
                    m_hoverSignal();
                    return true;
                }
            }
            else if(m_state != NORMAL)
            {
                m_state = NORMAL;
                m_leaveSignal();
                return true;
            }
            break;

        case sf::Event::MouseButtonPressed :
            if(m_state == HOVER)
            {
                m_state = PRESSED;
                m_pressSignal();
                return true;
            }
            break;

        case sf::Event::MouseButtonReleased :
            if(m_state == PRESSED && GetRect().Contains(event.MouseButton.X, event.MouseButton.Y))
            {
                m_state = CLICKED;
                m_clickSignal();
                m_state = HOVER;
                m_releaseSignal();
                return true;
            }
            break;

        default :
            break;
        }
    }

    return false;
}

void sf::ui::ImageButton::Draw(sf::RenderWindow& window)
{
    window.Draw(m_sprites[m_state]);
}
