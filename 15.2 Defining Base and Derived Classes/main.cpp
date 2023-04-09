#include "Quote.h"

int main()
{
	//Because a derived object contains subparts corresponding to its base classes, we can use an object of a derived type as if it were an object of its base types.
	//In particular, we can bind a base-class reference or pointer to the base-class part of a derived object

	Quote item;
	Bulk_Quote bulk;
	Quote* p = &item;
	p = &bulk;
	Quote& r = bulk;
	r.
}