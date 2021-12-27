#pragma once
#include "entity.h"

class Node : public Entity
{
private:
	const int nodeID;
public:
	Node(int _nodeID);
	int get_id();
	void output_all(AttributeDictionary& _dictionary, std::ostream& _out = std::cout);
};