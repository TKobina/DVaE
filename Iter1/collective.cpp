#include "collective.h"

Collective::Collective(AttributeDictionary& _nodeDict, AttributeDictionary& _edgeDict) :
	nodeDict(_nodeDict), edgeDict(_edgeDict) {}

void Collective::remap(vector<shared_ptr<Entity>>& _v, map<int, int>& _m)
{
	_m.clear();
	for (size_t i = 0; i < _v.size(); ++i)
	{
		_m.emplace(_v[i]->entityID, i);
	}
}

void Collective::add_entity(vector<shared_ptr<Entity>>& _v, map<int, int>& _m, shared_ptr<Entity> _e)
{
	_v.push_back(_e);
	_m.emplace(_e->entityID, _v.size() - 1);
}

shared_ptr<Entity> Collective::get_entity(vector<shared_ptr<Entity>>& _v, map<int, int>& _m, int _id)
{
	int index = _m[_id];
	return _v[index];
}

void Collective::remove_entity(vector<shared_ptr<Entity>>& _v, map<int, int>& _m, int _id)
{
	int index = _m[_id];
	_v.erase(_v.begin() + index);
	remap(_v, _m);
}

void Collective::add_node(shared_ptr<Entity> _e)
{
	add_entity(nodes, nodeMap, _e);
}

shared_ptr<Entity> Collective::get_node(int _id)
{
	return get_entity(nodes, nodeMap,_id);
}

void Collective::remove_node(int _id)
{
	remove_entity(nodes, nodeMap, _id);
}

void Collective::add_edge(shared_ptr<Entity> _e)
{
	add_entity(edges, edgeMap, _e);
}

shared_ptr<Entity> Collective::get_edge(int _id)
{
	return get_entity(edges, edgeMap, _id);
}

void Collective::remove_edge(int _id)
{
	remove_entity(edges, edgeMap, _id);
}

void Collective::print_all(std::ostream& _out)
{
	/*
	_out << "\nNODE DICTIONARY:";
	nodeDict.output_dictionary(_out);
	*/

	_out << "\nNODES: ";
	_out << LDIVIDE;
	for (auto& node : nodes)
	{
		//_out << std::setfill('=') << std::setw(5);  //NOT WORKING WHY???
		node->output_all(nodeDict, _out);
		_out << SDIVIDE;
	}
	_out << "\n";

	/*
	_out << "\nEDGE DICTIONARY:";
	edgeDict.output_dictionary(_out);
	*/

	_out << "\nEDGES:";
	_out << LDIVIDE;
	for (auto& edge : edges)
	{
		edge->output_all(edgeDict, _out);
		_out << SDIVIDE;
	}

	_out << "\n";
}

