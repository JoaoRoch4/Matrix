#pragma once

#include <array> // For std::array (used for fixed-size matrix storage)
#include <initializer_list> // For initializer_list (used for matrix initialization)
#include <iosfwd> // For forward declaration of std::ostream (used for printing)
#include <iostream>	 // For std::cout and printing
#include <sstream>   // **Added this for std::ostringstream**
#include <stdexcept> // Not used here but commonly useful for exceptions
#include <string>	 // For std::string (not used here but commonly useful)

// Template class for a fixed-size matrix of integers
template <size_t Rows, size_t Cols, typename T = long long>
class Matrix {

private:

	// Proxy that either prints on destruction or returns a string representation
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

				for (auto& val : row) oss << val << ' ';
				oss << '\n';
			}
			return oss.str();
		}

	public:

		// Construct the proxy and leave m_consumed false.
		PrinterProxy(const std::array<std::array<T, Cols>, Rows> &data)
		  : m_data(data), m_consumed(false) {}

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

public:

	// 2D array to store matrix elements
	std::array<std::array<T, Cols>, Rows> data {};

	// Default constructor (zero-initialized matrix)
	Matrix() = default;

	// Constructor that allows matrix initialization with nested initializer lists
	Matrix(std::initializer_list<std::initializer_list<T>> init) {

		// Row index
		size_t r = 0;

		// Iterate through each row of the initializer list
		for (auto &row : init) {

			// Column index
			size_t c = 0;

			// Iterate through each value in the row
			for (auto &val : row) {

				// Assign value to matrix position
				data[r][c++] = val;
			}
			++r;
		}
	}

	// Overloaded addition operator
	// Ensures at compile-time that matrix dimensions match
	template <size_t R, size_t C>
	Matrix<Rows, Cols, T> operator+(const Matrix<R, C, T> &other) const {

		// Static assertion fails at compile time if sizes don't match
		static_assert(R == Rows && C == Cols,
					  "Matrices must have the same dimensions to be added.");

		// Result matrix
		Matrix<Rows, Cols, T> result;

		// Perform element-wise addition
		for (size_t i = 0; i < Rows; ++i)

			// Iterate through each column
			for (size_t j = 0; j < Cols; ++j)

				// Add corresponding elements
				result.data[i][j] = this->data[i][j] + other.data[i][j];

		// Return resulting matrix
		return result;
	}

	// Overloaded addition assignment operator
	// Ensures at compile-time that matrix dimensions match
	// This operator modifies the current matrix by adding another matrix to it
	template <size_t R, size_t C>
	Matrix<Rows, Cols, T> operator+=(const Matrix<R, C, T> &other) const {

		// Static assertion fails at compile time if sizes don't match
		static_assert(R == Rows && C == Cols,
					  "Matrices must have the same dimensions to be added.");

		for (size_t i = 0; i < Rows; ++i)
			for (size_t j = 0; j < Cols; ++j)
				// Add corresponding elements to this matrix
				this->data[i][j] = this->data[i][j] += other.data[i][j];
		return this;
	}

	// Conversion operator to allow conversion between different types of Matrix
	template <typename U>
	operator Matrix<Rows, Cols, U>() const {

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
	PrinterProxy print() const { return PrinterProxy(data); }

	// Overloaded output operator for printing the matrix
	friend std::ostream &
	operator<<(std::ostream &os, const Matrix<Rows, Cols, T> &matrix) {

		// Iterate through each row
		for (const auto &row : matrix.data) {

			// Iterate through each element in the row
			for (T val : row)

				// Print each element followed by a space
				os << val << ' ';

			// New line after each row
			os << '\n';
		}

		return os;
	}
};
