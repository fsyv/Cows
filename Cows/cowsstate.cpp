#include "cowsstate.h"

CowsState::CowsState(State state)
{
    m_eState = state;
}

CowsState::CowsState(const CowsState &cow)
{
    m_eState = cow.getState();
}

auto CowsState::getState()->decltype(m_eState) const
{
    return m_eState;
}
