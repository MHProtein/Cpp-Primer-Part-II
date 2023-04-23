#include "And_Query.h"
#include <algorithm>

Query_Result And_Query::eval(const Text_Query& text) const
{
	auto left = lhs_.eval(text), right = rhs_.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	//The algorithm writes the elements that appear in both sequences into the destination.
	return Query_Result(rep(), ret_lines, left.get_file());
}
