#ifndef ASFML_ANIMATEDSPRITE_HPP
#define ASFML_ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>

namespace sf
{
    class AnimatedSprite
    {
    public :
        struct Frame
        {
            sf::Sprite sprite;
            unsigned int time;
        };

        struct Animation
        {
            bool loop;
            bool autoplay;
            unsigned int totalTime;
            std::vector<Frame> frames;
        };

        AnimatedSprite();
		~AnimatedSprite();

        sf::Vector2f GetPosition() const;
        unsigned int GetCurrentAnimation() const;

        void SetPosition(const sf::Vector2f& position);
        void Move(const sf::Vector2f& position);
        void SetCurrentAnimation(unsigned int animation);

        bool LoadFromFile(const std::string& filePath);
        void Draw(sf::RenderWindow& window);

    private :
        sf::Clock m_clock;
        unsigned int m_currentAnimation;
        std::vector<Animation> m_animations;
    };
}


#endif // ASFML_ANIMATEDSPRITE_HPP
