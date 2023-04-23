#pragma once
#include <iostream>
#include <ostream>

class DebugDelete
{
public:
	explicit DebugDelete(std::ostream& os = std::cerr) :os_(os) {  }
	template<typename PointerType> void operator()(PointerType ptr)
	{
		if(ptr!=nullptr)
			delete ptr;
		os_ << "shared_ptr deleted" << std::endl;
	}

private:
	std::ostream& os_;
};
