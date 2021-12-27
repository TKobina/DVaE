#pragma once
#include "graph.h"

class Collective : public Graph
{
private:
	map<int, int> nodeMap;
	AttributeDictionary& nodeDict;

	map<int, int> edgeMap;
	AttributeDictionary& edgeDict;

	void remap(vector<shared_ptr<Entity>>& _v, map<int, int>& _m);

	void add_entity(vector<shared_ptr<Entity>>& _v, map<int, int>& _m, shared_ptr<Entity> _e);
	shared_ptr<Entity> get_entity(vector<shared_ptr<Entity>>& _v, map<int, int>& _m, int _id);
	void remove_entity(vector<shared_ptr<Entity>>& _v, map<int, int>& _m, int _id);

public:
	Collective(AttributeDictionary& _nodeDict, AttributeDictionary& _edgeDict);

	void add_node(shared_ptr<Entity> _e);
	shared_ptr<Entity> get_node(int _id);
	void remove_node(int _id);

	void add_edge(shared_ptr<Entity> _e);
	shared_ptr<Entity> get_edge(int _id);
	void remove_edge(int _id);

	void print_all(std::ostream& _out = std::cout);
};
