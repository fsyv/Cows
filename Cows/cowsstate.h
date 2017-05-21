#ifndef COWSSTATE_H
#define COWSSTATE_H

/**
 * @brief 牛得状态
 */

class CowsState
{
public:
    enum State{
        NoState = 0,    //没有状态
        Running,        //奔跑状态
        Walking         //行走状态
    };

public:
    CowsState(State state = NoState);
    CowsState(const CowsState &cow);
	CowsState(const CowsState *cow);
    ~CowsState();

private:
    State m_eState;

	State getState() const;
};

#endif // COWSSTATE_H
