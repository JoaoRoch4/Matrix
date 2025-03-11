#include "Random.hpp"
#include <random>

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

const long double Random::GetRandomNum() noexcept {
	const long double getNum {dist_longdouble(gen)};
	Num_real = getNum;
	return getNum;
}

template <typename T>
void Random::fillRandomVec(std::vector<T> &vec) noexcept {

	vec.reserve(vec.size());

	for (size_t i = 0; i < vec.size(); ++i) vec.push_back(dist_longdouble(gen));

	return;
}
