#ifndef IDLE
#define IDLE


#include <iostream>
#include "State.h"
#include "Animation.h"

class Idle: public State
{
public:
	Idle();
	~Idle();
	//Below will accept a referance to something of type animation,
	//And set current to that state
	void jumping(Animation* a);
	void climbing(Animation* a);
	void swording(Animation* a);
	void shielding(Animation* a);
private:

};

#endif // !IDLE