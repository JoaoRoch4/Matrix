#include <iostream>

#include "Error.hpp"
#include "Matrix.hpp"
#include "termcolor.hpp"

int main() {

	Matrix<2, 2> A =   {{1, 2}, 
						{3, 4}};

	Matrix<2, 2, int> AInt = A;

	Matrix<2, 2> B = {{5, 6}, {7, 8}};

	Matrix<2, 2, int> C = A + B;

	Matrix<2, 2, float> DFloat {{1.5f, 2.3f}, {3.4f, 4.1f}};
	Matrix<2, 2, int>	DInt = DFloat;
	Matrix<2, 2, double> DDouble = DFloat;

	std::cout << "\n DDouble.print() \n";
	DDouble.print();
	std::cout << "\n";

	std::cout << "Matrix<2, 2> C = A + B: \n" << C << '\n';
	std::cout << "Matrix<2, 2, float> DFloat: \n" << DFloat << '\n';
	std::cout << "Matrix<2, 2, int> DInt: \n" << DInt << '\n';
	std::cout << "Matrix<2, 2, double> DDouble: \n"
			  << "DDouble.print().str()\n" << DDouble.print().str() << '\n';

	return 0;
}
