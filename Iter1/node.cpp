#include "node.h"

Node::Node(int _nodeID) : nodeID(_nodeID) {}

int Node::get_id() { return nodeID; }

void Node::output_all(AttributeDictionary& _dictionary, std::ostream& _out)
{
	_out << "\n" << LDIVIDE << "\nNode ID | " << nodeID << SDIVIDE << "\nAttributes:";
	for (std::shared_ptr<_Attribute> attribute : attributes)
	{
		_out << "\n" << _dictionary.get_definition(attribute->get_key()) << " | ";
		_out << attribute->get_value();
	}
}