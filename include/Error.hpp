#pragma once

#include <iostream>
#include <iosfwd>
#include <string>

using STR  = std::string;
using OSTR = std::ostream;

class Error {

	STR m_message;
	

public:

	inline Error() noexcept = default;

	inline Error(const Error &other) noexcept = default;

	inline Error(Error &&other) noexcept = default;

	Error(const STR &message) noexcept;

	Error(const char *message) noexcept;

	[[noreturn]]
	void Exit(const char *message);

	[[noreturn]]
	void Exit(const STR &message);

	void Print(const char *message) const;

	void Print(const STR &message) const;

	friend std::ostream &operator<<(std::ostream &os, const Error &Err);

};

class StaticError : private Error {

public:

	[[noreturn]]
	static void Exit(const char *message) {
		Error().Exit(message);
	}

	[[noreturn]]
	static void Exit(const STR &message) {
		Error().Exit(message);
	}

	static void Print(const char *message) noexcept { Error().Print(message); }
	static void Print(const STR &message) noexcept { Error().Print(message); }

	StaticError() = default;
};
