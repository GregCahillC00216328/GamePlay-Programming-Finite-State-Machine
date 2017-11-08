#ifndef JUMPING
#define JUMPING
#include "State.h"
#include "Animation.h"
#include "Idle.h"
class Jumping: public State
{
public:
	Jumping();
	~Jumping();
	void idle(Animation* a);
};

#endif //JUMPING
