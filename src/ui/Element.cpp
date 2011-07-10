#include <aSFML/ui/Element.hpp>

sf::ui::Element::Element() :
    m_state(sf::ui::Element::NORMAL)
{
}

sf::ui::Element::~Element()
{
}

sf::ui::Element::State sf::ui::Element::GetState() const
{
    return m_state;
}

sf::Vector2f sf::ui::Element::GetPosition() const
{
    return sf::Vector2f();
}

float sf::ui::Element::GetRotation() const
{
    return 0.f;
}

sf::Vector2f sf::ui::Element::GetScale() const
{
    return sf::Vector2f();
}

sf::Color sf::ui::Element::GetColor() const
{
    return sf::Color::White;
}

void sf::ui::Element::SetState(sf::ui::Element::State state)
{
    m_state = state;
}

void sf::ui::Element::SetPosition(const sf::Vector2f& position)
{
}

void sf::ui::Element::SetRotation(float rotation)
{
}

void sf::ui::Element::SetScale(const sf::Vector2f& scale)
{
}

void sf::ui::Element::SetColor(const sf::Color& color)
{
}

void sf::ui::Element::Move(const sf::Vector2f& offset)
{
}

void sf::ui::Element::Rotate(float angle)
{
}

void sf::ui::Element::Scale(const sf::Vector2f& factor)
{
}

boost::signals::connection& sf::ui::Element::OnHover(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_hoverSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnLeave(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_leaveSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnPress(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_pressSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnClick(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_clickSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnRelease(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_releaseSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnEnable(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_enableSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnDisable(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_disableSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnActivate(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_activateSignal.connect(slot));
    return m_connections.back();
}

boost::signals::connection& sf::ui::Element::OnDesactivate(boost::signal<void ()>::slot_type slot)
{
    m_connections.push_back(m_desactivateSignal.connect(slot));
    return m_connections.back();
}

void sf::ui::Element::DisconnectSlot(boost::signals::connection& connection)
{
    connection.disconnect();
    for(std::vector<boost::signals::connection>::iterator it = m_connections.begin(); it != m_connections.end();)
    {
        if(*it == connection)
            it = m_connections.erase(it);
    }
}

void sf::ui::Element::DisconnectSlots()
{
    for(std::vector<boost::signals::connection>::iterator it = m_connections.begin(); it != m_connections.end(); ++it)
        it->disconnect();
    m_connections.clear();
}
