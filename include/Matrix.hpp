#pragma once

#include <array> // For std::array (used for fixed-size matrix storage)
#include <initializer_list> // For initializer_list (used for matrix initialization)
#include <iosfwd> // For forward declaration of std::ostream (used for printing)
#include <iostream>	   // For std::cout and printing
#include <memory>	   // For std::unique_ptr and std::shared_ptr
#include <sstream>	   // **Added this for std::ostringstream**
#include <stdexcept>   // Not used here but commonly useful for exceptions
#include <string>	   // For std::string (not used here but commonly useful)
#include <type_traits> // For std::is_arithmetic (used for type checking)
#include <utility>	   // For std::move (used for move constructor)

// Proxy that either prints on destruction or returns a string representation
template <size_t Rows, size_t Cols, typename T = long long>
class PrinterProxy {

private:

	// Reference to the matrix data
	const std::array<std::array<T, Cols>, Rows> &m_data;

	// True if str() was called
	mutable bool m_consumed;

	// Cached string representation
	mutable std::string m_str;

protected:

	// Lazily build the string representation
	std::string buildString() const {

		std::ostringstream oss;

		for (const auto &row : m_data) {

			for (auto &val : row) oss << val << ' ';
			oss << '\n';
		}
		return oss.str();
	}

public:

	// Construct the proxy and leave m_consumed false.
	PrinterProxy(const std::array<std::array<T, Cols>, Rows> &data)
	  : m_data(data), m_consumed(false) {
		static_assert(Rows > 0 && Cols > 0,
					  "Matrix must have at least one row and one column.");
	}

	// Calling str() returns the string and marks it as consumed so that
	// the destructor will not print anything.
	std::string str() const {

		if (m_str.empty()) m_str = buildString();

		m_consumed = true;

		return m_str;
	}

	// In the destructor, if str() was not called, print the representation.
	~PrinterProxy() {

		if (!m_consumed) {

			if (m_str.empty()) m_str = buildString();
			std::cout << m_str;
		}
	}

private:

	// Disable copy to avoid double printing
	PrinterProxy(const PrinterProxy &)			  = delete;
	PrinterProxy &operator=(const PrinterProxy &) = delete;
};

/**
 * @brief A class representing a matrix of fixed size.
 */
template <size_t Rows, size_t Cols, typename T = long long>
class Matrix {

private:

	static_assert(std::is_arithmetic_v<T>, "T is not arithmetic.");
	static_assert(Rows >= 0, "Rows must be greater than 0.");
	static_assert(Cols >= 0, "Cols must be greater than 0.");

public:

	// 2D array to store matrix elements
	std::array<std::array<T, Cols>, Rows> data;

	// Default constructor
	Matrix() : data() {};

	Matrix(const std::array<std::array<T, Cols>, Rows> &data) : data(data) {}

	// Copy constructor
	Matrix(const Matrix<Rows, Cols, T> &other) : data(other.data) {}

	Matrix(const Matrix<Rows, Cols, T> *other) {

		// Check if the pointer is not null
		if (other != nullptr) {
			// Copy data from the other matrix
			data = other->data;
		}
	}

	template <typename U = const Matrix<Rows, Cols, T>>
	Matrix(const std::unique_ptr<U> &other) {
		// Check if the pointer is not null
		if (other != nullptr) {
			// Copy data from the other matrix
			data = other->data;
		}
	}

	Matrix(const std::unique_ptr<
		   const std::initializer_list<std::initializer_list<T>>> &other) {
		// Check if the pointer is not null
		if (other != nullptr) {
			// Copy data from the other matrix
			data = Iter(*other);
		}
	}

	Matrix(std::shared_ptr<const Matrix<Rows, Cols, T>> other) {
		// Check if the pointer is not null
		if (other != nullptr) {
			// Copy data from the other matrix
			data = other->data;
		}
	}

	// Move constructor
	Matrix(Matrix<Rows, Cols, T> &&other) noexcept
	  : data(std::move(other.data)) {}

	Matrix(const std::unique_ptr<Matrix<Rows, Cols, T>> &&other) noexcept
	  : data(std::move(other->data)) {
		// data = Iter(std::ref(*other));
	}

	// Constructor that allows matrix initialization with nested initializer lists
	Matrix(const std::initializer_list<std::initializer_list<T>> &initRef) noexcept
	  : Matrix() {
		data = Iter(initRef);
	}

	// Constructor
	Matrix(const std::initializer_list<std::initializer_list<T>> &&initRef) noexcept
	  : Matrix() {
		data = std::move(Iter(initRef));
	}

	// Constructor that allows matrix initialization with nested initializer lists
	Matrix(const std::initializer_list<std::initializer_list<T>> *initPtr) noexcept
	  : Matrix() {
		data = Iter(*initPtr);
	}

	std::array<std::array<T, Cols>, Rows>
	Iter(const std::initializer_list<std::initializer_list<T>> &init) const {

		// Row index
		size_t r		 = 0;
		std::array<std::array<T, Cols>, Rows> localData = data;

		// Iterate through each row of the initializer list
		for (const std::initializer_list<T> &row : init) {

			// Column index
			size_t c = 0;

			// Iterate through each value in the row
			for (const T val : row) {

				// Assign value to matrix position
				localData[r][c++] = val;
			}
			++r;
		}

		return localData;
	}

	std::array<std::array<T, Cols>, Rows>
	Iter(const std::initializer_list<std::initializer_list<T>> &&init) const {

		const std::initializer_list<std::initializer_list<T>> localInit =
			std::move(init);
		return Iter(localInit);
	}
		
	std::array<std::array<T, Cols>, Rows> getData() const { return data; }

	void setData(const std::array<std::array<T, Cols>, Rows> &data) {
		this->data = data;
	}

	void setData(const std::initializer_list<std::initializer_list<T>> &Data) {
		data = Iter(Data);
	}

	const char *getType() const {
		// Return the type of the matrix
		if constexpr (std::is_same_v<T, long long>) return "long long";
		else if constexpr (std::is_same_v<T, long>) return "long";
		else if constexpr (std::is_same_v<T, short>) return "short";
		else if constexpr (std::is_same_v<T, unsigned long long>)
			return "unsigned long long";
		else if constexpr (std::is_same_v<T, unsigned long>)
			return "unsigned long";
		else if constexpr (std::is_same_v<T, unsigned short>)
			return "unsigned short";
		else if constexpr (std::is_same_v<T, unsigned int>)
			return "unsigned int";
		else if constexpr (std::is_same_v<T, unsigned char>)
			return "unsigned char";
		else if constexpr (std::is_same_v<T, signed char>) return "signed char";
		else if constexpr (std::is_same_v<T, wchar_t>) return "wchar_t";
		else if constexpr (std::is_same_v<T, int>) return "int";
		else if constexpr (std::is_same_v<T, float>) return "float";
		else if constexpr (std::is_same_v<T, double>) return "double";
		else if constexpr (std::is_same_v<T, long double>) return "long double";
		else if constexpr (std::is_same_v<T, char>) return "char";
		else if constexpr (std::is_same_v<T, bool>) return "bool";
		else return "unknown type";
	}

	/**
	 * @brief Adds two matrices together with *this and the argument matrix.
	 * @param other The matrix to be added to *this matrix.
	 * @return A new matrix that is the sum of *this and the argument matrix.
	 */
	template <size_t R, size_t C>
	Matrix<Rows, Cols, T> Add(const Matrix<R, C, T> &other) const {

		// Static assertion fails at compile time if template is empty
		static_assert(R >= 0, "Matrix R element is empty!");
		static_assert(C >= 0, "Matrix C element is empty!");

		// Static assertion ensures that sizes match
		static_assert(R == Rows && C == Cols,
					  "Matrices must have the same dimensions to be added.");

		// Result matrix
		Matrix<Rows, Cols, T> result;

		// Perform element-wise addition
		for (size_t i = 0; i < Rows; ++i) {
			for (size_t j = 0; j < Cols; ++j) {
				result.data[i][j] = this->data[i][j] + other.data[i][j];
			}
		}

		// Return resulting matrix
		return result;
	}

	/**
	 * @brief Adds two matrices together passed as arguments.
	 * @param mtx1 first matrix to be added.
	 * @param mtx2 second matrix to be added.
	 * @return A new matrix that is the sum of the two matrices.
	 */
	template <size_t R1, size_t C1, size_t R2, size_t C2>
	Matrix<Rows, Cols, T>
	Add(const Matrix<R1, C1, T> &mtx1, const Matrix<R2, C2, T> &mtx2) const {

		static_assert(R1 >= 0, "Matrix1 R1 element is empty!");
		static_assert(R2 >= 0, "Matrix2 R2 element is empty!");
		static_assert(C1 >= 0, "Matrix1 C1 element is empty!");
		static_assert(C2 >= 0, "Matrix2 C2 element is empty!");

		// Static assertion fails at compile time if sizes don't match
		static_assert(R1 == Rows && C1 == Cols,
					  "Matrix1 must have the same dimensions to be added.");
		static_assert(R2 == Rows && C2 == Cols,
					  "Matrix2 must have the same dimensions to be "
					  "added.");

		// Result matrix
		Matrix<Rows, Cols, T> result;

		// Perform element-wise addition
		for (size_t i = 0; i < Rows; ++i)

			// Iterate through each column
			for (size_t j = 0; j < Cols; ++j)

				// Add corresponding elements
				result.data[i][j] = mtx1.data[i][j] + mtx2.data[i][j];

		const Matrix<Rows, Cols, T> CResult = result;

		// Return resulting matrix
		return CResult;
	}

	// Conversion operator to allow conversion between different types of Matrix
	template <typename U>
	operator Matrix<Rows, Cols, U>() {

		static_assert(std::is_arithmetic_v<U>, "U is not arithmetic.");

		// Create a new matrix of the desired type
		Matrix<Rows, Cols, U> result;

		// Iterate through each element of the matrix
		for (size_t i = 0; i < Rows; ++i) {

			// Iterate through each column
			for (size_t j = 0; j < Cols; ++j) {

				// Convert and assign the value to the new matrix
				result.data[i][j] = static_cast<U>(data[i][j]);
			}
		}
		return result;
	}

	// Prints the matrix to the console
	PrinterProxy<Rows, Cols, T> print() const {
		return PrinterProxy<Rows, Cols, T>(data);
	}

	/**
	 * @brief Returns a reference to the matrix.
	 * @return A reference to the matrix.
	 */
	Matrix &Ref() const {
		// Create a new matrix object
		Matrix *matrix {};
		// Assign the current matrix data to the new matrix
		matrix->data = data;
		// Return the new matrix
		return *matrix;
	}

	/**
	 * @brief Returns a pointer to the matrix.
	 * @return A pointer to the matrix.
	 */
	Matrix *Ptr() const {
		// Create a new matrix object
		Matrix *matrix {};
		// Assign the current matrix data to the new matrix
		matrix->data = data;
		// Return the new matrix
		return matrix;
	}

	// Overloaded output operator for printing the matrix
	friend std::ostream &
	operator<<(std::ostream &os, const Matrix<Rows, Cols, T> &matrix) {

		os << PrinterProxy<Rows, Cols, T>(matrix.data).str();
		return os;
	}

	/**
	 * @brief Returns a pointer to the matrix using the dereference operator.
	 * @return A pointer to the matrix.
	 */
	inline Matrix *operator*() { return Ptr(); }

	/**
	 * @brief Returns a const pointer to the matrix using the dereference
	 * operator.
	 * @return A const pointer to the matrix.
	 */
	inline const Matrix *operator*() const { return Ptr(); }

	/**
	 * @brief Returns a pointer to the matrix using the arrow operator.
	 * @return A pointer to the matrix.
	 */
	Matrix *operator->() const { return Ptr(); }

	// Overloaded addition operator	
	Matrix operator+(const Matrix &other1) const {
			
		// Result matrix
		 

		// Return resulting matrix
		return Add(other1);
		
	}

	Matrix &operator=(Matrix<Rows, Cols, T> &other) {
		// Check for self-assignment
		if (this != &other) {
			// Copy data from the other matrix
			data = other.data;
		}
		return *this;
	}

	Matrix &operator+=(const Matrix<Rows, Cols, T> &other) {
		// Check for self-assignment
		if (this != &other) {
			// Add data from the other matrix
			data = other.data;
		}
		return *this;
	}

	// Overloaded addition assignment operator
	// Ensures at compile-time that matrix dimensions match.
	// This operator modifies the current matrix by adding another matrix to it.
	template <size_t R, size_t C>
	Matrix<Rows, Cols, T> &operator+=(const Matrix<R, C, T> &other) {
		// Static assertion to ensure matrix dimensions match
		static_assert(R == Rows && C == Cols,
					  "Matrices must have the same dimensions to be added.");
		static_assert(R > 0 && C > 0,
					  "Matrix must have at least one row and one column.");

		// Perform addition and assign the result to this matrix
		*this = Add(other);
		return *this;
	}

	Matrix<Rows, Cols, T> operator[](const size_t &i) {

		// Check if the index is within bounds
		if (i >= Rows) throw std::out_of_range("Index out of range.");

		auto localData = data;
		localData[i]   = data[i];

		Matrix<Rows, Cols, T> &result = *this;
		result.setData(localData);

		// Return the row at index i
		return result;
	}

	std::array<std::array<T, Cols>, Rows> operator[](const size_t i) const {
		// Check if the index is within bounds
		if (i >= Rows) throw std::out_of_range("Index out of range.");
		auto localData = data;
		localData[i]   = data[i];
		// Return the row at index i
		return localData;
	}

	bool operator==(const Matrix &other) const = default;

	
};

/**
 * @brief A specialization of the Matrix class for a 1x1 matrix.
 */
template <typename j>
class Matrix<1, 1, j> {

private:

	const static size_t Rows = 1;
	const static size_t Cols = 1;

	friend class Matrix<Rows, Cols, j>;

	static_assert(std::is_arithmetic_v<j>, "T is not arithmetic.");

public:

	// Constructor for 1x1 matrix

	// 1D array to store matrix elements
	std::array<j, Cols> data;

	// Default constructor
	Matrix() : data() {};

	// Copy constructor
	Matrix(const Matrix<Rows, Cols, j> &other) : data(other.data) {}

	// Move constructor
	Matrix(Matrix<Rows, Cols, j> &&other) noexcept
	  : data(std::move(other.data)) {}

	std::array<std::array<j, Cols>, Rows> getData() const { return data; }

	void setData(const std::array<std::array<j, Cols>, Rows> &data) {
		this->data = data;
	}

	// Constructor that allows matrix initialization with nested initializer
	// lists
	Matrix(std::initializer_list<std::initializer_list<j>> init) : Matrix() {

		// Row index
		size_t r = 0;

		// Iterate through each row of the initializer list
		for (auto &row : init) { data[r] = ++r; }
	}
};
