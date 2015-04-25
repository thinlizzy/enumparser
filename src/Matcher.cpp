#include "Matcher.h"

Matcher::Matcher(char ch)
{
	matchers.set(ch);
}

Matcher::Matcher(std::string const & chars)
{
	for( char ch : chars ) {
		matchers.set(ch);
	}
}

Matcher & Matcher::addRange(char first, char last)
{
	for( char ch = first; ch <= last; ++ch ) {
		matchers.set(ch);
	}
	return *this;
}

Matcher & Matcher::addChar(char ch)
{
	matchers.set(ch);
	return *this;
}

Matcher Matcher::reverse() const
{
	Matcher matcher(*this);
	matcher.matchers.flip();
	return matcher;
}

bool Matcher::matches(char ch) const
{
	return matchers[ch];
}
