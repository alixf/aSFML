#include <aSFML/ui/DefaultSkin.hpp>

sf::ui::Switch::StateSkin::StateSkin() :
    backgroundColor(sf::Color::White),
    backgroundRoundness(0.f),
    backgroundGradientColor(sf::Color::White),
    backgroundGradientOrientation(sf::Orientation::NONE),
    backgroundBorderColor(sf::Color::White),
    backgroundBorderThickness(0.f),
    backgroundBorderGradientColor(sf::Color::White),
    backgroundBorderGradientOrientation(sf::Orientation::NONE),
    switchColor(sf::Color::Black),
    switchRoundness(0.f),
    switchGradientColor(sf::Color::Black),
    switchGradientOrientation(sf::Orientation::NONE),
    switchMargin(sf::Vector2f(0.f, 0.f)),
    switchBorderColor(sf::Color::Black),
    switchBorderThickness(0.f),
    switchBorderGradientColor(sf::Color::Black),
    switchBorderGradientOrientation(sf::Orientation::NONE),
    onTextSize(16.f),
    onTextFont(const_cast<sf::Font&>(sf::Font::GetDefaultFont())),
    onTextColor(sf::Color::Blue),
    onTextShadowColor(sf::Color::Black),
    onTextShadowOffset(sf::Vector2f(0.f, 0.f)),
    onTextMargin(sf::Vector2f(0.f, 0.f)),
    offTextSize(16.f),
    offTextFont(const_cast<sf::Font&>(sf::Font::GetDefaultFont())),
    offTextColor(sf::Color::Red),
    offTextShadowColor(sf::Color::Black),
    offTextShadowOffset(sf::Vector2f(0.f, 0.f)),
    offTextMargin(sf::Vector2f(0.f, 0.f))
{
}

sf::ui::Switch::Switch(bool value, sf::Vector2f position, sf::Vector2f size) :
    m_value(value),
    m_backgroundRect(sf::Vector2f(0.f,0.f),size),
    m_onText("ON"),
    m_offText("OFF"),
    m_skin(sf::ui::DefaultSkin::GetInstance().GetSwitchSkin())
{
    ApplySkin();
    SetPosition(position);
}

sf::ui::Switch::~Switch()
{
}

sf::Vector2f sf::ui::Switch::GetPosition() const
{
    return m_background.GetPosition();
}

sf::Vector2f sf::ui::Switch::GetSize() const
{
    return sf::Vector2f(m_backgroundRect.Width, m_backgroundRect.Height);
}

bool sf::ui::Switch::GetValue() const
{
    return m_value;
}

sf::FloatRect sf::ui::Switch::GetRect() const
{
    return m_backgroundRect;
}

sf::ui::Switch::Skin sf::ui::Switch::GetSkin() const
{
    return m_skin;
}

void sf::ui::Switch::SetPosition(const sf::Vector2f& position)
{
    m_backgroundRect.Left = position.x;
    m_backgroundRect.Top = position.y;
    m_background.SetPosition(position);
    m_onText.SetPosition(ceil(m_backgroundRect.Left+m_backgroundRect.Width/4-m_onText.GetRect().Width/2), ceil(m_backgroundRect.Top+m_backgroundRect.Height/2-m_onText.GetRect().Height/2));
    m_offText.SetPosition(ceil(m_backgroundRect.Left+m_backgroundRect.Width*3/4-m_offText.GetRect().Width/2), ceil(m_backgroundRect.Top+m_backgroundRect.Height/2-m_offText.GetRect().Height/2));
    m_switch.SetPosition((m_value) ? position.x-m_skin[m_state].switchMargin.x+m_backgroundRect.Width/2 : position.x+m_skin[m_state].switchMargin.x, position.y+m_skin[m_state].switchMargin.y);
}

void sf::ui::Switch::SetSize(const sf::Vector2f& size)
{
    m_backgroundRect.Width = size.x;
    m_backgroundRect.Height = size.y;
    ApplySkin();
}

void sf::ui::Switch::SetValue(bool value)
{
    if(m_value != value)
    {
        m_value = value;
        m_valueChangeSignal(m_value);
    }
}

void sf::ui::Switch::SetSkin(const Skin& skin)
{
    m_skin = skin;
    ApplySkin();
}

void sf::ui::Switch::OnEvent(const sf::Event& event)
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
                SetValue(!GetValue());
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

void sf::ui::Switch::Draw(sf::RenderWindow& window)
{
    if(m_state != DISABLED)
    {
        window.Draw(m_background);

        if(m_value)
        {
            if(m_skin[m_state].onTextShadowOffset != sf::Vector2f(0.f, 0.f))
            {
                m_onText.Move(m_skin[m_state].onTextShadowOffset);
                m_onText.SetColor(m_skin[m_state].onTextShadowColor);
                window.Draw(m_onText);
                m_onText.Move(-m_skin[m_state].onTextShadowOffset);
                m_onText.SetColor(m_skin[m_state].onTextColor);
            }
            window.Draw(m_onText);
        }
        else
        {
            if(m_skin[m_state].offTextShadowOffset != sf::Vector2f(0.f, 0.f))
            {
                m_offText.Move(m_skin[m_state].offTextShadowOffset);
                m_offText.SetColor(m_skin[m_state].offTextShadowColor);
                window.Draw(m_offText);
                m_offText.Move(-m_skin[m_state].offTextShadowOffset);
                m_offText.SetColor(m_skin[m_state].offTextColor);
            }
            window.Draw(m_offText);
        }
        window.Draw(m_switch);
    }
}

void sf::ui::Switch::ApplySkin()
{
    sf::Vector2f position = GetPosition();
    StateSkin stateSkin = m_skin[m_state];

    // Background
    m_background = sf::RoundedRectangle(sf::FloatRect(0.f, 0.f, m_backgroundRect.Width, m_backgroundRect.Height), stateSkin.backgroundColor, stateSkin.backgroundRoundness, stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundGradientOrientation, stateSkin.backgroundColor, stateSkin.backgroundGradientColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundBorderGradientOrientation, stateSkin.backgroundBorderColor, stateSkin.backgroundBorderGradientColor, true);
    // Off text
    m_offText.SetFont(stateSkin.offTextFont);
    m_offText.SetColor(stateSkin.offTextColor);
    m_offText.SetCharacterSize(stateSkin.offTextSize);
    // On text
    m_onText.SetFont(stateSkin.onTextFont);
    m_onText.SetColor(stateSkin.onTextColor);
    m_onText.SetCharacterSize(stateSkin.onTextSize);
    // Switch
    m_switch = sf::RoundedRectangle(sf::FloatRect(0, 0, m_backgroundRect.Width/2, m_backgroundRect.Height-stateSkin.switchMargin.y*2),
                                    stateSkin.switchColor, stateSkin.switchRoundness, stateSkin.switchBorderThickness, stateSkin.switchBorderColor);

    sf::ApplyGradient(m_switch, stateSkin.switchGradientOrientation, stateSkin.switchColor, stateSkin.switchGradientColor);
    sf::ApplyGradient(m_switch, stateSkin.switchBorderGradientOrientation, stateSkin.switchBorderColor, stateSkin.switchBorderGradientColor, true);

    SetPosition(position);
}

boost::signals::connection& sf::ui::Switch::OnValueChange(boost::signal<void (bool)>::slot_type slot)
{
    m_connections.push_back(m_valueChangeSignal.connect(slot));
    return m_connections.back();
}
