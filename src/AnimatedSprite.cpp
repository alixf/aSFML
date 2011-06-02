#include <aSFML/AnimatedSprite.hpp>
#include <ticpp/ticpp.h>
#include <aSFML/ImageManager.hpp>

sf::AnimatedSprite::AnimatedSprite() :
m_currentAnimation(0)
{
}

sf::AnimatedSprite::~AnimatedSprite()
{
}

sf::Vector2f sf::AnimatedSprite::GetPosition() const
{
    return m_animations.at(0).frames.at(0).sprite.GetPosition();
}

unsigned int sf::AnimatedSprite::GetCurrentAnimation() const
{
    return m_currentAnimation;
}

void sf::AnimatedSprite::SetPosition(const sf::Vector2f& position)
{
    for(std::vector<Animation>::iterator animation = m_animations.begin(); animation != m_animations.end(); ++animation)
        for(std::vector<Frame>::iterator frame = animation->frames.begin(); frame != animation->frames.end(); ++frame)
            frame->sprite.SetPosition(position);
}

void sf::AnimatedSprite::Move(const sf::Vector2f& position)
{
    for(std::vector<Animation>::iterator animation = m_animations.begin(); animation != m_animations.end(); ++animation)
        for(std::vector<Frame>::iterator frame = animation->frames.begin(); frame != animation->frames.end(); ++frame)
            frame->sprite.Move(position);
}

void sf::AnimatedSprite::SetCurrentAnimation(unsigned int animation)
{
    m_currentAnimation = animation;
    m_clock.Reset();
}

bool sf::AnimatedSprite::LoadFromFile(const std::string& filePath)
{
    m_animations.clear();

    sf::Image* image = NULL;

    // Load Document
    ticpp::Document document(filePath);
    document.LoadFile();

    // AnimatedSprite attributes
    for (ticpp::Iterator<ticpp::Attribute> attribute = attribute.begin(document.FirstChildElement()); attribute != attribute.end(); attribute++)
    {
        std::string name = attribute->Name();
        if(name == "image")
            image = &sf::ImageManager::GetInstance().GetImage(attribute->Value());
    }

    // Count animations and reserve space
    unsigned int animationCount = 0;
    for(ticpp::Iterator<ticpp::Element> animation = animation.begin(document.FirstChildElement()); animation != animation.end(); animation++)
        animationCount++;
    m_animations.reserve(animationCount);

    // Animations
    for(ticpp::Iterator<ticpp::Element> animation = animation.begin(document.FirstChildElement()); animation != animation.end(); animation++)
    {
        m_animations.push_back(Animation());

        bool loop = false;
        bool autoplay = false;

        // Animation attributes
        for(ticpp::Iterator<ticpp::Attribute> attribute = attribute.begin(&*animation); attribute != attribute.end(); attribute++)
        {
            std::string name = attribute->Name();
            if(name == "loop")
                attribute->GetValue(&loop);
            if(name == "autoplay")
                attribute->GetValue(&autoplay);
        }

        // Count frames and reserve space
        unsigned int frameCount = 0;
        for(ticpp::Iterator<ticpp::Element> frame = frame.begin(&*animation); frame != frame.end(); frame++)
            frameCount++;
        m_animations.back().frames.reserve(frameCount);

        // Frames
        for(ticpp::Iterator<ticpp::Element> frame = frame.begin(&*animation); frame != frame.end(); frame++)
        {
            // Frame attributes
            unsigned int x = 0;
            unsigned int y = 0;
            unsigned int width = 0;
            unsigned int height = 0;
            unsigned int originX = 0;
            unsigned int originY = 0;
            unsigned int time = 1.f;

            for(ticpp::Iterator<ticpp::Attribute> attribute = attribute.begin(&*frame); attribute != attribute.end(); attribute++)
            {
                std::string name = attribute->Name();
                if(name == "x")
                    attribute->GetValue(&x);
                if(name == "y")
                    attribute->GetValue(&y);
                if(name == "width")
                    attribute->GetValue(&width);
                if(name == "height")
                    attribute->GetValue(&height);
                if(name == "originX")
                    attribute->GetValue(&originX);
                if(name == "originY")
                    attribute->GetValue(&originY);
                if(name == "time")
                    attribute->GetValue(&time);
            }

            m_animations.back().frames.push_back(Frame());
            m_animations.back().frames.back().sprite.SetImage(*image);
            m_animations.back().frames.back().sprite.SetSubRect(sf::IntRect(x,y,width,height));
            m_animations.back().frames.back().sprite.SetOrigin(originX, originY);
            m_animations.back().frames.back().time = time;
            m_animations.back().totalTime += time;
        }
    }

    m_currentAnimation = 0;
    m_clock.Reset();

	return true;
}


void sf::AnimatedSprite::Draw(sf::RenderWindow& window)
{
    float time = m_clock.GetElapsedTime();
    while(time >= m_animations[m_currentAnimation].totalTime)
        time -= m_animations[m_currentAnimation].totalTime;
    unsigned int frame = 0;
    while(time > m_animations[m_currentAnimation].frames[frame].time)
    {
        if(frame >= m_animations[m_currentAnimation].frames.size())
            frame -= m_animations[m_currentAnimation].frames.size();
        time -= m_animations[m_currentAnimation].frames[frame++].time;
    }
    window.Draw(m_animations[m_currentAnimation].frames[frame].sprite);
 }
