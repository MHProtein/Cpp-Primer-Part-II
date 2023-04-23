#include "Query.h"
#include "And_Query.h"
#include "Not_Query.h"
#include "Or_Query.h"
#include "Word_Query.h"

Query::Query(const std::string& word) :q_(new Word_Query(word))
{ 
}

Query operator~(const Query& operand)
{
	return std::shared_ptr<Query_base>(new Not_Query(operand));
}

Query operator|(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new Or_Query(lhs, rhs));
}

Query operator&(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new And_Query(lhs, rhs));
}

std::ostream& operator<<(std::ostream& os, const Query& q)
{
	return os << q.rep();
}
