#pragma once

// TODO: rename...
enum TileType {
	Plains,
	Hills,
	Water,
	Urban,
	Bridge,
	Coast,
	Woods
};

// TODO: rename...
enum SortMode {
	BackToFront,
	FrontToBack,
	Deferred,
	Depth
};

enum StringSplitOptions {
	REMOVE_EMPTY,
	NONE
};

enum TriggerType {
	KEY_TRIGGER,
	BUTTON_TRIGGER
};

// Light: takes alot of damage from all damaging sources.
// Medium: takes small damage from light, some from piercing and alot from explosive sources.
// Heavy: takes next to nothing damage from light, small damage from piercing and some damage 
//	      from explosive sources.

enum ArmorType {
	Light,
	Medium,
	Heavy
};

// Light: good versus light armor.
// Piercing: good versus light and medium armors.
// Explosive: super effective against light and medium armors. Deals some damage
//			  to heavy armor aswel.

enum DamageType {
	LightWeight,
	Piercing,
	Explosive
};

enum OrganicUnit {
	GroundForces,
	AirForces,
	Navy
};
