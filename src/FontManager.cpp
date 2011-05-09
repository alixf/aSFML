#include <aSFML/FontManager.hpp>

sf::FontManager& sf::FontManager::GetInstance()
{
    static FontManager instance;
    return instance;
}

sf::FontManager::~FontManager()
{
    Clear();
}

sf::Font& sf::FontManager::GetFont(const std::string& path)
{
    FontMap::iterator it = m_fonts.find(path);
    if(it == m_fonts.end())
    {
        sf::Font* font = new sf::Font();
        font->LoadFromFile(path);
        m_fonts.insert(std::pair<std::string, sf::Font*>(path, font));
        return *font;
    }
    else
        return *(it->second);
}

void sf::FontManager::DeleteFont(const sf::Font& font)
{
    for(FontMap::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    {
        if(it->second == &font)
        {
            delete &font;
            m_fonts.erase(it);
        }
    }
}

void sf::FontManager::DeleteFont(const std::string& path)
{
    FontMap::iterator it = m_fonts.find(path);

    if(it != m_fonts.end())
    {
        delete it->second;
        m_fonts.erase(it);
    }
}

void sf::FontManager::Clear()
{
    for(FontMap::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
        delete it->second;
    m_fonts.clear();
}

sf::FontManager::FontManager()
{
}
