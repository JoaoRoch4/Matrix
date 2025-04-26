#pragma once

#include "Matrix.hpp"
#include <iostream>
#include <istream>

using std::cout;
#define tpid(x) typeid(x).name()

int main() {

	Matrix matrix(3, 3);

	std::cout << "Matrix Rows: " << matrix.GetRows() << "\n"
			  << "Matrix Cols: " << matrix.GetCols() << "\n";

	Matrix matrix2 = matrix;

	

	Matrix matrix3(2, 2);
	matrix3 = matrix2;

	int	 cols = matrix3.GetCols<int>();
	long rows = matrix2.GetRows<long>();

	long double ldCols {matrix.GetCols<long double>()};
	long double ldRows {matrix.GetRows<long double>()};

	Matrix matrix4(10, 15);

	long long llCols = matrix4.GetCols();
	long long llRows = matrix4.GetCols();

	Matrix matrix5(12, 20);

	unsigned long long ullCols = matrix5.GetCols();
	unsigned long long ullRows = matrix5.GetRows();

	cout << "cols: " << cols << " cols type: " << tpid(cols) << '\n'
		 << "rows: " << rows << " rows type: " << tpid(rows) << '\n'
		 << "ldCols: " << ldCols << " ldCols type: " << tpid(ldCols) << '\n' 
		 << "ldRows: " << ldRows << " ldRows type: " << tpid(ldRows) << '\n' 
		 << "llCols: " << llCols << " llCols type: " << tpid(llCols) << '\n' 
		 << "llRows: " << llRows << " llRows type: " << tpid(llRows) << '\n' 
		 << "ullCols: " << ullCols << " ullCols type: " << tpid(ullCols) << '\n' 
		 << "ullRows: " << ullRows << " ullRows type: " << tpid(ullRows);

	std::cin.get();
	return 0;
}
