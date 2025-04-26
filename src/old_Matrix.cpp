
#include "Matrix.hpp"
#include "MyTypes.hpp"
#include "Random.hpp"
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

Matrix::Matrix() noexcept : m_iRows(), m_iCols(), m_vvData() {}

Matrix::Matrix(const size_t& Rows, const size_t& Cols) noexcept : Matrix() {

	m_iRows = Rows;
	m_iCols = Cols;
	m_vvData.resize(Rows, vec<int>(Cols, 0));

	
}

Matrix::Matrix(const Matrix &other) noexcept
  : m_iRows(other.m_iRows),
	m_iCols(other.m_iCols),
	m_vvData(other.m_vvData) {}

Matrix::Matrix(Matrix &&Matrix) noexcept {

	m_iRows	 = std::move(Matrix.m_iRows);
	m_iCols	 = std::move(Matrix.m_iCols);
	m_vvData = std::move(Matrix.m_vvData);
}

Matrix &Matrix::operator=(const Matrix &obj) noexcept {

	m_iRows			 = obj.m_iRows;
	m_iCols			 = obj.m_iCols;
	m_vvData		 = obj.m_vvData;

	return *this;
}

const Matrix &Matrix::operator=(const Matrix &obj) const noexcept {

	Matrix mtx;

	mtx.m_iRows = obj.m_iRows;
	mtx.m_iCols	= obj.m_iCols;
	mtx.m_vvData = obj.m_vvData;

	return mtx;

}

/*
Matrix::Matrix(const size_t &iRows, const size_t &iCols, const vec<ld> &vRows,
			   const vec<ld> &Vcols, const vLdPar &vPar_RowsCols,
			   const vPar &vPar_Matrix, const vParPtr &vParPtr_Matrix) noexcept
  : m_iRows(iRows),
	m_iCols(iCols),
	m_vRows(vRows),
	m_vCols(Vcols),
	m_vPar_RowsCols(vPar_RowsCols),
	m_vPar_Matrix(vPar_Matrix),
	m_vParPtr_Matrix(vParPtr_Matrix) {}
	


Matrix &Matrix::operator=(const Matrix &obj) noexcept {

	m_iRows			 = obj.m_iRows;
	m_iCols			 = obj.m_iCols;
	m_vRows			 = obj.m_vRows;
	m_vCols			 = obj.m_vCols;
	m_vPar_RowsCols	 = obj.m_vPar_RowsCols;
	m_vPar_Matrix	 = obj.m_vPar_Matrix;
	m_vParPtr_Matrix = obj.m_vParPtr_Matrix;

	return *this;
}



const Matrix &Matrix::operator=(const Matrix &obj) const noexcept {

	Matrix mtx;

	mtx.m_iRows			 = obj.m_iRows;
	mtx.m_iCols			 = obj.m_iCols;
	mtx.m_vRows			 = obj.m_vRows;
	mtx.m_vCols			 = obj.m_vCols;
	mtx.m_vPar_RowsCols	 = obj.m_vPar_RowsCols;
	mtx.m_vPar_Matrix	 = obj.m_vPar_Matrix;
	mtx.m_vParPtr_Matrix = obj.m_vParPtr_Matrix;

	return mtx;
}
*/