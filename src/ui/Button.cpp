#include <aSFML/ui/DefaultSkin.hpp>

sf::ui::Button::StateSkin::StateSkin() :
    backgroundColor(sf::Color::White),
    backgroundRoundness(0.f),
    backgroundGradientColor(sf::Color::White),
    backgroundGradientOrientation(sf::Orientation::NONE),
    backgroundBorderColor(sf::Color::White),
    backgroundBorderThickness(0.f),
    backgroundBorderGradientColor(sf::Color::White),
    backgroundBorderGradientOrientation(sf::Orientation::NONE),
    textSize(16.f),
    textFont(const_cast<sf::Font&>(sf::Font::GetDefaultFont())),
    textColor(sf::Color::Black),
    textShadowColor(sf::Color::Black),
    textShadowOffset(sf::Vector2f(0.f, 0.f)),
    textMargin(sf::FloatRect(0.f,0.f,0.f,0.f))
{
}

sf::ui::Button::Button(const std::wstring& text, const sf::Vector2f& position, const sf::Vector2f& size) :
    m_backgroundRect(0.f, 0.f, (size.x == -1.f) ? 0.f : size.x, (size.y == -1.f) ? 0.f : size.y),
    m_size(size),
    m_text(text),
    m_skin(sf::ui::DefaultSkin::GetInstance().GetButtonSkin())
{
    ApplySkin();
    SetPosition(position);
}

sf::ui::Button::~Button()
{
}

sf::Vector2f sf::ui::Button::GetPosition() const
{
    return m_background.GetPosition();
}

sf::Vector2f sf::ui::Button::GetSize() const
{
    return sf::Vector2f(m_backgroundRect.Width, m_backgroundRect.Height);
}

sf::FloatRect sf::ui::Button::GetRect() const
{
    return m_backgroundRect;
}

std::wstring sf::ui::Button::GetString() const
{
    return m_text.GetString().ToWideString();
}

sf::ui::Button::Skin sf::ui::Button::GetSkin() const
{
    return m_skin;
}

void sf::ui::Button::SetPosition(const sf::Vector2f& position)
{
    m_backgroundRect.Left = position.x;
    m_backgroundRect.Top = position.y;
    m_background.SetPosition(position);
    m_text.SetPosition(position+sf::Vector2f(m_skin[m_state].textMargin.Left, m_skin[m_state].textMargin.Top));
}

void sf::ui::Button::SetString(const std::wstring& string)
{
    m_text.SetString(string);
    ApplySkin();
}

void sf::ui::Button::SetSkin(sf::ui::Button::Skin& skin)
{
    m_skin = skin;
    ApplySkin();
}

void sf::ui::Button::OnEvent(const sf::Event& event)
{
    if(m_state != DISABLED)
    {
        State previousState = m_state;

        switch(event.Type)
        {
        case sf::Event::MouseMoved :
            if(GetRect().Contains(event.MouseMove.X, event.MouseMove.Y))
            {
                if(m_state == NORMAL)
                {
                    m_state = HOVER;
                    m_hoverSignal();
                }
            }
            else if(m_state != NORMAL)
            {
                m_state = NORMAL;
                m_leaveSignal();
            }
            break;

        case sf::Event::MouseButtonPressed :
            if(m_state == HOVER)
            {
                m_state = PRESSED;
                m_pressSignal();
            }
            break;

        case sf::Event::MouseButtonReleased :
            if(m_state == PRESSED && GetRect().Contains(event.MouseButton.X, event.MouseButton.Y))
            {
                m_state = CLICKED;
                m_clickSignal();
                m_state = HOVER;
                m_releaseSignal();
            }
            break;

        default :
            break;
        }

        if(m_state != previousState)
            ApplySkin();
    }
}

void sf::ui::Button::Draw(sf::RenderWindow& window)
{
    window.Draw(m_background);
    if(m_skin[m_state].textShadowOffset != sf::Vector2f(0.f, 0.f))
    {
        m_text.Move(m_skin[m_state].textShadowOffset);
        m_text.SetColor(m_skin[m_state].textShadowColor);
        window.Draw(m_text);
        m_text.Move(-m_skin[m_state].textShadowOffset);
        m_text.SetColor(m_skin[m_state].textColor);
    }
    window.Draw(m_text);
}

void sf::ui::Button::ApplySkin()
{
    sf::Vector2f position = GetPosition();
    StateSkin stateSkin = m_skin[m_state];

    // Text
    m_text.SetFont(stateSkin.textFont);
    m_text.SetColor(stateSkin.textColor);
    m_text.SetCharacterSize(stateSkin.textSize);

    // Background
    if(m_size != sf::Vector2f(-1.f, -1.f)) // background has a fixed size
        m_backgroundRect = sf::FloatRect(sf::Vector2f(0.f, 0.f), m_size);
    else // background size dynamically generated from text size
        m_backgroundRect = sf::FloatRect(0.f,0.f,m_text.GetRect().Width+stateSkin.textMargin.Left+stateSkin.textMargin.Width, m_text.GetRect().Height+stateSkin.textMargin.Top+stateSkin.textMargin.Height);

    m_background = sf::RoundedRectangle(m_backgroundRect, stateSkin.backgroundColor, stateSkin.backgroundRoundness, stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundGradientOrientation, stateSkin.backgroundColor, stateSkin.backgroundGradientColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundBorderGradientOrientation, stateSkin.backgroundBorderColor, stateSkin.backgroundBorderGradientColor, true);

    SetPosition(position);
}
