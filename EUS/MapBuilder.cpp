#include "MapBuilder.h"

MapBuilder::MapBuilder(Game& game) : EntityBuilder("", game) {
}

#pragma region Public members
Entity* MapBuilder::buildMap(const std::string& name, const std::string& sheetName, size_t tileSize) const {
	std::string path = "Content\\" + name + ".txt";

	Texture* texture = game().content().load<Texture>(sheetName);

	TileBuilder builder(game());
	
	SheetMapping mappings;
	mappings.load(path);

	NamedTileSheet sheet(texture, tileSize);
	sheet.load(path);

	MapLoader loader;
	loader.load(path);

	Entity* map = new Entity();

	for (size_t i = 0; i < loader.getMapHeight(); i++) {
		for (size_t j = 0; j < loader.getMapWidth(); j++) {
			char ch = loader.charAt(i, j);

			std::string name = mappings.getTileName(ch);
			pmath::Rectf source = sheet.getSource(name);

			Entity* tile = new Entity();
			tile->setX(source.size.x * j);
			tile->setY(source.size.y * i);
			tile->setSize(source.size);

			SpriteRenderer* renderer = new SpriteRenderer(game(), *tile);
			renderer->setSprite(new Sprite());
			renderer->getSprite().swapTexture(texture);
			renderer->getSprite().setSource(source);
			renderer->getSprite().useSource();
			renderer->getSprite().setX(tile->getX());
			renderer->getSprite().setY(tile->getY());

			tile->addComponent(renderer);
			renderer->enable();

			map->addChild(tile);
		}
	}

	return map;
}
#pragma endregion

MapBuilder::~MapBuilder() {
}
