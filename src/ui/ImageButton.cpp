#include <aSFML/ui/ImageButton.hpp>

sf::ui::ImageButton::ImageButton(const sf::Image& image, const sf::Vector2f& position)
{
    SetImage(image);
    SetPosition(position);
}

sf::ui::ImageButton::~ImageButton()
{
}

sf::Vector2f sf::ui::ImageButton::GetPosition() const
{
    return m_sprites.at(NORMAL).GetPosition();
}

float sf::ui::ImageButton::GetRotation() const
{
    return m_sprites.at(NORMAL).GetRotation();
}

sf::Vector2f sf::ui::ImageButton::GetScale() const
{
    return m_sprites.at(NORMAL).GetScale();
}

sf::Color sf::ui::ImageButton::GetColor() const
{
    return m_sprites.at(NORMAL).GetColor();
}

sf::FloatRect sf::ui::ImageButton::GetRect() const
{
    sf::IntRect subRect = m_sprites.at(NORMAL).GetSubRect();
    return sf::FloatRect(GetPosition(), sf::Vector2f(subRect.Width, subRect.Height));
}

void sf::ui::ImageButton::SetPosition(const sf::Vector2f& position)
{
    m_sprites[DISABLED].SetPosition(position);
    m_sprites[NORMAL].SetPosition(position);
    m_sprites[HOVER].SetPosition(position);
    m_sprites[PRESSED].SetPosition(position);
}

void sf::ui::ImageButton::SetRotation(float angle)
{
    m_sprites[DISABLED].SetRotation(angle);
    m_sprites[NORMAL].SetRotation(angle);
    m_sprites[HOVER].SetRotation(angle);
    m_sprites[PRESSED].SetRotation(angle);
}

void sf::ui::ImageButton::SetScale(const sf::Vector2f& factor)
{
    m_sprites[DISABLED].SetScale(factor);
    m_sprites[NORMAL].SetScale(factor);
    m_sprites[HOVER].SetScale(factor);
    m_sprites[PRESSED].SetScale(factor);
}

void sf::ui::ImageButton::SetColor(const sf::Color& color)
{
    m_sprites[DISABLED].SetColor(color);
    m_sprites[NORMAL].SetColor(color);
    m_sprites[HOVER].SetColor(color);
    m_sprites[PRESSED].SetColor(color);
}

void sf::ui::ImageButton::SetImage(const sf::Image& image, bool resetSpritesSubRects)
{
    m_sprites[DISABLED].SetImage(image, resetSpritesSubRects);
    m_sprites[NORMAL].SetImage(image, resetSpritesSubRects);
    m_sprites[HOVER].SetImage(image, resetSpritesSubRects);
    m_sprites[PRESSED].SetImage(image, resetSpritesSubRects);
}

void sf::ui::ImageButton::Move(const sf::Vector2f& offset)
{
    m_sprites[DISABLED].Move(offset);
    m_sprites[NORMAL].Move(offset);
    m_sprites[HOVER].Move(offset);
    m_sprites[PRESSED].Move(offset);
}

void sf::ui::ImageButton::Rotate(float angle)
{
    m_sprites[DISABLED].Rotate(angle);
    m_sprites[NORMAL].Rotate(angle);
    m_sprites[HOVER].Rotate(angle);
    m_sprites[PRESSED].Rotate(angle);
}

void sf::ui::ImageButton::Scale(const sf::Vector2f& factor)
{
    m_sprites[DISABLED].Scale(factor);
    m_sprites[NORMAL].Scale(factor);
    m_sprites[HOVER].Scale(factor);
    m_sprites[PRESSED].Scale(factor);
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
