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
	map->tag("map");

	TileEngine* engine = new TileEngine(game(), *map, 
		loader.getMapWidth(), 
		loader.getMapHeight(), 
		tileSize);

	map->addComponent(engine);

	for (size_t i = 0; i < loader.getMapHeight(); i++) {
		for (size_t j = 0; j < loader.getMapWidth(); j++) {
			const char ch = loader.charAt(i, j);

			const std::string name = mappings.getTileName(ch);
			const pmath::Rectf source = sheet.getSource(name);

			Entity* tile = builder.buildTile(name);
			tile->getTransform().setX(static_cast<float>(tileSize * j));
			tile->getTransform().setY(static_cast<float>(tileSize * i));

			SpriteRenderer* renderer = new SpriteRenderer(game(), *tile);
			renderer->setSprite(new Sprite());
			renderer->getSprite().setScaleX(tileSize / source.size.x);
			renderer->getSprite().setScaleY(tileSize / source.size.y);
			renderer->getSprite().swapTexture(texture);
			renderer->getSprite().setSource(source);
			renderer->getSprite().useSource();

			tile->addComponent(renderer);
			renderer->enable();

			map->addChild(tile);

			outTiles.push_back(tile);
		}
	}

	MapGrid* grid = new MapGrid(game(), *map, engine->mapWidthInTiles(), engine->mapHeightInTiles(), engine->tileSize());
	grid->enable();

	AStarPathfinder* pathfinder = new AStarPathfinder(game(), *map, *grid);
	grid->enable();

	map->addComponent(grid);
	map->addComponent(pathfinder);

	return map;
}
#pragma endregion

MapBuilder::~MapBuilder() {
}
