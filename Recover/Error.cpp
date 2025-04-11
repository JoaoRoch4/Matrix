#include "Error.hpp"

#include <__msvc_ostream.hpp>
#include <intrin.h>
#include <iosfwd>
#include <iostream>
#include <stdexcept>

void Error::Exit(const char *message) {
	__debugbreak();
	Print(message);
	throw std::runtime_error(message);
}

void Error::Exit(const STR &message) { Exit(message.c_str()); }

void Error::Print(const char *message) const noexcept {
	std::cerr << message << std::endl;
}

void Error::Print(const STR &message) const noexcept {
	return Print(message.c_str());
}

using OSTR = std::ostream;
OSTR &operator<<(OSTR &os, const Error &e) noexcept {
	std::cerr << e << std::endl;
	return os;
}
