#include "Or_Query.h"

Query_Result Or_Query::eval(const Text_Query& text) const
{
	auto right = rhs_.eval(text), left = lhs_.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());
	return Query_Result(rep(), ret_lines, left.get_file());
}
