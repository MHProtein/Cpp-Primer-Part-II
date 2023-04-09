#include <fstream>
#include <iostream>
#include <string>
#include "TextQuery.h"

void runQueries(std::ifstream& infile)
{
	TextQuery tq(infile);
	while(true)
	{
		std::string ans;
		std::cout << "Enter the word to look for, or q to quit: ";
		if (!(std::cin >> ans) || ans == "q")
			break;
		tq.query(ans)
	}
}