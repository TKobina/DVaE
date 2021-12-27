/*
* ================================REFERENCES=================================
* C++
*	std::exception: https://en.cppreference.com/w/cpp/error/exception
*   headers & includes: http://www.cplusplus.com/articles/Gw6AC542/
* UML
*	this project: https://app.moqups.com/h9FeigePnb/edit/page/a1e20da75
*	guide: https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/
* ==================================TO DO====================================
* ALL
*	check parameters
*		const
*		pass by reference
*	check comments on CS2370 Project 4 (out of bounds illegality)
*	THREAD PROTECTION
* ATTRIBUTE.H
*	return string? stringstream?
* ATTRIBUTEDICTIONARY.H
*	format output (output_dictionary()) nicely
*	int/unsigned/size_t for keys/indexes?
* ENTITY.H
*	DERIVE NODE/EDGE CLASSES
*	int/unsigned/size_t for indexes?
*	use exceptions for search algorithms?
* EDGES (ENTITY.H)
*	redesign to hold pointers rather than id's for nodes?
* GRAPH.H/IMPORTER.h
*	throw error if trying to add duplicate id
*	throw error if trying to access non-present entity
*	build iterators for nodes, edges??
*	make dictionaries consts?
* BOOK.H
* IMPORTER.h
*	first field always entity ID; change this?
*	can only currently have nodes in edge.entities (importer.cpp line 46-ish)
* LOGGER.H
*	max lines to hold 
*	control output to file vs screen
* TEST.H
*	build test framework for data structure
*/

#include <iostream>
#include "importer.h"
#include "book.h"

using std::string;

int main()
{
	Book book;
	Importer_CSV* importer = new Importer_CSV();	

	std::ifstream infile;
	infile.open("MOCK_NODES.CSV");
	importer->proc_import(book, NODE, infile);
	infile.close();

	infile.open("MOCK_EDGES.CSV");
	importer->proc_import(book, EDGE, infile);
	infile.close();

	std::ofstream ofile;
	ofile.open("output_log.txt");
	book.print_all(ofile);

	std::cout << std::endl;
	return 0;
}