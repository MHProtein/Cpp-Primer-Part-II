#include "Query.h"
#include "Text_Query.h"
#include "fstream"
#include <iostream>

int main()
{
	std::ifstream s("D:\\C++ Primer Part II\\15.9 Text Queries Revisited\\Weight.txt");
	auto q = ~Query("girl") & Query("the");
	auto ans = q.eval(Text_Query(s));
	print(std::cout , ans);
}
