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

sf::ui::Button::Skin& sf::ui::DefaultSkin::GetButtonSkin()
{
    return m_buttonSkin;
}

sf::ui::ProgressBar::Skin& sf::ui::DefaultSkin::GetProgressBarSkin()
{
    return m_progressBarSkin;
}

sf::ui::Slider::Skin& sf::ui::DefaultSkin::GetSliderSkin()
{
    return m_sliderSkin;
}

sf::ui::Switch::Skin& sf::ui::DefaultSkin::GetSwitchSkin()
{
    return m_switchSkin;
}

sf::ui::TextInput::Skin& sf::ui::DefaultSkin::GetTextInputSkin()
{
    return m_textInputSkin;
}
