#include "Error.hpp"
#include "MyTypes.hpp"

#include <__msvc_ostream.hpp>
#include <intrin.h>
#include <iostream>
#include <stdexcept>

#pragma diag_suppress 001

void Error::Exit(const char *message) {
	__CLS();
	__debugbreak();
	Print(message);
	return throw std::runtime_error(message);
}

void Error::Exit(const str &message) { return Exit(message.c_str()); }

void Error::Print(const char *message) const noexcept {
	std::cerr << message << std::endl;
}

void Error::Print(const str &message) const noexcept {
	return Print(message.c_str());
}
