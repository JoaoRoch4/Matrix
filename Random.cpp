#include "MyTypes.hpp"
#include "Random.hpp"
#include <random>
#include <vector>

Random::Random() noexcept
	: gen(std::random_device {}()),
	  dist_float(),
	  dist_double(),
	  dist_longdouble(),
	  dist_int(),
	  dist_SizeT(),
	  Num_real(),
	  Num_Int() {}

Random::Random(const Random &other) noexcept : Random() {

	if (&other != this) {

		gen		 = other.gen;
		Num_real = other.Num_real;
	}
}

Random &Random::operator=(const Random &other) noexcept {
	if (this != &other) {
		gen		 = other.gen;
		Num_real = other.Num_real;
	}
	return *this;
}

Random &Random::operator=(const int other) noexcept {
	Num_Int = other;
	return *this;
}

long double Random::GetRandomNum() noexcept {
	const long double getNum {dist_longdouble(gen)};
	Num_real = getNum;
	return getNum;
}

