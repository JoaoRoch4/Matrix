#include "Error.hpp"

#include "MyTypes.hpp"

 #include <intrin.h>

void Error::Exit(const char *message) {
	__CLS();
	__debugbreak();
	std::cerr << message << std::endl;
	throw std::runtime_error(message);
	exit(EXIT_FAILURE);
}

void Error::Exit(const str &message) {}
