#pragma once

#include "Random.hpp"


#include <array>
#include <chrono>
#include <exception>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <any>


#define CnExcpt	   const noexcept
#define CExprExcpt constexpr noexcept

#define INLN		 inline
#define INLNCEXPR	 constexpr __forceinline
#define CLEAR_SCREEN "\033[2J\033[1;1H"
#define Make_uptr	 std::make_unique
#define mk_unq		 std::make_unique
#define Make_sptr	 std::make_shared
#define mk_sptr		 std::make_shared

using str	  = std::string;
using ostr	  = std::ostream;
using istr	  = std::istream;
using strstrn = std::stringstream;

using ANY = std::any;

// signed long long 64-bits interger.
// Ocuppies 8 bytes.
// Ranges from
// -9.223.372.036.854.775.808 to 9.223.372.036.854.775.807;
// similar to ll
using big = signed long long;

// const signed 64-bits constant interger.
// Ocuppies 8 bytes.
// Ranges from
// -9.223.372.036.854.775.808 to 9.223.372.036.854.775.807
// similar to ll_c
using big_c = const signed long long;

// unsigned 64-bits interger. Ocuppies 8 bytes. Ranges from 0 to
// 18.446.744.073.709.551.615
// Same as max
using big_u = unsigned long long;

// const unsigned 64-bits constant interger.
// Ocuppies 8 bytes.
// Ranges from 0 to 18.446.744.073.709.551.615
// Same as max_c
using big_cu = const unsigned long long;

using big_v = volatile signed long long;

using big_cv = const volatile signed long long;

using big_vu = volatile unsigned long long;

using big_cvu = const volatile unsigned long long;

// signed 8-bits char.
// Ocuppies 1 byte.
// Ranges from -128 to 127.
using BYTES = signed char;

// const signed 8-bits constant char. Ocuppies 1 BYTES. Ranges from -128 to
// 127. similar to cc
using BYTES_c = const signed char;

// unsigned 8-bits char. Ocuppies 1 BYTES. Ranges from 0 to 255.
using BYTES_u = unsigned char;

// const unsigned 8-bits constant char. Ocuppies 1 BYTES. Ranges from 0 to
// 255.
using BYTES_cu = const unsigned char;

using BYTES_v = volatile signed char;

using BYTES_cv = const volatile signed char;

using BYTES_vu = volatile unsigned char;

using BYTES_cvu = const volatile unsigned char;

// signed 16-bits wide char. Ocuppies 2 BYTESs. Ranges from -32.768
// to 32.767. similar to short
using BYTESW = wchar_t;

using BYTESW_v = volatile wchar_t;

// const signed 16-bits wide char. Ocuppies 2 BYTESs.
// Ranges from -32.768 to 32.767.
// similar to const short
using BYTESW_c = const wchar_t;

using BYTESW_vc = const volatile wchar_t;

// const signed 8-bits constant char. Ocuppies 1 byte however changes with
// use. Ranges from -128 to 127. similar to byte_c
using cc	= signed const char;
using cc_v	= volatile signed const char;
using c_uc	= unsigned const char;
using c_vuc = volatile unsigned const char;

using cstr	= const char *;
using cstrW = const wchar_t *;

using c8	= char8_t;
using c8_c	= const char8_t;
using c8_v	= volatile char8_t;
using c8_vc = const volatile char8_t;

using c16	 = char16_t;
using c16_c	 = const char16_t;
using c16_v	 = volatile char16_t;
using c16_vc = const volatile char16_t;

using c32	 = char32_t;
using c32_c	 = const char32_t;
using c32_v	 = volatile char32_t;
using c32_vc = const volatile char32_t;

// signed 32-bits long interger
using l = signed long;

// const signed 32-bits long interger
using l_c = const signed long;

// unsigned 32-bits long interger
using l_u = unsigned long;

// const unsigned 32-bits long interger
using l_cu = const unsigned long;
using l_v  = volatile signed long;

using l_cv = const volatile signed long;

using l_vu = volatile unsigned long;

using l_cvu = const volatile unsigned long;

// long double
using ld = long double;

// const long double
using ld_c = const long double;

// signed 16-bits interger
using lil = signed short;

// const signed 16-bits interger
using lil_c = const signed short;

// unsigned 16-bits interger
using lil_u = unsigned short;

// unsigned const 16-bits interger
using lil_uc = unsigned const short;

using ll = big;

// const signed 64-bits long long interger
using ll_c		 = const signed long long;
using ll_u		 = unsigned long long;
using ll_uc		 = const unsigned long long;
using MAX		 = unsigned long long;
using MAX_c		 = const unsigned long long;
using min		 = signed char;
using min_c		 = const signed char;
using num		 = signed int;
using num_c		 = const signed int;
using num_u		 = unsigned int;
using num_uc	 = const unsigned int;
using num16		 = signed short;
using num16_c	 = const signed short;
using num16_u	 = unsigned short;
using num16_uc	 = unsigned const short;
using num32		 = signed int;
using num32_c	 = const signed int;
using num32_u	 = unsigned int;
using num32_uc	 = const unsigned int;
using num64		 = signed long long;
using num64_c	 = signed const long long;
using num64_u	 = unsigned long long;
using num64_uc	 = const unsigned long long;
using real		 = float;
using real_c	 = const float;
using real2x	 = double;
using real2x_c	 = const double;
using real4x	 = long double;
using real4x_c	 = long double;
using realMax	 = long double;
using ldoub		 = long double;
using mmword	 = long double;
using longd		 = long double;
using longdouble = long double;
using realMax_c	 = const long double;
using realMax_vc = const volatile long double;
using str		 = std::string;
using str_v		 = volatile std::string;
using str_c		 = const std::string;
using wstr		 = std::wstring;
using wstr_v	 = volatile std::wstring;
using wstr_c	 = const std::wstring;

template <class T, size_t N>
using arr = std::array<T, N>;

template <class T>
using vec = std::vector<T, std::allocator<T>>;

template <class T>
using vec2x = std::vector<vec<T>, std::allocator<vec<T>>>;

template <typename T1, typename T2>
using PAR = std::pair<T1, T2>;

using VecStr = vec<str>;

template <class T, class Deleter = std::default_delete<T>>
using uptr = std::unique_ptr<T, Deleter>;

template <class T>
using sptr = std::shared_ptr<T>;

using namespace std::chrono;

using timePoint = time_point<system_clock>;

using excp = std::exception;

template <typename T1, typename T2>
using VPars = PAR<vec<T1>, vec<T2>>;

template <typename T1, typename T2>
using VPars_Uptr = uptr<PAR<vec<T1>, vec<T2>>>;

template <typename T1, typename T2>
using Matrix2d2 = VPars<T1, T2>;

template <typename T1, typename T2>
using Matrix2d2_uptr = uptr<VPars<T1, T2>>;

using vPar	  = vec<PAR<vec<ld>, vec<ld>>>;
using vParPtr = sptr<vec<PAR<vec<ld>, vec<ld>>>>;
using vLdPar  = PAR<vec<ld>, vec<ld>>;

template <class T>
using numCap = std::numeric_limits<T>;

using UptrRand = uptr<Random>;
using vCols	   = vec<size_t>;
using vRows	   = vec<size_t>;
using VecPar   = vec<PAR<vCols, vRows>>;
using Matrix2d = uptr<VecPar>;

// Clear the screen.

class MyTypes {

public:

	inline void __CLS() { std::cout << CLEAR_SCREEN << std::endl; }
};

// 
