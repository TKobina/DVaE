#pragma once
#include "entity.h"

class Edge : public Entity
{
private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::map<int, int> entityMap;
	const int edgeID;
	void remap_entities();
public:
	int nEntities = 0;
	
	Edge(int _edgeID);
	int get_id();
	void output_all(AttributeDictionary& _dictionary, std::ostream& _out = std::cout);

	void add_entity(std::shared_ptr<Entity> _e);
	std::vector<std::shared_ptr<Entity>>& get_entities();
	void remove_entity(int _key);
};