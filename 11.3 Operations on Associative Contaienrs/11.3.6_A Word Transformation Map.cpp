#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

auto buildMap(std::ifstream& map)
{
	std::map<std::string, std::string> temp_map;
	std::string key;
	std::string value;
	while (map >> key && std::getline(map, value))
	{
		if (value.size() > 1)
			temp_map[key] = value.substr(1);
		else
			throw std::runtime_error("no value for " + key);
	}
	return temp_map;
}

const std::string& transform(const std::string& s, const std::map<std::string, std::string>& m)
{
	auto it = m.find(s);
	if (it == m.cend())
		return s;
	return it->second;
}

void wordTransformation(std::ifstream& map, std::ifstream& input)
{
	std::map<std::string, std::string> word_map = buildMap(map);
	std::string text;
	while (std::getline(input, text))
	{
		bool isfirstword = true;
		std::string word;
		std::istringstream words(text);
		while(words>>word)
		{
			if (isfirstword)
				isfirstword = false;
			else
				std::cout << " ";
			std::cout << transform(word, word_map);
		}
		std::cout << std::endl;
	}
}