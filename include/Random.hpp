#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <type_traits>
#include <vector>

class Random {

protected:

	std::mt19937_64 gen;

	std::uniform_real_distribution<float>		dist_float;
	std::uniform_real_distribution<double>		dist_double;
	std::uniform_real_distribution<long double> dist_longdouble;
	std::uniform_int_distribution<int>			dist_int;
	std::uniform_int_distribution<size_t>		dist_SizeT;

	long double Num_real;
	size_t		Num_Int;

public:

	Random() noexcept;
	~Random() noexcept = default;

	// Copy constructor
	Random(const Random &other) noexcept;

	// Move constructor
	Random(Random &&other) noexcept = default;

	// Copy assignment operator
	Random &operator=(const Random &other) noexcept;

	// Assignment operator
	Random &operator=(const int other) noexcept;

	// Move assignment operator
	Random &operator=(Random &&other) noexcept = default;

	// Assignment reference operator
	Random &operator=(Random &Other) noexcept = default;

	// Assignment pointer operator
	Random &operator*(Random *OtherPtr) noexcept { return *this; }

	inline Random  GetRandom() const noexcept { return *this; }
	inline Random &GetRandomRef() noexcept { return *this; }
	inline Random *GetRandomPtr() noexcept { return this; }

	const long double GetRandomNum() noexcept;

	template <typename T>
	T GetRandomReal(const T cap) noexcept {
		T Get {};
		Num_real = dist_longdouble(gen);
		Get		 = static_cast<T>(Num_real);
		if (Get > cap) return cap;
		return Get;
	}

	template <typename T>
	T GetRandomReal() noexcept {
		T Get {};
		Num_real = dist_longdouble(gen);
		Get		 = static_cast<T>(Num_real);
		return Get;
	}

	template <typename T>
	T GetRandomInt() noexcept {
		T Get {};
		Num_Int = dist_SizeT(gen);
		Get		= static_cast<T>(Num_Int);
		return Get;
	}

	template <typename T>
	T GetRandomIntRange(const int &num1, const int &num2) {

		using intDist = std::uniform_int_distribution<int>;
		intDist dist(num1, num2);
		auto	result = dist(gen);
		T		Get	   = static_cast<T>(result);
		return Get;
	}

	template <typename T>
	T GetRandomInt(const size_t cap) noexcept {
		T Get {};
		Num_Int = dist_SizeT(gen);
		Get		= static_cast<T>(Num_Int);
		if (Get > cap) return cap;
		return Get;
	}

	template <typename T>
	T GetRandomAny() {
		if constexpr (std::is_integral<T>::value) {

			T Get {};
			Num_Int = dist_SizeT(gen);
			Get		= static_cast<T>(Num_Int);

			return Get;

		} else if constexpr (std::is_floating_point<T>::value) {

			T Get {};
			Num_real = dist_longdouble(gen);
			Get		 = static_cast<T>(Num_real);

			return Get;

		} else if constexpr (!(std::is_integral<T>::value ||
							   std::is_floating_point<T>::value)) {
			std::cout << "Unknown type.\n";
		}
	}

	template <typename T>
	T GetRandomAny(const T cap) {

		T Get {};

		if (std::is_integral<T>::value) {

			Num_Int = dist_SizeT(gen);
			Get		= static_cast<T>(Num_Int);
			if (Get > cap) return cap;

			return Get;

		} else if (std::is_floating_point<T>::value) {

			Num_real = dist_longdouble(gen);
			Get		 = static_cast<T>(Num_real);
			if (Get > cap) return cap;

			return Get;

		} else {
			std::cout << "Unknown type.\n";
		}
	}

	template <typename T>
	T GetRandomAny(const size_t min, const size_t max) {

		T Get {};

		if (std::is_integral<T>::value) {

			std::uniform_int_distribution<T> dist(min, max);

			Get = static_cast<T>(dist(gen));

			return Get;

		} else if (std::is_floating_point<T>::value) {

			std::uniform_real_distribution<T> dist(min, max);

			Get = static_cast<T>(dist(gen));

			return Get;

		} else {
			std::cout << "Unknown type.\n";
		}
	}

	template <typename T>
	T GetRandomAny(const float min, const float max) {

		T Get {};

		if (std::is_integral<T>::value) {

			int iMin = static_cast<int>(min);
			int iMax = static_cast<int>(max);

			std::uniform_int_distribution<T> dist(iMin, iMax);

			Get = static_cast<T>(dist(gen));

			return Get;

		} else if (std::is_floating_point<T>::value) {

			std::uniform_real_distribution<T> dist(min, max);

			Get = static_cast<T>(dist(gen));

			return Get;

		} else {
			std::cout << "Unknown type.\n";
		}
	}

	using UptrRand = std::unique_ptr<Random>;

	UptrRand GetrdUptr() { return std::make_unique<Random>(*this); };

	template <typename T>
	void fillRandomVec(std::vector<T> &vec) noexcept;
};

class StaticRandom : protected Random {

public:

	StaticRandom() noexcept {}
	~StaticRandom() = default;

	StaticRandom(const StaticRandom &other)				   = default;
	StaticRandom &operator=(const StaticRandom &other)	   = default;
	StaticRandom(StaticRandom &&other) noexcept			   = default;
	StaticRandom &operator=(StaticRandom &&other) noexcept = default;

	inline const static Random GetRandomStatic() {
		static std::unique_ptr<Random> random = std::make_unique<Random>();
		return random->GetRandom();
	}

	inline static Random *GetRandomStaticPtr() {
		static std::unique_ptr<Random> random = std::make_unique<Random>();
		return random->GetRandomPtr();
	}

	inline const static Random &GetRandomStaticRef() {
		static std::unique_ptr<Random> random = std::make_unique<Random>();
		return random->GetRandomRef();
	}

	bool operator==(const StaticRandom &other) const = default;
};

/* signed */
/* const signed */			  // _c
/* unsigned */				  // _u
/* const unsigned */		  // _cu
/* volatile signed */		  // _v
/* const volatile signed */	  // _cv
/* volatile unsigned */		  // _vu
/* const volatile unsigned */ // _cvu
