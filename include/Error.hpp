#pragma once

#include "MyTypes.hpp"

#include <ostream>

class Error {

public:
	void Exit(const char *message);
	void Exit(const str &message);
	void Print(const char *message) const noexcept;
	void Print(const str &message) const noexcept;

	friend ostr &operator<<(ostr &os, const Error &e) noexcept;

	Error() = default;

	bool operator==(const Error &other) const = default;
};

class StaticError : public Error {

public:
	static void Exit(const char *message) { Error().Exit(message); }
	static void Exit(const str &message) { Error().Exit(message); }
	static void Print(const char *message) noexcept { Error().Print(message); }
	static void Print(const str &message) noexcept { Error().Print(message); }

	static friend ostr &operator<<(ostr &os, const StaticError &e) noexcept {

		Error << e;
		 
		
	}

	StaticError() = default;
};
