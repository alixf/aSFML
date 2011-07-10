#include <aSFML/ui/Button.hpp>
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
    textCharacterSize(16.f),
    textFont(const_cast<sf::Font&>(sf::Font::GetDefaultFont())),
    textColor(sf::Color::Black),
    textShadowColor(sf::Color::Black),
    textShadowOffset(sf::Vector2f(0.f, 0.f)),
    textMargin(sf::FloatRect(0.f,0.f,0.f,0.f))
{
}

sf::ui::Button::Button(const std::wstring& text, const sf::Vector2f& position, const sf::Vector2f& size) :
    m_string(text),
    m_skin(sf::ui::DefaultSkin::GetInstance().GetButtonSkin())
{
    m_renderImages[DISABLED] = new sf::RenderImage();
    m_renderImages[NORMAL] = new sf::RenderImage();
    m_renderImages[HOVER] = new sf::RenderImage();
    m_renderImages[PRESSED] = new sf::RenderImage();

    if(size == sf::Vector2f(-1.f, -1.f))
        ApplySkin();
    else
        ApplySkin(size);
    SetPosition(position);
}

sf::ui::Button::~Button()
{
    for(std::map<State, sf::RenderImage*>::iterator it = m_renderImages.begin(); it != m_renderImages.end(); ++it)
        delete it->second;
}

sf::ui::Button::Skin sf::ui::Button::GetSkin() const
{
    return m_skin;
}

sf::Vector2f sf::ui::Button::GetSize() const
{
    return sf::Vector2f(m_sprites.at(NORMAL).GetSubRect().Width, m_sprites.at(NORMAL).GetSubRect().Height);
}

sf::FloatRect sf::ui::Button::GetRect() const
{
    return sf::FloatRect(GetPosition(), sf::Vector2f(m_sprites.at(NORMAL).GetSubRect().Width, m_sprites.at(NORMAL).GetSubRect().Height));
}

std::wstring sf::ui::Button::GetString() const
{
    return m_string;
}

sf::Vector2f sf::ui::Button::GetPosition() const
{
    return m_sprites.at(NORMAL).GetPosition();
}

float sf::ui::Button::GetRotation() const
{
    return m_sprites.at(NORMAL).GetRotation();
}

sf::Vector2f sf::ui::Button::GetScale() const
{
    return m_sprites.at(NORMAL).GetScale();
}

sf::Color sf::ui::Button::GetColor() const
{
    return m_sprites.at(NORMAL).GetColor();
}

void sf::ui::Button::SetState(State state)
{
    m_state = state;
}

void sf::ui::Button::SetSkin(Skin& skin)
{
    m_skin = skin;
    ApplySkin();
}

void sf::ui::Button::SetSize(const sf::Vector2f& size)
{
    ApplySkin(size);
}

void sf::ui::Button::SetString(const std::wstring& string)
{
    m_string = string;
    ApplySkin();
}

void sf::ui::Button::SetPosition(const sf::Vector2f& position)
{
    m_sprites[DISABLED].SetPosition(position);
    m_sprites[NORMAL].SetPosition(position);
    m_sprites[HOVER].SetPosition(position);
    m_sprites[PRESSED].SetPosition(position);
}

void sf::ui::Button::SetRotation(float angle)
{
    m_sprites[DISABLED].SetRotation(angle);
    m_sprites[NORMAL].SetRotation(angle);
    m_sprites[HOVER].SetRotation(angle);
    m_sprites[PRESSED].SetRotation(angle);
}

void sf::ui::Button::SetScale(const sf::Vector2f& factor)
{
    m_sprites[DISABLED].SetScale(factor);
    m_sprites[NORMAL].SetScale(factor);
    m_sprites[HOVER].SetScale(factor);
    m_sprites[PRESSED].SetScale(factor);
}

void sf::ui::Button::SetColor(const sf::Color& color)
{
    m_sprites[DISABLED].SetColor(color);
    m_sprites[NORMAL].SetColor(color);
    m_sprites[HOVER].SetColor(color);
    m_sprites[PRESSED].SetColor(color);
}

void sf::ui::Button::Move(const sf::Vector2f& offset)
{
    m_sprites[DISABLED].Move(offset);
    m_sprites[NORMAL].Move(offset);
    m_sprites[HOVER].Move(offset);
    m_sprites[PRESSED].Move(offset);
}

void sf::ui::Button::Rotate(float angle)
{
    m_sprites[DISABLED].Rotate(angle);
    m_sprites[NORMAL].Rotate(angle);
    m_sprites[HOVER].Rotate(angle);
    m_sprites[PRESSED].Rotate(angle);
}

void sf::ui::Button::Scale(const sf::Vector2f& factor)
{
    m_sprites[DISABLED].Scale(factor);
    m_sprites[NORMAL].Scale(factor);
    m_sprites[HOVER].Scale(factor);
    m_sprites[PRESSED].Scale(factor);
}

bool sf::ui::Button::OnEvent(const sf::Event& event)
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
                    Element::m_hoverSignal();
                    return false;
                }
            }
            else if(m_state != NORMAL)
            {
                SetState(NORMAL);
                m_leaveSignal();
                return false;
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
                SetState(CLICKED);
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

void sf::ui::Button::Draw(sf::RenderWindow& window)
{
    window.Draw(m_sprites[m_state]);
}

void sf::ui::Button::ApplySkin()
{
    State drawableStates[4] = {DISABLED, NORMAL, HOVER, PRESSED};

    for(unsigned int i = 0; i < 4; ++i)
    {
        // State's Skin
        StateSkin& stateSkin = m_skin[drawableStates[i]];
        // Text
        sf::Text text(m_string, stateSkin.textFont, stateSkin.textCharacterSize);
        text.SetColor(stateSkin.textColor);
        text.SetPosition(stateSkin.textMargin.Left+stateSkin.backgroundBorderThickness, stateSkin.textMargin.Top+stateSkin.backgroundBorderThickness);
        // Background
        sf::FloatRect backgroundRect(0.f, 0.f, text.GetRect().Width+stateSkin.textMargin.Left+stateSkin.textMargin.Width, text.GetRect().Height+stateSkin.textMargin.Top+stateSkin.textMargin.Height);
        sf::Shape background(sf::RoundedRectangle(backgroundRect, stateSkin.backgroundColor, stateSkin.backgroundRoundness, stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderColor));
        background.SetPosition(stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderThickness);
        sf::ApplyGradient(background, stateSkin.backgroundGradientOrientation, stateSkin.backgroundColor, stateSkin.backgroundGradientColor);
        sf::ApplyGradient(background, stateSkin.backgroundBorderGradientOrientation, stateSkin.backgroundBorderColor, stateSkin.backgroundBorderGradientColor, true);
        // Create RenderImage
        sf::RenderImage& renderImage = *(m_renderImages[drawableStates[i]]);
        renderImage.Create(text.GetRect().Width+stateSkin.textMargin.Left+stateSkin.textMargin.Width+2*stateSkin.backgroundBorderThickness,
                           text.GetRect().Height+stateSkin.textMargin.Top+stateSkin.textMargin.Height+2*stateSkin.backgroundBorderThickness);
        // Draw background on renderImage
        renderImage.Draw(background);
        // Draw text on renderImage
        if(stateSkin.textShadowOffset != sf::Vector2f(0.f, 0.f))
        {
            text.Move(stateSkin.textShadowOffset);
            text.SetColor(stateSkin.textShadowColor);
            renderImage.Draw(text);
            text.Move(-stateSkin.textShadowOffset);
            text.SetColor(stateSkin.textColor);
        }
        renderImage.Draw(text);
        renderImage.Display();
        // bind sprite to renderImage
        m_sprites[drawableStates[i]].SetImage(renderImage.GetImage(), true);
    }
}

void sf::ui::Button::ApplySkin(const sf::Vector2f& buttonSize)
{
    State drawableStates[4] = {DISABLED, NORMAL, HOVER, PRESSED};

    for(unsigned int i = 0; i < 4; ++i)
    {
        // State's Skin
        StateSkin& stateSkin = m_skin[drawableStates[i]];
        // Text
        sf::Text text(m_string, stateSkin.textFont, stateSkin.textCharacterSize);
        text.SetColor(stateSkin.textColor);
        text.SetPosition(stateSkin.textMargin.Left+stateSkin.backgroundBorderThickness, stateSkin.textMargin.Top+stateSkin.backgroundBorderThickness);
        // Background
        sf::FloatRect backgroundRect(0.f, 0.f, buttonSize.x, buttonSize.y);
        sf::Shape background(sf::RoundedRectangle(backgroundRect, stateSkin.backgroundColor, stateSkin.backgroundRoundness, stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderColor));
        background.SetPosition(stateSkin.backgroundBorderThickness, stateSkin.backgroundBorderThickness);
        sf::ApplyGradient(background, stateSkin.backgroundGradientOrientation, stateSkin.backgroundColor, stateSkin.backgroundGradientColor);
        sf::ApplyGradient(background, stateSkin.backgroundBorderGradientOrientation, stateSkin.backgroundBorderColor, stateSkin.backgroundBorderGradientColor, true);
        // Create RenderImage
        sf::RenderImage& renderImage = *(m_renderImages[drawableStates[i]]);
        renderImage.Create(buttonSize.x, buttonSize.y);
        // Draw background on renderImage
        renderImage.Draw(background);
        // Draw text on renderImage
        if(stateSkin.textShadowOffset != sf::Vector2f(0.f, 0.f))
        {
            text.Move(stateSkin.textShadowOffset);
            text.SetColor(stateSkin.textShadowColor);
            renderImage.Draw(text);
            text.Move(-stateSkin.textShadowOffset);
            text.SetColor(stateSkin.textColor);
        }
        renderImage.Draw(text);
        renderImage.Display();
        // bind sprite to renderImage
        m_sprites[drawableStates[i]].SetImage(renderImage.GetImage(), true);
    }
}

