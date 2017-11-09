#ifndef ANIMATION
#define ANIMATION
#include <iostream>


class Animation
{
	//creates a pointer of class state
	class State* current;
public:
	Animation();
	void setCurrent(State* s)
	{
		current = s;
	}
	void idle();
	void jumping();
	void climbing();
	void swording();
	void shielding();

private:

};

#endif // !AMINATION