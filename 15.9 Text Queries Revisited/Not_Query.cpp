#include "Not_Query.h"

Query_Result Not_Query::eval(const Text_Query& text) const
{
	auto result = query_.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return Query_Result(rep(), ret_lines, result.get_file());
}
