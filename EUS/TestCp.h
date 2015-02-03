#pragma once
#include "Entity.h"

class TestCp : public Component {
public:
	TestCp(Entity* const owner, int updateOrder = 0);
		
	~TestCp();
};

