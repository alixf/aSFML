#include <aSFML/ui/DefaultSkin.hpp>

sf::ui::DefaultSkin& sf::ui::DefaultSkin::GetInstance()
{
    static DefaultSkin instance;
    return instance;
}

sf::ui::DefaultSkin::DefaultSkin()
{
}

sf::ui::DefaultSkin::~DefaultSkin()
{
}

const sf::ui::Button::Skin& sf::ui::DefaultSkin::GetButtonSkin() const
{
    return m_buttonSkin;
}

const sf::ui::ProgressBar::Skin& sf::ui::DefaultSkin::GetProgressBarSkin() const
{
    return m_progressBarSkin;
}

const sf::ui::Slider::Skin& sf::ui::DefaultSkin::GetSliderSkin() const
{
    return m_sliderSkin;
}

const sf::ui::Switch::Skin& sf::ui::DefaultSkin::GetSwitchSkin() const
{
    return m_switchSkin;
}

const sf::ui::TextInput::Skin& sf::ui::DefaultSkin::GetTextInputSkin() const
{
    return m_textInputSkin;
}

void sf::ui::DefaultSkin::SetButtonSkin(const Button::Skin& skin)
{
    m_buttonSkin = skin;
}

void sf::ui::DefaultSkin::SetProgressBarSkin(const ProgressBar::Skin& skin)
{
    m_progressBarSkin = skin;
}

void sf::ui::DefaultSkin::SetSliderSkin(const Slider::Skin& skin)
{
    m_sliderSkin = skin;
}

void sf::ui::DefaultSkin::SetSwitchSkin(const Switch::Skin& skin)
{
    m_switchSkin = skin;
}

void sf::ui::DefaultSkin::SetTextInputSkin(const TextInput::Skin& skin)
{
    m_textInputSkin = skin;
}
