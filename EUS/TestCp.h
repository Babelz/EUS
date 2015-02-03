#pragma once
#include "Entity.h"
#include "Component.h"

class TestCp : public Component
{
public:
	TestCp(Entity* const owner, int updateOrder = 0);
		
	~TestCp();
};

