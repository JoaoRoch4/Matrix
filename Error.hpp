#pragma once

#include "MyTypes.hpp"

#include <iostream>
class Error {

	public:

	void Exit(const char* message);
	void Exit(const str& message);
		
};

class StaticError : public Error {

public:
	inline void Exit(const char* message) { Error().Exit(message); }
	inline void Exit(const str& message) { Error().Exit(message); }
};
