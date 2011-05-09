#ifndef ASFML_ANIMATEDSPRITE_HPP
#define ASFML_ANIMATEDSPRITE_HPP
/*
#include <SFML/Graphics.hpp>
#include <ticpp.h>

namespace sf
{
    class AnimatedSprite
    {
    public :
        struct Frame
        {
            sf::Sprite sprite;
            float time;
        };

        struct Animation
        {
            bool loop;
            bool autoplay;
            std::vector<sf::Sprite> frames;
        };

        AnimatedSprite();

		~AnimatedSprite();
		
        bool LoadFromFile(const std::string& filePath);

        void Draw(sf::RenderWindow& window);

    private :
        sf::Clock m_clock;
        std::vector<Animation> m_animations;
        sf::Image m_image;
    };
}
*/

#endif // ASFML_ANIMATEDSPRITE_HPP