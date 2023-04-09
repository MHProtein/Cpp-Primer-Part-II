#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <functional>
#include <sstream>
#include "StrBlob.h"

int main()
{
	StrBlob sb{ "hi","there" };
	StrBlobPtr p(sb);
	std::plus<StrBlob> sbplus;
	sbplus(StrBlob(), StrBlob());
}