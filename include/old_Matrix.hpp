#pragma once

#include "Colors.hpp"
#include "MyTypes.hpp"
#include "Random.hpp"
#include <concepts>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

/**
 * @brief Proxy that represents one row of the matrix integer type.
 */
class MatrixRowProxyInt {

	vec<vec<long long>> m_vvData;
	unsigned long long	m_row;
	
public:
	
	/**
	 * @brief Deleted Default Constructor.
	 */
	inline MatrixRowProxyInt() = delete;

	/**
	 * @brief Default Constructor with parameters.
	 * @param data new value for the class member m_vvData.
	 * @param row new value for the class member m_row.
	 */
	[[nodiscard]]
	inline MatrixRowProxyInt(vec<vec<long long>> &data,
							 unsigned long long	  row) noexcept
	  : m_vvData(data), m_row(row) {}

	/**
	 * @brief m_vvData getter.
	 * @return  m_vvData reference.
	 */
	inline vec<vec<long long>> &GetData() noexcept { return m_vvData; }

	/**
	 * @brief SetData setter.
	 * @param data new value for the class member m_vvData.
	 */
	inline void SetData(vec<vec<long long>> &data) noexcept { m_vvData = data; }

	/**
	 * @brief Returns a reference to the element at the given column.
	 *
	 * (after converting the index to unsigned long long) in the
	 *  current row of the matrix.. The [[nodiscard]] attribute
	 *  encourages users of the operator not to ignore the return value.
	 *
	 * @param col The function takes an integral parameter (the column index)
	 *  using a C++20 concept (std::integral auto) to ensure the argument is
	 *  an integral type..
	 *
	 */
	[[nodiscard]]
	inline long long &operator[](std::integral auto col) {
		return m_vvData[m_row][static_cast<unsigned long long>(col)];
	}

	/**
	 * @brief Returns Const a reference to the element at the given column.
	 *
	 * (after converting the index to unsigned long long) in the
	 * current row of the matrix.. The [[nodiscard]] attribute
	 * encourages users of the operator not to ignore the return value.
	 *
	 * @param col The function takes an integral parameter (the column index)
	 * using a C++20 concept (std::integral auto) to ensure the argument is
	 *	an integral type..
	 *
	 */
	[[nodiscard]]
	inline const long long &operator[](std::integral auto col) const {
		return m_vvData[m_row][static_cast<unsigned long long>(col)];
	}
};

template <typename Fp = long double>
class MatrixRowProxyFloat {

	vec<vec<Fp>> m_vvData;
	size_t		 m_row;

public:

	/**
	 * @brief Deleted Default Constructor.
	 */
	inline MatrixRowProxyFloat() = delete;

	/**
	 * @brief Default Constructor with parameters.
	 * @param data new value for the class member m_vvData.
	 * @param row new value for the class member m_row.
	 */
	[[nodiscard]]
	inline MatrixRowProxyFloat(vec<vec<Fp>>		 &data,
							   unsigned long long row) noexcept
	  : m_vvData(data), m_row(row) {}

	/**
	 * @brief m_vvData getter.
	 * @return  m_vvData reference.
	 */
	inline vec<vec<Fp>> &GetData() noexcept { return m_vvData; }

	/**
	 * @brief SetData setter.
	 * @param data new value for the class member m_vvData.
	 */
	inline void SetData(vec<vec<Fp>> &data) noexcept { m_vvData = data; }

	// Non-const access using concepts
	[[nodiscard]]
	inline long double &operator[](std::floating_point auto col) {
		return m_vvData[m_row][static_cast<Fp>(col)];
	}

	// Const access using concepts
	[[nodiscard]]
	const long long &operator[](std::floating_point auto col) const {
		return m_vvData[m_row][static_cast<long double>(col)];
	}
};

class Matrix {

	using vPar	  = vec<PAR<vec<ld>, vec<ld>>>;
	using vParPtr = sptr<vec<PAR<vec<ld>, vec<ld>>>>;
	using vLdPar  = PAR<vec<ld>, vec<ld>>;
	using vLlPar  = PAR<vec<ll>, vec<ll>>;

	size_t		  m_iRows;
	size_t		  m_iCols;
	vec<vec<int>> m_vvData;

	// Default constructor
	[[nodiscard("Default constructor")]]
	Matrix() noexcept;

public:

	// Parameter constructor
	[[nodiscard]]
	Matrix(const size_t &Rows, const size_t &Cols) noexcept;

	// Copy constructor
	[[nodiscard]]
	Matrix(const Matrix &other) noexcept;

	// Move constructor
	[[nodiscard]]
	Matrix(Matrix &&Matrix) noexcept;

	// Constructor with all parameters
	// Matrix(const size_t &m_iRows, const size_t &m_iCols, const vec<ld>
	// &m_vRows, const vec<ld> &m_vCols, const vLdPar &m_vPar_RowsCols, const
	// vPar &m_vPar_Matrix, const vParPtr &m_vParPtr_Matrix) noexcept;

	// Reference assignment operator
	Matrix &operator=(const Matrix &obj) noexcept;

	// const Reference assignment operator
	const Matrix &operator=(const Matrix &obj) const noexcept;

	// array subscript copy operator
	template <typename ret, typename arg>
	ret operator[](arg index) noexcept {}
	// array subscript reference operator
	template <typename ret, typename arg>
	ret &operator[](arg &index) noexcept {}

	// const array subscript copy operator
	template <typename ret, typename arg>
	const ret operator[](arg index) const noexcept {}

	// const array subscript reference operator
	template <typename ret, typename arg>
	const ret &operator[](arg &index) const noexcept {}

	// getters
	template <typename num = long long>
	INLN num GetRows() CnExcpt {
		if constexpr (typeid(num) != typeid(long long)) {
			num newV = static_cast<num>(m_iRows);
			return newV;
		}
		return m_iRows;
	}

	template <typename num = long long>
	INLN num GetCols() CnExcpt {
		if constexpr (typeid(num) != typeid(long long)) {
			num newV = static_cast<num>(m_iCols);
			return newV;
		}
		return m_iCols;
	}

	template <typename num = long long>
	INLN vec<num> GetM_vRows() CnExcpt {

		if constexpr (typeid(num) != typeid(long long)) {
			vec<num> newVec = static_cast<vec<num>>(m_vRows);
			return newVec;
		}
		return m_vRows;
	}

	template <typename num = long long>
	INLN vec<num> GetM_vCols() CnExcpt {
		if constexpr (typeid(num) != typeid(long long)) {
			vec<num> newVec = static_cast<vec<num>>(m_iCols);
			return newVec;
		}
		return m_iCols;
	}


	// Setters
	INLN void SetGetRows(const size_t &iRows) noexcept { m_iRows = iRows; }
	INLN void SetCols(const size_t &iCols) noexcept { m_iCols = iCols; }

};

template <typename Type>
class Matrix_T : public Matrix {

private:

	bool			  M_bCalled;
	UptrRand		  M_Rand;
	size_t			  M_iRows;
	size_t			  M_iCols;
	vec<Type>		  M_VecCows;
	vec<Type>		  M_VecCols;
	VPars<Type, Type> M_iiVecPair;
	VecPar			  M_VecPar;
	Matrix2d		  M_Matrix;

public:

	/** Default constructor
	 * Initializes the random number generator and a random matrix.
	 */
	Matrix_T() noexcept;

	// Copy constructor
	Matrix_T(const Matrix_T &other, const bool bDelete_vectors = false);

	// full constructor
	Matrix_T(const bool bFill, const bool bDelete_vectors = false);

	// Constructor with Rows and Cols parameters
	Matrix_T(const int Rows, const int Cols, bool bDelete_vectors = false);

	// Constructor with Rows and Cols parameters also vectors
	Matrix_T(const size_t Rows, const size_t Cols, vec<Type> &Vec1,
			 vec<Type> &Vec2);

protected:

	void Start();

	void Fill(bool bDelete_vectors = true);
	void Fill(const Type Rows, const Type Cols, bool bDelete_vectors = true);
	void Fill(const size_t Rows, const size_t Cols, vec<Type> &vec1,
			  vec<Type> &vec2, bool bDelete_vectors = true);

	template <typename... Vectors>
	inline void delete_vectors(Vectors &...vecs) {
		(vecs.clear(), ...);
		(vecs.shrink_to_fit(), ...);
	}

public:

	inline void SetRows(const Type &Rows) noexcept { M_iRows = Rows; }
	inline Type GetRows() const noexcept { return M_iRows; }

	inline void SetCols(const Type &Cols) noexcept { M_iCols = Cols; }
	inline Type GetCols() const noexcept { return M_iCols; }

	inline void SetVrows(const vec<Type> &vec) noexcept { M_VecCows = vec; }
	inline vec<Type> GetVrows() const noexcept { return M_VecCows; }

	inline void SetMatrix(const Matrix2d &matrix) { *M_Matrix = *matrix; }
	// inline Matrix2d GetMatrix() const noexcept { return M_Matrix; }

	UptrRand &GetRandom() noexcept { return M_Rand; }

	void fillVectors(vec<Type> &vec1, const size_t VecSize1, vec<Type> &vec2,
					 const size_t VecSize2);

	void
	fillVectors(vec<Type> &vec1, const size_t VecSize1, const size_t vec1Min,
				const size_t vec1Max, vec<Type> &vec2, const size_t VecSize2,
				const size_t vec2Min, const size_t vec2Max);

	void
	fillVectors(vec<Type> &vec1, const size_t VecSize1, const float vec1Min,
				const float vec1Max, vec<Type> &vec2, const size_t VecSize2,
				const float vec2Min, const float vec2Max);

	bool operator==(const Matrix_T &other) const = default;

	Matrix_T &operator=(const Matrix_T &other) = default;

	void GetMatrix();
	void printMatrix();

	~Matrix_T() = default;
};

template <typename Type>
inline Matrix_T<Type>::Matrix_T() noexcept
  : M_bCalled(false),
	M_Rand(mk_unq<Random>()),
	M_iRows(1),
	M_iCols(1),
	M_VecCows(vec<Type>()),
	M_VecCols(vec<Type>()),
	M_iiVecPair(VPars<Type, Type>()),
	M_VecPar(VecPar()),
	M_Matrix(mk_unq<VecPar>(M_VecPar)) {}

template <typename Type>
inline void Matrix_T<Type>::Start() {
	fillVectors(M_VecCows, M_iRows, M_VecCols, M_iCols);

	M_iiVecPair = std::make_pair(M_VecCows, M_VecCols);

	M_VecPar.reserve(M_VecCows.size() + M_VecCols.size());

	M_iiVecPair.first.reserve(M_VecCows.size());
	M_iiVecPair.second.reserve(M_VecCols.size());

	M_VecPar.reserve(M_VecCows.size() + M_VecCols.size());
}

template <typename Type>
inline Matrix_T<Type>::Matrix_T(const Matrix_T &other,
								const bool		bDelete_vectors) {

	M_iRows		= other.M_iRows;
	M_iCols		= other.M_iCols;
	M_VecCows	= other.M_VecCows;
	M_VecCols	= other.M_VecCols;
	M_iiVecPair = other.M_iiVecPair;
	M_iiVecPair = other.M_iiVecPair;

	if (other.M_Matrix) *M_Matrix = *other.M_Matrix;
	else {
		const str &msg = str(
			"Error: Matrix is null." __FUNCTION__ "\n at Line: " + __LINE__);
		std::cerr << msg;
		throw std::runtime_error(msg);
	}
	if (bDelete_vectors) delete_vectors(M_VecCows, M_VecCols, M_iiVecPair);
}

template <typename Type>
inline Matrix_T<Type>::Matrix_T(const bool bFill, const bool bDelete_vectors)
  : Matrix_T() {
	if (bFill) { Fill(M_iRows, M_iCols, bDelete_vectors); }
}

template <typename Type>
inline Matrix_T<Type>::Matrix_T(const int Rows, const int Cols,
								bool bDelete_vectors)
  : Matrix_T(true) {

	M_iRows	 = Rows;
	M_iCols	 = Cols;
	M_Matrix = nullptr;
	// UNDONE CheckPtr(M_Matrix);
}

template <typename Type>
Matrix_T<Type>::Matrix_T(const size_t Rows, const size_t Cols, vec<Type> &Vec1,
						 vec<Type> &Vec2)
  : Matrix_T(true) {

	M_iRows	  = Rows;
	M_iCols	  = Cols;
	M_VecCols = Vec1;
	M_VecCols = Vec2;
}

template <typename Type>
inline void
Matrix_T<Type>::Fill(const Type Rows, const Type Cols, bool bDelete_vectors) {

	fillVectors(M_VecCows, M_iRows, M_VecCols, M_iCols);

	const size_t size = M_VecCows.size() + M_VecCols.size();

	M_iiVecPair = std::make_pair(M_VecCows, M_VecCols);
	M_iiVecPair.reserve(size);
	M_iiVecPair.push_back(M_iiVecPair);

	M_Matrix->reserve(size);
	M_Matrix->push_back(M_iiVecPair.back());

	if (M_Matrix == nullptr) {

		const str &msg = str(
			"Error: Matrix is null." __FUNCTION__ "\n at Line: " + __LINE__);

		std::cerr << msg;
		throw std::runtime_error(msg);
	}
	if (bDelete_vectors)
		return delete_vectors(M_VecCows, M_VecCols, M_iiVecPair);
}

template <typename Type>
inline void
Matrix_T<Type>::Fill(const size_t Rows, const size_t Cols, vec<Type> &vec1,
					 vec<Type> &vec2, bool bDelete_vectors) {

	M_iRows = Rows;
	M_iCols = Cols;

	fillVectors(M_VecCows, Rows, M_VecCols, Cols);

	const size_t size = M_VecCows.size() + M_VecCols.size();

	M_iiVecPair = std::make_pair(vec1, vec2);
	M_iiVecPair.reserve(size);
	M_iiVecPair.push_back(M_iiVecPair);

	M_Matrix->reserve(size);
	M_Matrix->push_back(M_iiVecPair.back());

	if (M_Matrix == nullptr) {

		const str &msg = str(
			"Error: Matrix is null." __FUNCTION__ "\n at Line: " + __LINE__);

		std::cerr << msg;
		throw std::runtime_error(msg);
	}
	if (bDelete_vectors)
		return delete_vectors(M_VecCows, M_VecCols, M_iiVecPair);
}

template <typename Type>
inline void Matrix_T<Type>::Fill(bool bDelete_vectors) {

	if (M_Rand) *M_Rand = M_Rand->GetRandomAny<Type>();
	else {

		const str &msg = str("Error: Random number generator is "
							 "null. " __FUNCTION__ "\n at Line: " +
							 __LINE__);

		std::cerr << msg;
		throw std::runtime_error(msg);
	}

	fillVectors(M_VecCows, M_iRows, M_VecCols, M_iCols);

	const size_t size = M_VecCows.size() + M_VecCols.size();

	M_iiVecPair = std::make_pair(M_VecCows, M_VecCols);
	M_iiVecPair.reserve(size);
	M_iiVecPair.push_back(M_iiVecPair);

	M_Matrix->reserve(size);
	M_Matrix->push_back(M_iiVecPair.back());

	// undone CheckPtr(M_Matrix);

	if (bDelete_vectors)
		return delete_vectors(M_VecCows, M_VecCols, M_iiVecPair);
}

template <typename Type>
inline void Matrix_T<Type>::GetMatrix() {

	if (M_Matrix == nullptr) {

		const str &msg = str(
			"Error: Matrix is null. " __FUNCTION__ "\n at Line: " + __LINE__);

		std::cerr << msg;
		throw std::runtime_error(msg);
	}
}

template <typename Type>
void Matrix_T<Type>::fillVectors(vec<Type> &vec1, const size_t VecSize1,
								 vec<Type> &vec2, const size_t VecSize2) {

	vec1.reserve(VecSize1);
	vec2.reserve(VecSize2);

	UptrRand rand = Random().GetrdUptr();

	auto FillVec1 = [&VecSize1, &vec1, &rand]() -> void {
		for (size_t i = 0; i < VecSize1; ++i) {

			if (rand)
				vec1.push_back(rand->GetRandomAny<Type>(numCap<Type>::max()));
			else {
				const str &msg = str("Error: Random number generator is "
									 "null." __FUNCTION__ "\n at Line: " +
									 __LINE__);

				std::cerr << msg;
				throw std::runtime_error(msg);
			}
		}
	};

	auto FiilVec2 = [&VecSize2, &vec2, &rand]() -> void {
		for (size_t i = 0; i < VecSize2; ++i) {

			if (rand)
				vec2.push_back(rand->GetRandomAny<Type>(numCap<Type>::max()));
			else {
				const str &msg = str("Error: Random number generator is "
									 "null." __FUNCTION__ "\n at Line: " +
									 __LINE__);

				std::cerr << msg;
				throw std::runtime_error(msg);
			}
		}
	};

	std::thread t1(FillVec1);
	std::thread t2(FiilVec2);

	t1.join();
	t2.join();

	rand.reset();
	rand = nullptr;
}

template <typename Type>
void Matrix_T<Type>::fillVectors(vec<Type> &vec1, const size_t VecSize1,
								 const size_t vec1Min, const size_t vec1Max,
								 vec<Type> &vec2, const size_t VecSize2,
								 const size_t vec2Min, const size_t vec2Max) {

	vec1.reserve(VecSize1);
	vec2.reserve(VecSize2);

	UptrRand rand = Random().GetrdUptr();

	// Todo:

	auto FillVec1 = [&VecSize1, &vec1, &rand, &vec1Min, &vec1Max]() -> void {
		for (size_t i = 0; i < VecSize1; ++i) {

			if (rand)
				vec1.push_back(rand->GetRandomAny<Type>(vec1Min, vec1Max));
			else {

				const str &msg = str("Error: Random number generator is "
									 "null." __FUNCTION__ "\n at Line: " +
									 __LINE__);

				std::cerr << msg;
				throw std::runtime_error(msg);
			}
		}
	};

	auto FiilVec2 = [&VecSize2, &vec2, &rand, &vec2Min, &vec2Max]() -> void {
		for (size_t i = 0; i < VecSize2; ++i) {

			if (rand)
				vec2.push_back(rand->GetRandomAny<Type>(vec2Min, vec2Max));
			else {
				const str &msg = str("Error: Random number generator is "
									 "null." __FUNCTION__ "\n at Line: " +
									 __LINE__);

				std::cerr << msg;
				throw std::runtime_error(msg);
			}
		}
	};

	std::thread t1(FillVec1);
	std::thread t2(FiilVec2);

	t1.join();
	t2.join();

	rand.reset();
	rand = nullptr;
}

template <typename Type>
inline void
Matrix_T<Type>::fillVectors(vec<Type> &vec1, const size_t VecSize1,
							const float vec1Min, const float vec1Max,
							vec<Type> &vec2, const size_t VecSize2,
							const float vec2Min, const float vec2Max) {

	vec1.reserve(VecSize1);
	vec2.reserve(VecSize2);

	UptrRand rand = Random().GetrdUptr();

	auto FillVec1 = [&VecSize1, &vec1, &rand, &vec1Min, &vec1Max]() -> void {
		for (size_t i = 0; i < VecSize1; ++i)
			vec1.push_back(rand->GetRandomAny<Type>(vec1Min, vec1Max));
	};

	auto FiilVec2 = [&VecSize2, &vec2, &rand, &vec2Min, &vec2Max]() -> void {
		for (size_t i = 0; i < VecSize2; ++i)
			vec2.push_back(rand->GetRandomAny<Type>(vec2Min, vec2Max));
	};

	std::thread t1(FillVec1);
	std::thread t2(FiilVec2);

	t1.join();
	t2.join();

	rand.reset();
	rand = nullptr;
}

template <typename Type>
inline void Matrix_T<Type>::printMatrix() {

	if (M_Matrix == nullptr) {

		const str &msg = str(
			"Error: Matrix is null." __FUNCTION__ "\n at Line: " + __LINE__);

		std::cerr << msg;
		throw std::runtime_error(msg);
	}

	auto &vec1		= M_Matrix->front().first;
	auto &vec2		= M_Matrix->front().second;
	auto  it1_begin = vec1.begin();
	auto  it1_end	= vec1.end();
	auto  it2_begin = vec2.begin();
	auto  it2_end	= vec2.end();

	if (it1_begin._Ptr == nullptr ||
		it1_end._Ptr == nullptr ||
		it2_begin._Ptr == nullptr ||
		it2_end._Ptr == nullptr) {

		const str &msg =
			str("Error: Iterator is null." __FUNCTION__ "at Line: " + __LINE__);

		std::cerr << msg;
		throw std::runtime_error(msg);
	}

	for (it1_begin; it1_begin != it1_end; ++it1_begin) {

		std::cout << *it1_begin << " ";

		for (auto it2 = vec2.begin(); it2 != vec2.end(); ++it2)
			std::cout << *it2 << " ";

		std::print("\n");
	}
}
