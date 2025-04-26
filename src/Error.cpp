#include "Error.hpp"

#include <__msvc_ostream.hpp>
#include <intrin.h>
#include <iosfwd>
#include <iostream>
#include <stdexcept>

Error::Error(const STR &message) noexcept : m_message(message) {}

Error::Error(const char *message) noexcept : m_message(message) {}

void Error::Exit(const char *message) {
	__debugbreak();
	Print(message);
	throw std::runtime_error(message);
}

void Error::Exit(const STR &message) { Exit(message.c_str()); }

void Error::Print(const char *message) const {
	std::cerr << message << std::endl;
}

void Error::Print(const STR &message) const {
	return Print(message.c_str());
}

std::ostream &operator<<(std::ostream &os, const Error &Err) {
	os << "Error occurred: " << Err.m_message;
	return os;
}
