#pragma once

#include "MyTypes.hpp"
#include <iosfwd>
#include <iostream>

class Error {

public:
	bool Exit();
	bool Exit(const char* message);
	bool Exit(const str& message);

	bool ExitCondition(const bool& condition, const str& message);
	bool ExitCondition(const bool& condition, const char* message);
	
	void Print(const char* message) const noexcept;
	void Print(const str& message) const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Error& e) noexcept {
		std::cerr << e;
		return os;
	}
};

class StaticError : public Error {

public:
	static inline void Exit(const char* message) { Error().Exit(message); }
	static inline void Exit(const str& message) { Error().Exit(message); }
	static inline void Print(const char* message) noexcept {
		Error().Print(message);
	}
	static inline void Print(const str& message) noexcept {
		Error().Print(message);
	}

	static friend std::ostream& operator<<(std::ostream&	  os,
										   const StaticError& e) noexcept {
		os << static_cast<const Error&>(e);
		return os;
	}

	StaticError() = default;
};

#define CheckPtr(Ptr)                                                   \
	if (Ptr == nullptr) {                                               \
		const str& __msg {str("Error:" #Ptr                             \
							  "is null. " __FUNCTION__ "\n at Line: " + \
							  ##__LINE__)};                             \
		Error	   err;                                                 \
		err.Exit(__msg);                                                \
	}