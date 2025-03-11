#pragma once

#include "MyTypes.hpp"
#include <iostream>

class Error {

public:

	void Exit(const char *message);
	void Exit(const str& message);
	void Print(const char* message) const noexcept;
	void Print(const str& message) const noexcept;

	friend ostr& operator<<(ostr& os, const Error& e) noexcept {
		std::cerr << e;
	}
};

static class StaticError : public Error {

public:
	static inline void Exit(const char* message) { Error().Exit(message); }
	static inline void Exit(const str& message) { Error().Exit(message); }
	static inline void Print(const char* message) noexcept {
		Error().Print(message);
	}
	static inline void Print(const str& message) noexcept {
		Error().Print(message);
	}

	static friend ostr& operator<<(ostr& os, const Error& e) noexcept {
		std::cerr << e;
	}

	StaticError() = default;
};
