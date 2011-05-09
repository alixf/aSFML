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

            Button::Skin&       GetButtonSkin();
            ProgressBar::Skin&  GetProgressBarSkin();
            Slider::Skin&       GetSliderSkin();
            Switch::Skin&       GetSwitchSkin();
            TextInput::Skin&    GetTextInputSkin();

        private :
            DefaultSkin();
            Button::Skin        m_buttonSkin;
            ProgressBar::Skin   m_progressBarSkin;
            Slider::Skin        m_sliderSkin;
            Switch::Skin        m_switchSkin;
            TextInput::Skin     m_textInputSkin;
        };
    }
}

#endif // ASFML_UI_DEFAULTSKIN_HPP
