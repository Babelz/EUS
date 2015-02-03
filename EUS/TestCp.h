#pragma once
#include "Entity.h"

class TestCp : public Component {
public:
	TestCp(Entity& owner, int updateOrder = 0);
		
	~TestCp();
};

