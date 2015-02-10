#include "Vector4.hpp"

class Color {
private:
	pmath::Vec4f data;
public:
	Color(float r, float g, float b, float a);
	
	float r() const;
	float g() const;
	float b() const;
	float a() const;

	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color white;
};