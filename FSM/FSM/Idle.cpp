#include "Idle.h"

Idle::Idle()
{
}

Idle::~Idle()
{
}
//Below will return state to idle after completion of state switching
//Then will delete itself, freeing up memeory
void Idle::jumping(Animation * a)
{
	std::cout << "Jumping" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::climbing(Animation * a)
{
	std::cout << "Climbing" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::swording(Animation * a)
{
	std::cout << "Swording" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::shielding(Animation * a)
{
	std::cout << "Shielding" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

