#pragma once
#include <iostream>
#include "Animation.h"
class State
{
	
public:
	
	virtual void idle(Animation* a)
	{
		std::cout << "State::Idling" << std::endl;
	}

	virtual void jumping(Animation* a)
	{
		std::cout << "State::Jumping" << std::endl;
	}

	virtual void climbing(Animation* a)
	{
		std::cout << "State::Climbing" << std::endl;
	}
	virtual void swording(Animation* a)
	{
		std::cout << "State::Swording" << std::endl;
	}

	virtual void shielding(Animation* a)
	{
		std::cout << "State::Shielding" << std::endl;
	}
};