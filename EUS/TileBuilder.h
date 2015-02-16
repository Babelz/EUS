#pragma once
#include "Entity.h"
#include "TileInfo.h"
#include <string>
#include <list>

struct TileBuilderData {
	const std::string tileName;
	const std::function<Entity*()> builder;
	
	TileBuilderData(const std::string& tileName, std::function<Entity*()> builder) : tileName(tileName),
																		             builder(builder) {
	}
};

class TileBuilder {
private:
	std::list<TileBuilderData> tileDatas;
protected:
	Entity* createEntity() const;

	Entity* createFactory() const;
	Entity* createSea() const;
	Entity* createCity() const;

	void pushBuilder(const std::string& tileName, std::function<Entity*()> builder);

	virtual void createBuilders() = 0;
public:
	TileBuilder();

	Entity* buildTile(const std::string& name) const;

	void initialize();

	~TileBuilder();
};

