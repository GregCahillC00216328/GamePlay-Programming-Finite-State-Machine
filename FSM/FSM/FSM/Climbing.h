#ifndef CLIMBING
#define CLIMBING
#include "State.h"
#include "Animation.h"
#include "Idle.h"
class Climbing : public State
{
public:
	Climbing();
	~Climbing();
	void idle(Animation* a);
};

#endif //CLIMBING