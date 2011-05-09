#include <aSFML/ImageManager.hpp>

sf::ImageManager& sf::ImageManager::GetInstance()
{
    static ImageManager instance;
    return instance;
}

sf::ImageManager::~ImageManager()
{
    Clear();
}

sf::Image& sf::ImageManager::GetImage(const std::string& path)
{
    ImageMap::iterator it = m_images.find(path);
    if(it == m_images.end())
    {
        sf::Image* image = new sf::Image();
        image->LoadFromFile(path);
        m_images.insert(std::pair<std::string, sf::Image*>(path, image));
        return *image;
    }
    else
        return *(it->second);
}

void sf::ImageManager::DeleteImage(const sf::Image& image)
{
    for(ImageMap::iterator it = m_images.begin(); it != m_images.end(); ++it)
    {
        if(it->second == &image)
        {
            delete &image;
            m_images.erase(it);
        }
    }
}

void sf::ImageManager::DeleteImage(const std::string& path)
{
    ImageMap::iterator it = m_images.find(path);

    if(it != m_images.end())
    {
        delete it->second;
        m_images.erase(it);
    }
}

void sf::ImageManager::Clear()
{
    for(ImageMap::iterator it = m_images.begin(); it != m_images.end(); ++it)
        delete it->second;
    m_images.clear();
}

sf::ImageManager::ImageManager()
{
}
