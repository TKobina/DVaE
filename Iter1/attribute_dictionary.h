#pragma once

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "misc.h"

class AttributeDictionary
{
private:
	std::map<int, std::string> dictionary;
	std::map<std::string, int> rdictionary;
	int lastKey = 0;
public:
	void add_definition(std::string _definition);
	void set_definition(int _key, std::string _definition);
	std::string get_definition(int _key);
	void remove_definition(int _key);
	
	int get_key(std::string _definition);

	void output_dictionary(std::ostream& _out);
};


