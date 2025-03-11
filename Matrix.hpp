#pragma once

#include "MyTypes.hpp"
#include "Random.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#define CheckPtr(Ptr)                                              \
	if (Ptr == nullptr) {                                          \
		const str &__msg("Error:" #Ptr                             \
						 "is null. " __FUNCTION__ "\n at Line: " + \
						 ##__LINE__);                              \
		std::cerr << __msg;                                        \
		throw std::runtime_error(__msg.c_str());                   \
	}

class MatrixVec;

class Matrix {

	friend MatrixVec;

	using vPar	  = vec<PAR<vec<ld>, vec<ld>>>;
	using vParPtr = sptr<vec<PAR<vec<ld>, vec<ld>>>>;
	using vLdPar  = PAR<vec<ld>, vec<ld>>;

protected:
	size_t	m_iRows;
	size_t	m_iCols;
	vec<ld> m_vRows;
	vec<ld> m_Vcols;
	vLdPar	m_vPar_RowsCols;
	vPar	m_vPar_Matrix;
	vParPtr m_vParPtr_Matrix;

public:
	// Default constructor
	Matrix() noexcept;

	// Parameter constructor
	Matrix(const size_t &Rows, const size_t &Cols) noexcept;

	Matrix(const size_t &m_iRows, const size_t &m_iCols, const vec<ld> &m_vRows,
		   const vec<ld> &m_Vcols, const vLdPar &m_vPar_RowsCols,
		   const vPar &m_vPar_Matrix, const vParPtr &m_vParPtr_Matrix) noexcept;

	Matrix(const Matrix &Matrix) noexcept = default;

	Matrix(Matrix &&Matrix) noexcept = default;

	// getters
	INLN size_t GetRows() CnExcpt { return m_iRows; }
	INLN size_t		 GetCols() CnExcpt { return m_iCols; }
	INLN vec<ld> GetM_vRows() CnExcpt { return m_vRows; }
	INLN vec<ld>	  GetM_vCols() CnExcpt { return m_Vcols; }
	INLN vLdPar		  GetM_vPar_RowsCols() CnExcpt { return m_vPar_RowsCols; }
	INLN vPar		  GetM_vPar_Matrix() CnExcpt { return m_vPar_Matrix; }
	INLN vParPtr	  GetM_vParPtr_Matrix() CnExcpt { return m_vParPtr_Matrix; }

	// Setters
	INLN void SetGetRows(const size_t &iRows) noexcept { m_iRows = iRows; }
	INLN void	   SetCols(const size_t &iCols) noexcept { m_iCols = iCols; }
	INLN void SetM_vRows(const vec<ld> &vRows) noexcept {
		m_vRows = vRows;
	}
	INLN void SetM_vCols(const vec<ld> &vCols) noexcept {
		m_Vcols = vCols;
	}
	INLN void SetM_vPar_RowsCols(const vLdPar &RowsCols) noexcept {
		m_vPar_RowsCols = RowsCols;
	}
	INLN void SetM_vPar_Matrix(const vPar &vPar_Matrix) noexcept {
		m_vPar_Matrix = vPar_Matrix;
	}
	INLN void SetM_vParPtr_Matrix(const vParPtr &vParPtr_Matrix) noexcept {
		m_vParPtr_Matrix = vParPtr_Matrix;
	}

	
};

template <typename Type>
class Matrix_T {

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

	void Start();

	// Copy constructor
	Matrix_T(const Matrix_T &other, const bool bDelete_vectors = false);

	// full constructor
	Matrix_T(const bool bFill, const bool bDelete_vectors = false);

	// Constructor with Rows and Cols parameters
	Matrix_T(const int Rows, const int Cols, bool bDelete_vectors = false);

	// Constructor with Rows and Cols parameters also vectors
	Matrix_T(const size_t Rows, const size_t Cols, vec<Type> &Vec1,
			 vec<Type> &Vec2);

	void Fill(bool bDelete_vectors = true);

	void Fill(const Type Rows, const Type Cols, bool bDelete_vectors = true);

	void Fill(const size_t Rows, const size_t Cols, vec<Type> &vec1,
			  vec<Type> &vec2, bool bDelete_vectors = true);

	template <typename... Vectors>
	__forceinline void delete_vectors(Vectors &...vecs) {
		(vecs.clear(), ...);
		(vecs.shrink_to_fit(), ...);
	}

	__forceinline void SetRows(const Type &Rows) noexcept { M_iRows = Rows; }
	__forceinline Type GetRows() const noexcept { return M_iRows; }

	__forceinline void SetCols(const Type &Cols) noexcept { M_iCols = Cols; }
	__forceinline Type GetCols() const noexcept { return M_iCols; }

	__forceinline void SetVrows(const vec<Type> &vec) noexcept {
		M_VecCows = vec;
	}
	__forceinline vec<Type> GetVrows() const noexcept { return M_VecCows; }

	__forceinline void SetMatrix(const Matrix2d &matrix) {
		*M_Matrix = *matrix;
	}

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
	CheckPtr(M_Matrix);
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

	CheckPtr(M_Matrix.get());

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

	auto FillVec1 = [&VecSize1, &vec1, &rand, &func]() -> void {
		for (size_t i = 0; i < VecSize1; ++i) {

			if (rand)
				vec1.push_back(rand->GetRandomAny<Type>(numCap<Type>::max()));
			else {
				const str &msg = str("Error: Random number generator is "
									 "null." func __FUNCTION__ "\n at Line: " +
									 __LINE__);

				std::cerr << msg;
				throw std::runtime_error(msg);
			}
		}
	};

	auto FiilVec2 = [&VecSize2, &vec2, &rand, &func]() -> void {
		for (size_t i = 0; i < VecSize2; ++i) {

			if (rand)
				vec2.push_back(rand->GetRandomAny<Type>(numCap<Type>::max()));
			else {
				const str &msg = str("Error: Random number generator is "
									 "null." func __FUNCTION__ "\n at Line: " +
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

	auto FillVec1 = [&VecSize1, &vec1, &rand, &vec1Min, &vec1Max,
					 &func]() -> void {
		for (size_t i = 0; i < VecSize1; ++i) {

			if (rand)
				vec1.push_back(rand->GetRandomAny<Type>(vec1Min, vec1Max));
			else {

				const str &msg = str("Error: Random number generator is "
									 "null."  __FUNCTION__ "\n at Line: " +
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
									 "null." func __FUNCTION__ "\n at Line: " +
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

	if (it1_begin._Ptr == nullptr || it1_end._Ptr == nullptr ||
		it2_begin._Ptr == nullptr || it2_end._Ptr == nullptr) {

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