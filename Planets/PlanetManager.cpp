//
//
//
//
//
#include <queue>
#include <map>

#include "Path.hpp"
#include "PlanetManager.hpp"
#include "Main.hpp"


uint square(uint x)
{
	return x * x;
}

uint DistanceSquared(Point a, Point b) 
{
	return square(a.x - b.x) + square(a.y - b.y);
}

void GraphData::AddNeighbor(Planet* _new, double _cost)
{
	//Double check that the new planet isn't already a neighbor:
	for (auto it = m_Neighbors.begin(); it != m_Neighbors.end(); it++)
	{
		if (_new == it->pDestination)//Not a new planet
			return;
	}
	Planet_Edge t;
	t.Cost = _cost;
	t.pDestination = _new;
	m_Neighbors.push_back(t);
}

Planet_Edge GraphData::GetNeighborEdge(uint _index)
{
	return m_Neighbors[_index];
}

std::vector<Planet_Edge> GraphData::GetAllNeighbors()
{
	return m_Neighbors; //Hate doing this, has to be done.
}

double GraphData::GetNeighborTravelCost(uint _index)
{
	return m_Neighbors[_index].Cost;
}

Planet* GraphData::GetNeighborPlanet(uint _index)
{
	return m_Neighbors[_index].pDestination;
}

void GraphData::SetPosition(Point _point)
{
	m_Position = _point;
}

uint GraphData::GetNumNeighbors()
{
	return m_Neighbors.size();
}

GraphData::GraphData(Planet* _ptr)
{
	m_pPlanet = _ptr;
}

GraphData::~GraphData()
{
	
}

template <typename T>
uint GetElementPositionInVector(T Element, std::vector<T> arr)
{
	for (uint i = 0; i < arr.size(); i++)
	{
		if (arr[i] == Element) return i;
	}
}

Path PlanetManager::FindPathBetweenNodes(GraphData* Start, GraphData* End)
{
	ShortestPath<GraphData*> PathData;
	std::multimap<GraphData*, GraphData*> Edges;
	Path Path;
	
	uint length = PathData.Resolve(Edges, Start, End, Path);
	return Path;
}

void PlanetManager::Create_Universe()
{
	/*
	* The algorithm is fairly simple:
	* Take every single planet in the set, and assign to it a point 
	*	on a 2d plane.
	* Then go through each planet (or node) and determine it's distance to
	*	every other node in the set.
	* If the distance is below a certain value (5?) then create the connection
	* If there are no connections to a node, increase the threshold until there
	*	is one. Stop after 1 is added however. 
	*/
	
	//Double check that the planet list is initialized
	if (m_PlanetList.size() == 0) return;

	std::vector<Point> Points;
	for (auto it = m_PlanetList.begin(); it != m_PlanetList.end(); it++) 
	{
		uint counter = 0;
	beginning: //I want to cry
		Point t;
		t.x = Rand::GetRandomUINT(0, FIELD_WIDTH);
		t.y = Rand::GetRandomUINT(0, FIELD_HEIGHT);
		//Double check for duplicates:
		for (uint i = 0; i < Points.size(); i++)
		{
			if (Points[i].x == t.x && Points[i].y == t.y)
				goto beginning; //I just died a tiny bit. 
		}
		
		//Point is unique, add it.
		Points.push_back(t);
		m_GraphData[counter++]->SetPosition(t);
	}
	//Time for a really bad for performance algorithm!
	for (uint i = 0; i < Points.size(); i++)
	{
		uint NumConnections = 0;
		uint Radius = 5;
		while (NumConnections == 0)
		{
			for (uint j = 0; j < Points.size(); j++)
			{
				uint Distance = DistanceSquared(Points[i], Points[j]);
				if (Distance < square(Radius))
				{
					m_GraphData[i]->AddNeighbor(m_PlanetList[j], std::sqrt(Distance));
					m_GraphData[j]->AddNeighbor(m_PlanetList[i], std::sqrt(Distance));
				}
			}
			++Radius;
		}
	}
		//for (uint j = 0; j < Points.size(); j++)
		//{
		//	uint Distance = DistanceSquared(Points[i], Points[j]); 
		//	//If the two points are within the proper distance, then add edges for both of them
		//	if (Distance < square(5)) //Start out with 5
		//	{
		//		//Create the connection between the two planets
		//		m_GraphData[i]->AddNeighbor(m_PlanetList[j], std::sqrt(Distance));
		//		m_GraphData[j]->AddNeighbor(m_PlanetList[i], std::sqrt(Distance));
		//	}
		//}
		//if (NumConnections == 0)
		//{
		//	//Redo some of the initialization, except this time with increasing thresholds. 
		//	for (uint distance = 6; distance < (FIELD_HEIGHT < FIELD_WIDTH ? FIELD_WIDTH : FIELD_HEIGHT); distance++)
		//	{
		//		for (uint j = 0; j < Points.size(); j++)
		//		{
		//			uint Distance = DistanceSquared(Points[i], Points[j]) < square(5);
		//			//If the two points are within the proper distance, then add edges for both of them
		//			if (Distance < square(6)) //Start out with 5
		//			{
		//				//Create the connection between the two planets
		//				m_GraphData[i]->AddNeighbor(m_PlanetList[j], distance);
		//				m_GraphData[j]->AddNeighbor(m_PlanetList[i], distance);
		//				return;
		//			}
		//		}
		//	}
		//}
}

void PlanetManager::Tick()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		m_PlanetList[i]->Tick();
	}
}

uint PlanetManager::GetNumPlanets()
{
	return m_PlanetList.size();
}

PlanetManager::PlanetManager()
{
	//Initialize the list of planets.
	for (size_t i = 0; i < NUM_PLANETS; i++)
	{
		Planet* t = new Planet(i);
		m_PlanetList.push_back(t);
		GraphData* a = new GraphData(t);
		m_GraphData.push_back(a);
	}
	Create_Universe();
}


PlanetManager::~PlanetManager()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		delete m_PlanetList[i];
		delete m_GraphData[i];
	}
}