#include <aSFML/ui/DefaultSkin.hpp>

sf::ui::TextInput::StateSkin::StateSkin() :
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
    textShadowOffset(0.f,0.f),
    textOffset(0.f,0.f),
    placeholderSize(16.f),
    placeholderFont(const_cast<sf::Font&>(sf::Font::GetDefaultFont())),
    placeholderColor(sf::Color::Black),
    placeholderShadowColor(sf::Color::Black),
    placeholderShadowOffset(0.f,0.f),
    placeholderOffset(0.f,0.f),
    cursorColor(sf::Color::Black),
    cursorWidth(1.f),
    cursorGradientColor(sf::Color::Black),
    cursorGradientOrientation(sf::Orientation::NONE)
{
}

sf::ui::TextInput::TextInput(const std::wstring& placeholder, const sf::Vector2f& position, const sf::Vector2f& size) :
    m_backgroundRect(sf::Vector2f(0.f,0.f), size),
    m_cursorBlinkTime(500),
    m_drawCursor(false),
    m_cursorPosition(0),
    m_text(""),
    m_placeholder(placeholder),
    m_skin(sf::ui::DefaultSkin::GetInstance().GetTextInputSkin())
{
    ApplySkin();
    SetPosition(position);
}

sf::ui::TextInput::~TextInput()
{
}

sf::Vector2f sf::ui::TextInput::GetPosition() const
{
    return m_background.GetPosition();
}

sf::Vector2f sf::ui::TextInput::GetSize() const
{
    return sf::Vector2f(m_backgroundRect.Width, m_backgroundRect.Height);
}

sf::FloatRect sf::ui::TextInput::GetRect() const
{
    return m_backgroundRect;
}

std::wstring sf::ui::TextInput::GetText() const
{
    return m_text.GetString().ToWideString();
}

sf::ui::TextInput::Skin sf::ui::TextInput::GetSkin() const
{
    return m_skin;
}

void sf::ui::TextInput::SetPosition(const sf::Vector2f& position)
{
    m_backgroundRect.Left = position.x;
    m_backgroundRect.Top = position.y;
    m_background.SetPosition(position);
    m_text.SetPosition(position+sf::Vector2f(m_skin[m_state].textOffset.x, m_skin[m_state].textOffset.y));
    m_placeholder.SetPosition(position+sf::Vector2f(m_skin[m_state].placeholderOffset.x, m_skin[m_state].placeholderOffset.y));
    MoveCursor(0);
}

void sf::ui::TextInput::SetSkin(const Skin& skin)
{
    m_skin = skin;
    ApplySkin();
}

bool sf::ui::TextInput::OnEvent(const sf::Event& event)
{
    if(m_state != DISABLED)
    {
        switch(event.Type)
        {
        case sf::Event::MouseMoved :
            if(m_state != ACTIVE)
            {
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
            }
            break;

        case sf::Event::MouseButtonPressed :
            if(m_state == HOVER)
            {
                m_state = PRESSED;
                m_pressSignal();
                m_state = ACTIVE;
                return true;
            }
            if(m_state == ACTIVE)
            {
                if(!GetRect().Contains(event.MouseButton.X, event.MouseButton.Y))
                {
                    m_state = NORMAL;
                    m_desactivateSignal();
                    return true;
                }
                else
                {
                    //TODO : mouse cursor move and text selection
                }
            }
            break;

        case sf::Event::MouseButtonReleased :
            if(m_state == PRESSED)
            {
                m_state = CLICKED;
                m_clickSignal();
                m_state = ACTIVE;
                m_releaseSignal();
                m_drawCursor = true;
                m_cursorClock.Reset();
                return true;
            }
            break;

        case sf::Event::TextEntered :
            if(m_state == ACTIVE)
            {
                switch(event.Text.Unicode)
                {
                case 8 : // Backspace
                    if(m_cursorPosition > 0)
                    {
                        sf::String string = m_text.GetString();
                        string.Erase(m_cursorPosition-1);
                        m_text.SetString(string);
                        MoveCursor(-1);
                        m_valueChangeSignal(GetText());
                    }
                    break;

                case 127 : // Suppr
                    if(m_cursorPosition < m_text.GetString().GetSize())
                    {
                        sf::String string = m_text.GetString();
                        string.Erase(m_cursorPosition);
                        m_text.SetString(string);
                        m_valueChangeSignal(GetText());
                    }
                    break;

                case 13 : // Return
                    m_state = NORMAL;
                    m_submitSignal();
                    break;

                case 9 : // Tab
                    m_state = NORMAL;
                    m_switchSignal();
                    break;

                default : //TODO : make a character limit
                    sf::String string = m_text.GetString();
                    string.Insert(m_cursorPosition, event.Text.Unicode);
                    m_text.SetString(string);
                    MoveCursor(+1);
                    m_valueChangeSignal(GetText());
                    break;
                }
                return true;
            }
            break;

        case sf::Event::KeyPressed :
            if(m_state == ACTIVE)
            {
                switch(event.Key.Code)
                {
                case sf::Key::Left :
                    if(m_cursorPosition > 0)
                        MoveCursor(-1);
                    return true;
                    break;

                case sf::Key::Right :
                    if(m_cursorPosition < m_text.GetString().GetSize())
                        MoveCursor(+1);
                    return true;
                    break;

                default :
                    break;
                }
            }
            break;

        default :
            break;
        }
    }

    return false;
}

void sf::ui::TextInput::Draw(sf::RenderWindow& window)
{
    window.Draw(m_background);

    if(m_state != ACTIVE && m_text.GetString().IsEmpty()) // Draw placeholder
    {
        if(m_skin[m_state].placeholderShadowOffset != sf::Vector2f(0.f, 0.f))
        {
            m_placeholder.Move(m_skin[m_state].placeholderShadowOffset);
            m_placeholder.SetColor(m_skin[m_state].placeholderShadowColor);
            window.Draw(m_placeholder);
            m_placeholder.Move(-m_skin[m_state].placeholderShadowOffset);
            m_placeholder.SetColor(m_skin[m_state].placeholderColor);
        }
        window.Draw(m_placeholder);
    }
    else // Draw text
    {
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

    if(m_cursorClock.GetElapsedTime() > m_cursorBlinkTime)
    {
        m_drawCursor = !m_drawCursor;
        m_cursorClock.Reset();
    }
    if(m_drawCursor && m_state == ACTIVE)
        window.Draw(m_cursor);
}

void sf::ui::TextInput::MoveCursor(int offset)
{
    m_cursorPosition += offset;
    m_cursor.SetPosition(m_backgroundRect.Left+m_skin[m_state].textOffset.x+m_text.GetCharacterPos(m_cursorPosition).x, m_backgroundRect.Top+m_skin[m_state].textOffset.y);
    m_drawCursor = true;
    m_cursorClock.Reset();
}

void sf::ui::TextInput::ApplySkin()
{
    sf::Vector2f position = m_background.GetPosition();
    StateSkin stateSkin = m_skin[m_state];

    // Text
    m_text.SetCharacterSize(stateSkin.textSize);
    m_text.SetFont(stateSkin.textFont);
    m_text.SetColor(stateSkin.textColor);
    // Placeholder
    m_placeholder.SetCharacterSize(stateSkin.placeholderSize);
    m_placeholder.SetFont(stateSkin.placeholderFont);
    m_placeholder.SetColor(stateSkin.placeholderColor);
    // Background
    m_background = sf::RoundedRectangle(sf::FloatRect(0.f,0.f,m_backgroundRect.Width, m_backgroundRect.Height), stateSkin.backgroundColor, stateSkin.backgroundRoundness, stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundGradientOrientation, stateSkin.backgroundColor, stateSkin.backgroundGradientColor);
    sf::ApplyGradient(m_background, stateSkin.backgroundBorderGradientOrientation, stateSkin.backgroundBorderColor, stateSkin.backgroundBorderGradientColor, true);
    // Cursor
    m_cursor = sf::Shape::Rectangle(sf::FloatRect(0.f, 0.f, stateSkin.cursorWidth, m_backgroundRect.Height-2*stateSkin.textOffset.y), stateSkin.cursorColor);
    sf::ApplyGradient(m_cursor, stateSkin.cursorGradientOrientation, stateSkin.cursorColor, stateSkin.cursorGradientColor);

    SetPosition(position);
}

boost::signals::connection& sf::ui::TextInput::OnSwitch(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_switchSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::TextInput::OnSubmit(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_submitSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::TextInput::OnValueChange(boost::signal<void (const std::wstring&)>::slot_type slot)
{
    m_connections.push_back(m_valueChangeSignal.connect(slot));
    return m_connections.back();
}
