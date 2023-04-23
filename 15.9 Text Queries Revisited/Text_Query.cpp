#include "Text_Query.h"




std::ostream& print(std::ostream& os, const Query_Result& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " << (qr.lines->size() < 2 ? "time" : "times") << std::endl;
	for (const auto& num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
	}
	return os;
}


