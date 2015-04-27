#pragma once

// 2D view.
class View {
private:
	float x;
	float y;

	float rotX;
	float rotY;
public:
	View();

	float getX() const;
	float getY() const;

	void setX(float x);
	void setY(float y);

	float getRotX() const;
	float getRotY() const;

	void setRotX(float x);
	void setRotY(float y);

	~View();
};

