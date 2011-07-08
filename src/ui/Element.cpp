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

void sf::ui::Element::SetState(sf::ui::Element::State state)
{
    m_state = state;
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
