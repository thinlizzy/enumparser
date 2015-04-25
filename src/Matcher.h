#ifndef MATCHER_H_ENUM_PARSER_2015_04_24
#define MATCHER_H_ENUM_PARSER_2015_04_24

#include <string>
#include <bitset>

class Matcher {
	std::bitset<256> matchers;
public:
	Matcher() = default;
	Matcher(char ch);
	Matcher(std::string const & chars);
	Matcher & addRange(char first, char last);
	Matcher & addChar(char ch);
	Matcher reverse() const;
	bool matches(char ch) const;
};

#endif
