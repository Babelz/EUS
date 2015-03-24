#ifndef TRIGGERS_H
#define TRIGGERS_H

#include "SDL\SDL.h"
#include "SDL\SDL_keyboard.h"
#include "Enums.h"

class ITrigger {
public:
	ITrigger();
	~ITrigger();
	virtual int triggerHash() = 0;
};

class KeyTrigger : public ITrigger {
private:
	SDL_Keycode key;
public: 
	KeyTrigger(SDL_Keycode key);
	~KeyTrigger();
	int triggerHash();
};
#endif