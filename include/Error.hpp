#pragma once

#include <iosfwd>
#include <string>

class Error {

public:

	using STR  = std::string;
	using OSTR = std::ostream;

	[[noreturn]]
	void Exit(const char *message);

	[[noreturn]]
	void Exit(const STR &message);

	void Print(const char *message) const noexcept;

	void Print(const STR &message) const noexcept;

	Error() = default;

	bool operator==(const Error &other) const = default;
};

class StaticError : private Error {

public:

	[[noreturn]]
	static void Exit(const char *message) { Error().Exit(message); }

	[[noreturn]]
	static void Exit(const STR &message) { Error().Exit(message); }

	static void Print(const char *message) noexcept { Error().Print(message); }
	static void Print(const STR &message) noexcept { Error().Print(message); }

	StaticError() = default;
};
