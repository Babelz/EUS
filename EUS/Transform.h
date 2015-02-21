#pragma once
#include "Vector.hpp"

// TODO: missing basic transform class.
class Transform {
private:
	pmath::Vec3f position;
	pmath::Vec3f scale;
	pmath::Vec3f rotation;
	pmath::Vec3f sizeInPixels;
public:
	Transform();

	~Transform();
};

