/*
Interface for graph objects
*/
#pragma once

#include <iomanip>

#include <map>
#include <chrono>

#include "entity.h"
#include "attribute_dictionary.h"

using std::vector;
using std::map;
using std::shared_ptr;

class Graph
{
protected:
	vector<shared_ptr<Entity>> nodes;
	vector<shared_ptr<Entity>> edges;
public:
	virtual	void add_node(shared_ptr<Entity> _e) = 0;
	virtual shared_ptr<Entity> get_node(int _id) = 0;
	virtual void remove_node(int _id) = 0;

	virtual void add_edge(shared_ptr<Entity> _e) = 0;
	virtual shared_ptr<Entity> get_edge(int _id) = 0;
	virtual void remove_edge(int _id) = 0;

	virtual void print_all(std::ostream& _out = std::cout) = 0;
};
