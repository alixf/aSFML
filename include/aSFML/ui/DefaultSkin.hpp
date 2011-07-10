#ifndef ASFML_UI_DEFAULTSKIN_HPP
#define ASFML_UI_DEFAULTSKIN_HPP

#include "../ui.hpp"

namespace sf
{
    namespace ui
    {
        class DefaultSkin
        {
        public :
            static DefaultSkin& GetInstance();
            ~DefaultSkin();

            const Button::Skin&       GetButtonSkin() const;
            const ProgressBar::Skin&  GetProgressBarSkin() const;
            const Slider::Skin&       GetSliderSkin() const;
            const Switch::Skin&       GetSwitchSkin() const;
            const TextInput::Skin&    GetTextInputSkin() const;

            void SetButtonSkin(const Button::Skin& skin);
            void SetProgressBarSkin(const ProgressBar::Skin& skin);
            void SetSliderSkin(const Slider::Skin& skin);
            void SetSwitchSkin(const Switch::Skin& skin);
            void SetTextInputSkin(const TextInput::Skin& skin);

        private :
            DefaultSkin();
            Button::Skin         m_buttonSkin;
            ProgressBar::Skin    m_progressBarSkin;
            Slider::Skin         m_sliderSkin;
            Switch::Skin         m_switchSkin;
            TextInput::Skin      m_textInputSkin;
        };
    }
}

#endif // ASFML_UI_DEFAULTSKIN_HPP
