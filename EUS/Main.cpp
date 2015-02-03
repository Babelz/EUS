#include "Entity.h"
#include "TestCp.h"

void tagTests();
void componentTests();

int main() {
	tagTests();
	componentTests();

	Entity e;
	TestCp c(e);

	return 0;
}

void tagTests() {
	Entity e;

	assert(e.tag("jeesus"));
	assert(!e.tag("jeesus"));
	
	assert(e.isTagged("jeesus"));
	assert(e.unTag("jeesus"));
	assert(!e.isTagged("jeesus"));
}

void componentTests() {
	Entity e;
	e.enable();

	TestCp* c = new TestCp(e);

	assert(e.addComponent(c));
	assert(!e.addComponent(c));
	
	assert(e.containsComponent(c));
	assert(e.removeComponent(c));

	assert(!e.containsComponent(c));
	assert(!e.removeComponent(c));

	assert(e.addComponent(c));

	TestCp* gg = e.getComponent<TestCp>();
	assert(gg != nullptr);
	assert(gg == c);

	gg->destroy();

	e.update();
	e.update();
}