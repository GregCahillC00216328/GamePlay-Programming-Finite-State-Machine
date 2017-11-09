#ifndef SHIELDING
#define SHIELDING
#include "State.h"
#include "Animation.h"
#include "Idle.h"
class Shielding : public State
{
public:
	Shielding();
	~Shielding();
	void idle(Animation* a);
};

#endif //SWORDING