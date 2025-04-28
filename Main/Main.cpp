#include <iostream>
#include <memory>

#include "Error.hpp"
#include "Matrix.hpp"
#include "termcolor.hpp"

int main() {

	Matrix<2, 2> A =   {{1, 2}, 
						{3, 4}};

	Matrix<2, 2, int> AInt = A;

	Matrix<2, 2> B {{5, 6}, {7, 8}};

	Matrix<2, 2, int> C = A + B;

	Matrix<2, 2, long double> DLongDouble; 
	DLongDouble.setData({{1.55l, 2.301l}, {3.4001l, 4.1504l}});
	//Matrix<2, 2, int>	DInt = DFloat;
	//Matrix<2, 2, double> DDouble = DFloat;
	//Matrix<1, 1, long long> Empty{{2},{2}};
	Matrix<2, 2>		 Add;
	Add += Add.Add(A, B);

	std::cout << "DLongDouble.print();\n";
	DLongDouble.print();

	std::cout << "\n DLongDouble " << DLongDouble << '\n';

	std::cout << "DLongDouble.getType(); " << DLongDouble.getType() << '\n';
	
	

	std::unique_ptr<Matrix<2, 2, long>> pA =
		std::make_unique<Matrix<2, 2, long>>(Matrix<2, 2, long>{{5, 6}, {7, 8}});


	pA->print();

	std::cout << "Matrix<2, 2>Add;	Add = Add.Add(A, B)	" << Add << '\n';
	

	std::cout << "\n DDouble.print() \n";
	//DDouble.print();
	std::cout << "\n";

	std::cout << "Matrix<2, 2> C = A + B: \n" << C << '\n';
	//std::cout << "Matrix<2, 2, float> DFloat: \n" << DFloat << '\n';
	//std::cout << "Matrix<2, 2, int> DInt: \n" << DInt << '\n';
	//std::cout << "Matrix<2, 2, double> DDouble: \n"
			 // << "DDouble.print().str()\n" << DDouble.print().str() << '\n';

	return 0;
}
