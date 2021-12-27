#pragma once
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include "book.h"

class Importer
{

public:
	virtual void proc_import(Book& book, int type, std::istream& _in) = 0;
};

class Importer_CSV : public Importer
{
private:
	void parse_line(std::string& _line, std::vector<std::string>& _data, char split_char = ',');
public:
	//Importer_CSV();
	void proc_import(Book& _book, int type, std::istream& _in);
};