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

*/

//#include <iostream>
#include "../data_structure/importer.h"
#include "../data_structure/book.h"

using std::string;

int main()
{
	Book book;
	Importer_CSV* importer = new Importer_CSV();	

	std::ifstream infile;
	infile.open("data/MOCK_NODES.CSV");
	importer->proc_import(book, NODE, infile);
	infile.close();

	infile.open("data/MOCK_EDGES.CSV");
	importer->proc_import(book, EDGE, infile);
	infile.close();

	std::ofstream ofile;
	ofile.open("output/output_log.txt");
	book.print_all(ofile);

	std::cout << std::endl;
	return 0;
}