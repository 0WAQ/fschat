#include "ulti.h"

unsigned char toHex(unsigned char c)
{
	return c > 9 ? c + 55 : c + 48;
}

unsigned char fromHex(unsigned char c)
{
	unsigned char x = 0;
	if (c >= 'A' && c <= 'Z') x = c - 'A' + 10;
	else if (c >= 'a' && c <= 'z') x = c - 'a' + 10;
	else if (c >= '0' && c <= '9') x = c - '0';
	else assert(0);
	return x;
}

std::string urlEncode(const std::string& s)
{
	std::string tmp{ "" };

	size_t len = s.size();
	for (unsigned char c : s) {
		if (isalnum(c) ||
			(c == '-') ||
			(c == '_') ||
			(c == '.') ||
			(c == '~'))
		{
			tmp += c;
		}
		else if (c == ' ') {
			tmp += '+';
		}
		else {
			tmp += '%';
			tmp += toHex(c >> 4);
			tmp += toHex(c & 0x0F);
		}
	}
	return tmp;
}

std::string urlDecode(const std::string& s)
{
	std::string tmp{ "" };

	size_t len = s.size();
	for (size_t i = 0; i < len; ++i) {
		unsigned char c = s[i];
		if (c == '+') {
			tmp += ' ';
		}
		else if (c == '%') {
			assert(i + 2 < len);
			unsigned char high = fromHex((unsigned char)s[++i]);
			unsigned char low = fromHex((unsigned char)s[++i]);
			c += high * 16 + low;
		}
		else {
			tmp += c;
		}
	}
	return tmp;
}
