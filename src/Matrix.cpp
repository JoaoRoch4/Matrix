#include "Matrix.hpp"
#include "MyTypes.hpp"
#include "Random.hpp"
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

Matrix::Matrix() noexcept
  : m_iRows(1),
	m_iCols(1),
	m_vRows({m_iRows}),
	m_Vcols({m_iCols}),
	m_vPar_RowsCols({std::make_pair(std::move(std::ref(m_vRows)),
									std::move(std::ref(m_Vcols)))}),
	m_vPar_Matrix({m_vPar_RowsCols}),
	m_vParPtr_Matrix(mk_unq<vPar>()) {}

Matrix::Matrix(const size_t &Rows, const size_t &Cols) noexcept
  : m_iRows(Rows),
	m_iCols(Cols),
	m_vRows({m_iRows}),
	m_Vcols({m_iCols}),
	m_vPar_RowsCols({std::make_pair(std::move(std::ref(m_vRows)),
									std::move(std::ref(m_Vcols)))}),
	m_vPar_Matrix({m_vPar_RowsCols}),
	m_vParPtr_Matrix(mk_unq<vPar>()) {}

Matrix::Matrix(const size_t &iRows, const size_t &iCols, const vec<ld> &vRows,
			   const vec<ld> &Vcols, const vLdPar &vPar_RowsCols,
			   const vPar &vPar_Matrix, const vParPtr &vParPtr_Matrix) noexcept
  : m_iRows(iRows),
	m_iCols(iCols),
	m_vRows(vRows),
	m_Vcols(Vcols),
	m_vPar_RowsCols(vPar_RowsCols),
	m_vPar_Matrix(vPar_Matrix),
	m_vParPtr_Matrix(vParPtr_Matrix) {}
