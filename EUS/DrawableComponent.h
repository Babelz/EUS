#pragma once
#include "Component.h"

// Base class for components that can draw.
class DrawableComponent : public Component
{
private:
	int drawOrder;

	bool visible;
protected:
	virtual void onDraw();

	virtual void onVisibleChanged(bool newVisibility, bool oldVisibility);

	virtual void drawOrderChanged(int newOrder, int oldOrder);
public:
	int getDrawOrder() const;

	DrawableComponent(Entity* const owner, int updateOrder = 0, int drawOrder = 0);

	void show();
	void hide();
	bool isVisible() const;

	void draw();

	~DrawableComponent();
};

