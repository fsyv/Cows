#include "cowsstate.h"

CowsState::CowsState(State state)
{
    m_eState = state;
}

CowsState::CowsState(const CowsState &cow)
{
	m_eState = cow.getState();
}

CowsState::CowsState(const CowsState *cow)
{
	m_eState = cow->getState();
}

CowsState::~CowsState()
{

}

CowsState::State CowsState::getState() const
{
    return m_eState;
}
