/*

*/
#include "../graphics_engine/graphics_engine.h"
#include "../data_structure/importer.h"
#include "../data_structure/book.h"

int main()
{
	Book book;
	Importer_CSV* importer = new Importer_CSV();	

	GraphicsEngine g_engine;
	
	std::ifstream infile;
	infile.open("data/MOCK_NODES.CSV");
	importer->proc_import(book, NODE, infile);
	infile.close();

	infile.open("data/MOCK_EDGES.CSV");
	importer->proc_import(book, EDGE, infile);
	infile.close();

	if (!g_engine.initialize()) return -1;
	g_engine.run();
	

	std::ofstream ofile;
	ofile.open("output/output_log.txt");
	book.print_all(ofile);

	std::cout << std::endl;
	return 0;
}