//
//
//
//
//
#include <string>

#include "StateFactory.h"
#include "Main.hpp"
#include "Planet.hpp"
#include "GraphManager.h"

std::string GenerateStateString(std::vector<Planet*>* Data)
{
	std::string Out;
	GenerateStateString(Data, &Out);
	return Out;
}

void GenerateStateString(std::vector<Planet*>* Data, std::string* State)
{
	for (uint i = 0; i < Data->size(); ++i)
	{
		std::string Str;
		Data->at(i)->CreateState(&Str);
		State->append(Str);
	}
}

std::string GenerateMapString(std::vector<GraphData*>* Data)
{
	std::string Out;
	GenerateMapString(Data, &Out);
	return Out;
}

void GenerateMapString(std::vector<GraphData*>* Data, std::string* State)
{
	for (uint i = 0; i < Data->size(); ++i)
	{
		std::string s;
		s.append(std::to_string(Data->at(i)->GetPlanetRef()->GetID())); //First add in the index.
		s.append(":");
		s.append(std::to_string(Data->at(i)->GetPosition().x));
		s.append(" ");
		s.append(std::to_string(Data->at(i)->GetPosition().y));			//Then the x and y coords
		s.append(",");
		
		std::vector<Graph_Edge> edges = Data->at(i)->GetAllNeighbors();
		for (uint j = 0; j < edges.size(); ++j)							//The list of all the neighbors
		{
			s.append(std::to_string(edges[j].pDestination->GetPlanetRef()->GetID()));
			s.append(" "); //PLEASE NOTE: THERE WILL BE A SPACE JUST BEFORE THE SEMICOLON.
		}
		s.append(";");
		State->append(s);
	}
}