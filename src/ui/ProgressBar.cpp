#include <aSFML/ui/DefaultSkin.hpp>

sf::ui::ProgressBar::StateSkin::StateSkin() :
    backgroundColor(sf::Color::White),
    backgroundRoundness(0.f),
    backgroundGradientColor(sf::Color::White),
    backgroundGradientOrientation(sf::Orientation::NONE),
    backgroundBorderColor(sf::Color::Red),
    backgroundBorderThickness(0.f),
    backgroundBorderGradientColor(sf::Color::White),
    backgroundBorderGradientOrientation(sf::Orientation::NONE),
    fillColor(sf::Color::Black),
    fillRoundness(0.f),
    fillGradientColor(sf::Color::Black),
    fillGradientOrientation(sf::Orientation::NONE),
    fillMargin(1.f, 1.f, 1.f, 1.f),
    fillBorderColor(sf::Color::Black),
    fillBorderThickness(0.f),
    fillBorderGradientColor(sf::Color::Black),
    fillBorderGradientOrientation(sf::Orientation::NONE),
    textSize(16.f),
    textFont(const_cast<sf::Font&>(sf::Font::GetDefaultFont())),
    textColor(sf::Color(127,127,127)),
    textShadowColor(sf::Color(127,127,127)),
    textShadowOffset(0.f, 0.f)
{
}

sf::ui::ProgressBar::ProgressBar(float progress, const sf::Vector2f& position, const sf::Vector2f& size) :
    m_progress(progress),
    m_backgroundRect(position, size),
    m_fillRect(position+sf::Vector2f(1.f,1.f), size+sf::Vector2f(-size.x, -2.f)),
    m_skin(sf::ui::DefaultSkin::GetInstance().GetProgressBarSkin())
{
    ApplySkin();
    SetPosition(position);
}

sf::ui::ProgressBar::~ProgressBar()
{
}

sf::Vector2f sf::ui::ProgressBar::GetPosition() const
{
    return m_background.GetPosition();
}

sf::FloatRect sf::ui::ProgressBar::GetRect() const
{
    return m_backgroundRect;
}

sf::Vector2f sf::ui::ProgressBar::GetSize() const
{
    return sf::Vector2f(m_backgroundRect.Width, m_backgroundRect.Height);
}

float sf::ui::ProgressBar::GetProgress() const
{
    return m_progress;
}

sf::ui::ProgressBar::Skin sf::ui::ProgressBar::GetSkin() const
{
    return m_skin;
}

void sf::ui::ProgressBar::SetPosition(const sf::Vector2f& position)
{
    m_backgroundRect.Left = position.x;
    m_backgroundRect.Top = position.y;
    m_background.SetPosition(position);
    m_fillRect.Left = position.x+m_skin[m_state].fillMargin.Left;
    m_fillRect.Top = position.y+m_skin[m_state].fillMargin.Top;
    m_fill.SetPosition(sf::Vector2f(m_fillRect.Left, m_fillRect.Top));
}

void sf::ui::ProgressBar::SetSize(const sf::Vector2f& size)
{
    m_backgroundRect.Width = size.x;
    m_backgroundRect.Height = size.y;
    ApplySkin();
}

void sf::ui::ProgressBar::SetProgress(float progress)
{
    m_progress = progress;
    StateSkin stateSkin = m_skin[m_state];
    sf::Vector2f position = GetPosition();

    m_fillRect.Width = (m_backgroundRect.Width-stateSkin.fillMargin.Left-stateSkin.fillMargin.Width)*progress;
    m_fill = sf::RoundedRectangle(sf::FloatRect(0.f, 0.f, m_fillRect.Width, m_fillRect.Height), stateSkin.fillColor, stateSkin.fillRoundness, stateSkin.fillBorderThickness, stateSkin.fillBorderColor);
    sf::ApplyGradient(m_fill, stateSkin.fillGradientOrientation, stateSkin.fillColor, stateSkin.fillGradientColor);
    sf::ApplyGradient(m_fill, stateSkin.fillBorderGradientOrientation, stateSkin.fillBorderColor, stateSkin.fillBorderGradientColor, true);
    SetPosition(position);

    m_valueChangeSignal(m_progress);
}

void sf::ui::ProgressBar::SetSkin(const sf::ui::ProgressBar::Skin& skin)
{
    m_skin = skin;
    ApplySkin();
}

void sf::ui::ProgressBar::SetState(sf::ui::ProgressBar::State state)
{
    if(m_state != state)
    {
        m_state = state;
        ApplySkin();
    }
}

bool sf::ui::ProgressBar::OnEvent(const sf::Event& event)
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
                    SetState(HOVER);
                    m_hoverSignal();
                    return true;
                }
            }
            else if(m_state != NORMAL)
            {
                SetState(NORMAL);
                m_leaveSignal();
                return true;
            }
            break;

        case sf::Event::MouseButtonPressed :
            if(m_state == HOVER)
            {
                SetState(PRESSED);
                m_pressSignal();
                return true;
            }
            break;

        case sf::Event::MouseButtonReleased :
            if(m_state == PRESSED && GetRect().Contains(event.MouseButton.X, event.MouseButton.Y))
            {
                m_state = CLICKED;
                m_clickSignal();
                SetState(HOVER);
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

void sf::ui::ProgressBar::Draw(sf::RenderWindow& window)
{
    window.Draw(m_background);
    window.Draw(m_fill);
}

void sf::ui::ProgressBar::ApplySkin()
{
    sf::Vector2f position = GetPosition();
    StateSkin stateSkin = m_skin[m_state];

    m_background = sf::RoundedRectangle(sf::FloatRect(0.f, 0.f, m_backgroundRect.Width, m_backgroundRect.Height), stateSkin.backgroundColor, stateSkin.backgroundRoundness, stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundGradientOrientation, stateSkin.backgroundColor, stateSkin.backgroundGradientColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundBorderGradientOrientation, stateSkin.backgroundBorderColor, stateSkin.backgroundBorderGradientColor, true);

    SetProgress(m_progress);
    SetPosition(position);
}

boost::signals::connection&  sf::ui::ProgressBar::OnValueChange(boost::signal<void (float)>::slot_type slot)
{
    m_connections.push_back(m_valueChangeSignal.connect(slot));
    return m_connections.back();
}
