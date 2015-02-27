#pragma once
#include "Entity.h"

class PlayerController : public Component {
protected:
	void onDestroy();

	void onInitialize();
public:
	PlayerController(Game& game, Entity& owner, const int updateOrder = 0);
	
	~PlayerController();
};

