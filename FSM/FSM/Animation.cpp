#include "Animation.h"
#include "Idle.h"
Animation::Animation()
{
	current = new Idle();
}
//Below sets current to whatver the actual state is at that given moment

void Animation::idle()
{
	current->idle(this);
}

void Animation::jumping()
{
	current->jumping(this);
}

void Animation::climbing()
{
	current->climbing(this);
}

void Animation::swording()
{
	current->swording(this);
}

void Animation::shielding()
{
	current->shielding(this);
}

