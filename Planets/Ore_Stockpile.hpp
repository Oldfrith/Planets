//
//
//
//
//
#pragma once
#include <string>
#include <map>
#include <vector>

#include "Main.hpp"
typedef unsigned int uint;

#define NUM_ORES 8

typedef std::string Ore;


//The generator for all the ores. 
class OreNameGenerator
{
	std::vector<Ore> m_OreList;
public:
	std::vector<Ore> GetMasterOreList();
	OreNameGenerator();
	~OreNameGenerator();
};

//The actual interface each planet uses.
class Ore_Map
{
	std::map<Ore, uint> m_OreMap;
	std::vector<Ore> m_OreList;

public:
	uint GetOreAmount(Ore _ore);
	void SetOreAmount(Ore _ore, uint _amount);
	void AddOreAmount(Ore _ore, uint _amount);
	bool RemoveOreAmount(Ore _ore, uint _amount);
	void AddOre(Ore _ore, uint _amount = 0);
	void RemoveOre(Ore _ore);

	std::vector<Ore> GetOreList();
	uint GetTotalAmount();
	Ore_Map();
	~Ore_Map();
};