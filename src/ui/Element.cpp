#include <aSFML/ui/Element.hpp>

sf::ui::Element::Element() :
    m_state(sf::ui::Element::NORMAL)
{
}

sf::ui::Element::~Element()
{
}

void sf::ui::Element::OnHover(boost::signal<void ()>::slot_type slot)
{
    m_hoverSignal.connect(slot);
}

void sf::ui::Element::OnLeave(boost::signal<void ()>::slot_type slot)
{
    m_leaveSignal.connect(slot);
}

void sf::ui::Element::OnPress(boost::signal<void ()>::slot_type slot)
{
    m_pressSignal.connect(slot);
}

void sf::ui::Element::OnClick(boost::signal<void ()>::slot_type slot)
{
    m_clickSignal.connect(slot);
}

void sf::ui::Element::OnRelease(boost::signal<void ()>::slot_type slot)
{
    m_releaseSignal.connect(slot);
}

void sf::ui::Element::OnEnable(boost::signal<void ()>::slot_type slot)
{
    m_enableSignal.connect(slot);
}

void sf::ui::Element::OnDisable(boost::signal<void ()>::slot_type slot)
{
    m_disableSignal.connect(slot);
}

void sf::ui::Element::OnActivate(boost::signal<void ()>::slot_type slot)
{
    m_activateSignal.connect(slot);
}

void sf::ui::Element::OnDesactivate(boost::signal<void ()>::slot_type slot)
{
    m_desactivateSignal.connect(slot);
}
