#include <aSFML/ui/DefaultSkin.hpp>

sf::ui::Slider::StateSkin::StateSkin() :
    rangeHeight(4.f),
    rangeRoundness(0.f),
    rangeColor(sf::Color::White),
    rangeGradientColor(sf::Color::White),
    rangeGradientOrientation(sf::Orientation::NONE),
    rangeBorderThickness(0.f),
    rangeBorderColor(sf::Color::White),
    rangeBorderGradientColor(sf::Color::White),
    rangeBorderGradientOrientation(sf::Orientation::NONE),
    cursorWidth(10.f),
    cursorRoundness(0.f),
    cursorColor(sf::Color::Black),
    cursorGradientColor(sf::Color::Black),
    cursorGradientOrientation(sf::Orientation::NONE),
    cursorBorderThickness(0.f),
    cursorBorderColor(sf::Color::Black),
    cursorBorderGradientColor(sf::Color::Black),
    cursorBorderGradientOrientation(sf::Orientation::NONE)
{
}

sf::ui::Slider::Slider(float value, const sf::Vector2f& position, const sf::Vector2f& size) :
    m_value(0.f),
    m_cursorMouseOffset(0.f),
    m_dragAndDrop(false),
    m_boundingRect(sf::Vector2f(0.f, 0.f), size),
    m_rangeRect(0.f, 0.f, m_boundingRect.Width, 0.f), // We set height to 0.f, it cause it depends on the skin and will be corrected in ApplySkin
    m_cursorRect(0.f, 0.f, 0.f, m_boundingRect.Height), // Same here with the width
    m_skin(sf::ui::DefaultSkin::GetInstance().GetSliderSkin())
{
    ApplySkin();
    SetPosition(position);
}

sf::ui::Slider::~Slider()
{
}

sf::Vector2f sf::ui::Slider::GetPosition() const
{
    return sf::Vector2f(m_boundingRect.Left, m_boundingRect.Top);
}

sf::Vector2f sf::ui::Slider::GetSize() const
{
    return sf::Vector2f(m_boundingRect.Width, m_boundingRect.Height);
}

sf::FloatRect sf::ui::Slider::GetRect() const
{
    return m_boundingRect;
}

float sf::ui::Slider::GetValue() const
{
    return m_value;
}

sf::ui::Slider::Skin sf::ui::Slider::GetSkin() const
{
    return m_skin;
}

void sf::ui::Slider::SetPosition(const sf::Vector2f& position)
{
    m_boundingRect.Left = position.x;
    m_boundingRect.Top = position.y;

    m_rangeRect.Left = position.x;
    m_rangeRect.Top = m_boundingRect.Top+m_boundingRect.Height/2-m_rangeRect.Height/2;
    m_range.SetPosition(m_rangeRect.Left, m_rangeRect.Top);

    m_cursorRect.Top = position.y; // We only set vertical position here, horizontal will be set in the SetValue call
    SetValue(m_value);
}

void sf::ui::Slider::SetSize(const sf::Vector2f& size)
{
    m_boundingRect.Width = size.x;
    m_rangeRect.Width = size.x;
    m_boundingRect.Height = size.y;
    m_cursorRect.Height = size.y;
    ApplySkin();
}

void sf::ui::Slider::SetValue(float value)
{
    bool valueChanged = (value != m_value) ? true : false;

    m_value = (value < 0.f) ? 0.f : (value > 1.f) ? 1.f : value;
    m_cursorRect.Left = m_boundingRect.Left+(m_boundingRect.Width-m_cursorRect.Width)*m_value;
    m_cursor.SetPosition(ceil(m_cursorRect.Left), ceil(m_cursorRect.Top));

    if(valueChanged)
        m_valueChangeSignal(m_value);
}

void sf::ui::Slider::SetSkin(const sf::ui::Slider::Skin& skin)
{
    m_skin = skin;
    ApplySkin();
}

void sf::ui::Slider::SetState(sf::ui::Slider::State state)
{
    if(m_state != state)
    {
        m_state = state;
        ApplySkin();
    }
}

bool sf::ui::Slider::OnEvent(const sf::Event& event)
{
    if(m_state != DISABLED)
    {
        switch(event.Type)
        {
        case sf::Event::MouseMoved :
            if(m_dragAndDrop)
            {
                SetValue((event.MouseMove.X-m_boundingRect.Left)/m_boundingRect.Width);
                return true;
            }
            if(m_boundingRect.Contains(event.MouseMove.X, event.MouseMove.Y))
            {
                if(m_state != HOVER)
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
                m_pressSignal();
                SetState(PRESSED);

                m_dragAndDrop = true;
                if(m_cursorRect.Contains(event.MouseButton.X, event.MouseButton.Y)) // Mouse button pressed on cursor
                    m_cursorMouseOffset = event.MouseButton.X-m_cursorRect.Left;
                else // Mouse button pressed outside of cursor (range)
                {
                    m_cursorMouseOffset = m_cursorRect.Width/2;
                    SetValue((event.MouseButton.X-m_boundingRect.Left)/m_boundingRect.Width);
                }
                return true;
            }
            break;

        case sf::Event::MouseButtonReleased :
            if(m_boundingRect.Contains(event.MouseButton.X, event.MouseButton.Y) && m_state == PRESSED)
            {
                m_state = CLICKED;
                m_clickSignal();
                SetState(HOVER);
                return true;
            }
            else if(m_dragAndDrop)
            {
                SetState(NORMAL);
                m_releaseSignal();
                return true;
            }
            m_dragAndDrop = false;
            break;

        default :
            break;
        }
    }

    return false;
}

void sf::ui::Slider::Draw(sf::RenderWindow& window)
{
    window.Draw(m_range);
    window.Draw(m_cursor);
}

void sf::ui::Slider::ApplySkin()
{
    sf::Vector2f position = GetPosition();
    StateSkin stateSkin = m_skin[m_state];

    m_rangeRect.Height = stateSkin.rangeHeight;
    m_cursorRect.Width = stateSkin.cursorWidth;

    m_range = sf::RoundedRectangle(sf::FloatRect(0.f, 0.f, m_rangeRect.Width, m_rangeRect.Height), stateSkin.rangeColor, stateSkin.rangeRoundness, stateSkin.rangeBorderThickness, stateSkin.rangeBorderColor);
    sf::ApplyGradient(m_range, stateSkin.rangeGradientOrientation, stateSkin.rangeColor, stateSkin.rangeGradientColor);
    sf::ApplyGradient(m_range, stateSkin.rangeBorderGradientOrientation, stateSkin.rangeBorderColor, stateSkin.rangeBorderGradientColor, true);

    m_cursor = sf::RoundedRectangle(sf::FloatRect(0.f, 0.f, m_cursorRect.Width, m_cursorRect.Height), stateSkin.cursorColor, stateSkin.cursorRoundness, stateSkin.cursorBorderThickness, stateSkin.cursorBorderColor);
    sf::ApplyGradient(m_cursor, stateSkin.cursorGradientOrientation, stateSkin.cursorColor, stateSkin.cursorGradientColor);
    sf::ApplyGradient(m_cursor, stateSkin.cursorBorderGradientOrientation, stateSkin.cursorBorderColor, stateSkin.cursorBorderGradientColor, true);

    SetPosition(position);
}

boost::signals::connection& sf::ui::Slider::OnValueChange(boost::signal<void (float)>::slot_type slot)
{
    m_connections.push_back(m_valueChangeSignal.connect(slot));
    return m_connections.back();
}
