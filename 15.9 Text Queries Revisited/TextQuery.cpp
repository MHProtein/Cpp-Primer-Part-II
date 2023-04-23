#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream& ifs) :file(new std::vector<std::string>)
{
	std::string text;
	while (std::getline(ifs, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string word;
		while (line >> word)
		{
			auto& lines = wm[word];
			if (!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);
		}
	}
}

auto QueryResult::begin() const
{
	return lines->begin();
}

auto QueryResult::end() const
{
	return lines->end();
}

auto QueryResult::getfile() const
{
	return file;
}

auto TextQuery::query(const std::string& sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " << (qr.lines->size() < 2 ? "time" : "times") << std::endl;
	for (const auto & num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
	}
	return os;
}


