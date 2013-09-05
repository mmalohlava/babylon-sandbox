/*!
  @file		l2x.cpp
  @brief	latex to xml convertor
  
  Main file of latex to xml project
*/
#include "parser.h"
#include <locale>
#include <iostream>
//#include <strstrea.h>
#include <fstream>

using namespace std;
/*! 
	@brief main function
*/
int main(int argc, char **argv)
{
	
	//istrstream in("\\begin{document} \\end{document}");
	ifstream *in;
	if (argc > 1)
			in = new ifstream(argv[1]);
		else
			in = new ifstream("./!tex/doc0.tex");

	if (!in->is_open()) 
		return -1;
	
	// set LOCALE => for isalpha ... viz. HELP !!!
	printf("Set locale to %s\n----OUT----\n", setlocale( LC_CTYPE, "czech" ));

	Parser parser(reinterpret_cast<std::istream &>(*in), std::cout);
		
	
	while( !parser.IsEnd() )
	{	
		//printf("%d\n", parser.GetToken());
 		parser.GetToken();
	}
	printf("\n---END of OUT---\n");
	delete in;
	
	return 0;
}
 