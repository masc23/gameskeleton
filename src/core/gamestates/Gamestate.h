#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>

class Gamestate
{
public:
    Gamestate()
		: Finished(false), NextGamestatePtr(nullptr) {};

    virtual ~Gamestate() {};

	virtual void HandleEvents()                = 0;
	virtual void UpdateLogic(const float dt)   = 0;
	virtual void Draw(const float interp)      = 0;

	virtual void FinishState()                 = 0;
	virtual bool IsShutdown() { return false;    };
    virtual bool IsFinished() { return Finished; };

    virtual std::unique_ptr<Gamestate> GetNextGamestate() { return std::move(NextGamestatePtr); };

protected:
    bool Finished;
    std::unique_ptr<Gamestate> NextGamestatePtr;
};

#endif
