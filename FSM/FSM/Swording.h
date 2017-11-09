#ifndef SWORDING
#define SWORDING
#include "State.h"
#include "Animation.h"
#include "Idle.h"
class Swording : public State
{
public:
	Swording();
	~Swording();
	void idle(Animation* a);
};

#endif //SWORDING
