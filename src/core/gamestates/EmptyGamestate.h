#ifndef EMPTYGAMESTATE_H
#define EMPTYGAMESTATE_H

#include "Gamestate.h"

class EmptyGamestate : public Gamestate
{
public:
	EmptyGamestate();
	EmptyGamestate(const EmptyGamestate& other);
	~EmptyGamestate();

	virtual void HandleEvents();
	virtual void UpdateLogic(const float dt);
	virtual void Draw(const float interp);

	virtual void FinishState();

private:

};

#endif
