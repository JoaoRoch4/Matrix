#include <Colors.hpp>
#include <iostream>
#include <print>

int main() {

	My::Colors c1;
	My::Colors *c2 = new My::Colors;
	My::Colors	*c3(c2);

	bool bCheckBgExists	 = c1.bCheckBgExists("on_red");
	bool bCheckBgExists1 = c1.bCheckBgExists("on_purple");

	bool bCheckBgExists2 = c1.bCheckBgExists(My::BackgroundColorEnum::on_blue);
	bool bCheckBgExists3 = c1.bCheckBgExists(My::BackgroundColorEnum(555));
	bool bCheckBgExists4 = c1.bCheckBgExists(My::BackgroundColorEnum::none);
	bool bCheckBgExists5 = c1.bCheckBgExists("");
	bool bCheckBgExists6 = c1.bCheckBgExists("blablabla");

	std::cout << "bCheckBgExists: " << bCheckBgExists << '\n';
	std::cout << "bCheckBgExists1: " << bCheckBgExists1 << '\n';
	std::cout << "bCheckBgExists2: " << bCheckBgExists2 << '\n';
	std::cout << "bCheckBgExists3: " << bCheckBgExists3 << '\n';
	std::cout << "bCheckBgExists4: " << bCheckBgExists4 << '\n';
	std::cout << "bCheckBgExists5: " << bCheckBgExists5 << '\n';
	std::cout << "bCheckBgExists6: " << bCheckBgExists6 << '\n';

	delete c2;

	std::cin.get();
	return 0;
}
