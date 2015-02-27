#include "MapBuilder.h"

MapBuilder::MapBuilder(Game& game) : EntityBuilder("", game) {
}

#pragma region Public members
Entity* MapBuilder::buildMap(const std::string& name, const std::string& sheetName, size_t tileSize, std::vector<Entity*>& outTiles) const {
	std::string path = "Content\\" + name + ".txt";

	Texture* texture = game().content().load<Texture>(sheetName);

	TileBuilder builder(game());
	
	SheetMapping mappings;
	mappings.load(path);

	NamedTileSheet sheet(texture, 32);
	sheet.load(path);

	MapLoader loader;
	loader.load(path);

	Entity* map = new Entity();
	TileEngine* engine = new TileEngine(game(), *map, 
		loader.getMapWidth(), 
		loader.getMapHeight(), 
		tileSize);
	
	map->addComponent(engine);

	for (size_t i = 0; i < loader.getMapHeight(); i++) {
		for (size_t j = 0; j < loader.getMapWidth(); j++) {
			char ch = loader.charAt(i, j);

			std::string name = mappings.getTileName(ch);
			pmath::Rectf source = sheet.getSource(name);

			Entity* tile = builder.buildTile(name);
			tile->getTransform().setX(tileSize * j);
			tile->getTransform().setY(tileSize * i);

			SpriteRenderer* renderer = new SpriteRenderer(game(), *tile);
			renderer->setSprite(new Sprite());
			renderer->getSprite().swapTexture(texture);
			renderer->getSprite().setSource(source);
			renderer->getSprite().useSource();
			// TODO: debug scale.
			renderer->getSprite().setScale(2.0f);
			renderer->getSprite().setX(tile->getTransform().getPosition().x);
			renderer->getSprite().setY(tile->getTransform().getPosition().y);

			tile->addComponent(renderer);
			renderer->enable();

			map->addChild(tile);

			outTiles.push_back(tile);
		}
	}

	MapGrid* grid = new MapGrid(game(), *map, *engine);
	grid->enable();

	map->addComponent(grid);

	return map;
}
#pragma endregion

MapBuilder::~MapBuilder() {
}
