#ifndef TROOP_H
#define TROOP_H

#include <string>

enum UnitId
{
	PEASANT = 0,
	MILITIAS,
	ARCHERS,
	PIKEMEN,
	CAVALRIES,
	KNIGHTS,
	NOMADS,
	DWARVES,
	WOLVES,
	OGRES,
	TROLLS,
	DRAGONS,
	DEMONS,
	ZOMBIES,
	SKELETONS,
	GHOSTS,
	DRUIDS,
	ARCHMAGES,
	ORCS,
	ELVES,
	VAMPIRES,
	SPRITES,
	GNOMES,
	BARBARIANS,
	GIANTS,
	NumUnits
};

extern const std::string kUnitNames[NumUnits];
extern const std::string kUnitTextures[NumUnits];

#endif // TROOP_H
