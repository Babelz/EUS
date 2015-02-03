#include "TagContainer.h"

TagContainer::TagContainer() {
}

#pragma region Private members.
int TagContainer::indexOf(std::string tag) const {
	for (size_t i = 0; i < tags.size(); i++) {
		if (tags[i] == tag) {
			return i;
		}
	}

	throw std::logic_error("Container does not contain given tag.");
}
#pragma endregion

#pragma region Public members
bool TagContainer::isTagged(std::string tag) const {
	bool tagged = false;

	for (size_t i = 0; i < tags.size(); i++) {
		tagged = tags[i] == tag;

		if (tagged) {
			break;
		}
	}

	return tagged;
}
bool TagContainer::unTag(std::string tag) {
	bool remove = isTagged(tag);

	if (remove) {
		tags.erase(tags.begin() + indexOf(tag));
	}

	return remove;
}
bool TagContainer::tag(std::string tag){
	bool add = !isTagged(tag);
	
	if (add) {
		tags.push_back(tag);
	}

	return add;
}
#pragma endregion

TagContainer::~TagContainer() {
}
