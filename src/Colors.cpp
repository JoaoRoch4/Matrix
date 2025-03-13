#include "Colors.hpp"
#include "Error.hpp"
#include "MyTypes.hpp"
#include <cstdlib>
#include <intrin.h>
#include <iosfwd>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <termcolor.hpp>

namespace My {
Colors::Colors() noexcept
  : color(ColorEnum::none),
	backgroundColor(BackgroundColorEnum::none),
	isLocalized(false),
	ColorReturnStr(str()),
	BackgroundReturnStr(str()),
	buffer(0),
	InitializerCalled(false) {}

Colors::Colors(const Colors &c) noexcept {
	if (bISClassEmpty(c) && !InitializerCalled) Initializer();

	if (!bISClassEmpty(c)) {
		color				= bCheckColorExistsReturnColorEnum(c.color);
		backgroundColor		= enumBG_CheckBgColorExists(c.backgroundColor);
		isLocalized			= c.isLocalized;
		ColorReturnStr		= strCheckColorExists(c.ColorReturnStr);
		BackgroundReturnStr = strCheckBackgroundExists(c.BackgroundReturnStr);
	}
}

Colors::Colors(const Colors *ptr) noexcept {
	if (ptr == nullptr) {
		std::cout << termcolor::red << "pointer passed is a null pointer\n"
				  << termcolor::reset;
		Colors err = 1;
		if (ptr > &err) delete ptr;
		std::cin.get();
		std::exit(EXIT_FAILURE);
	}

	if (ptr != nullptr && bISClassEmpty(*ptr)) {
		std::cout << termcolor::red << "pointer passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
	}

	if (ptr != nullptr && !bISClassEmpty(*ptr)) {
		color			= bCheckColorExistsReturnColorEnum(ptr->color);
		backgroundColor = enumBG_CheckBgColorExists(ptr->backgroundColor);
		isLocalized		= ptr->isLocalized;
		ColorReturnStr	= strCheckColorExists(ptr->ColorReturnStr);
		BackgroundReturnStr =
			strCheckBackgroundExists(ptr->BackgroundReturnStr);
	}
}

Colors::Colors(const std::unique_ptr<Colors> &ptr) noexcept {
	if (ptr == nullptr) {
		std::cout << termcolor::red
				  << "unique_ptr pointer passed is a null pointer\n"
				  << termcolor::reset;
		std::cin.get();
		std::exit(EXIT_FAILURE);
	}

	if (ptr != nullptr && bISClassEmpty(*ptr)) {
		std::cout << termcolor::red << "unique_ptr pointer passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
	}

	if (ptr != nullptr || !bISClassEmpty()) {
		if (!InitializerCalled) Initializer();
		color			= bCheckColorExistsReturnColorEnum(ptr->color);
		backgroundColor = enumBG_CheckBgColorExists(ptr->backgroundColor);
		isLocalized		= ptr->isLocalized;
		ColorReturnStr	= strCheckColorExists(ptr->ColorReturnStr);
		BackgroundReturnStr =
			strCheckBackgroundExists(ptr->BackgroundReturnStr);
	}
}

Colors::Colors(const std::shared_ptr<Colors> &ptr) noexcept {
	if (ptr == nullptr) {
		std::cout << termcolor::red
				  << "shared_ptr pointer passed is a null pointer\n"
				  << termcolor::reset;
		ptr.~shared_ptr();
		std::cin.get();
		std::exit(EXIT_FAILURE);
	}

	if (ptr != nullptr && bISClassEmpty(*ptr)) {
		std::cout << termcolor::red << "shared_ptr pointer passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
	}

	if (ptr != nullptr || !bISClassEmpty()) {
		if (!InitializerCalled) Initializer();
		color			= bCheckColorExistsReturnColorEnum(ptr->color);
		backgroundColor = enumBG_CheckBgColorExists(ptr->backgroundColor);
		isLocalized		= ptr->isLocalized;
		ColorReturnStr	= strCheckColorExists(ptr->ColorReturnStr);
		BackgroundReturnStr =
			strCheckBackgroundExists(ptr->BackgroundReturnStr);
	}
}

Colors::Colors(const ColorEnum			 &color,
			   const BackgroundColorEnum &BackgroundColor) noexcept {
	const bool colorDoNotExists = (bCheckInvalidColor(color));
	const bool colorBackgroundDoNoExists =
		(bCheckInvalidColor(BackgroundColor));
	const bool bothDoNotExist = colorDoNotExists && colorBackgroundDoNoExists;

	if (colorDoNotExists && !colorBackgroundDoNoExists) {
		std::cout << termcolor::red << "Invalid ColorEnum passed\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
		this->backgroundColor = BackgroundColorEnum::none;
	}
	if (!colorDoNotExists && colorBackgroundDoNoExists) {
		std::cout << termcolor::red << "Invalid ColorEnum passed\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
		this->color = ColorEnum::none;
	}
	if (bothDoNotExist) {
		if (!InitializerCalled) Initializer();
		this->color			  = ColorEnum::none;
		this->backgroundColor = BackgroundColorEnum::none;
	}

	if (!bothDoNotExist) {
		if (!InitializerCalled) Initializer();
		this->color			  = ColorEnum::none;
		this->backgroundColor = BackgroundColorEnum::none;
	}
}

Colors::Colors(const str &ColorReturn, const str &BackgroundReturn) noexcept {
	const bool EmptyColorReturn		 = ColorReturn.empty();
	const bool EmptyBackgroundReturn = BackgroundReturn.empty();
	const bool Empty = EmptyColorReturn && EmptyBackgroundReturn;

	if (Empty) {
		std::cout << termcolor::red
				  << "ColorReturn and BackgroundReturn string passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();

		return;
	}
	if (EmptyColorReturn && !EmptyBackgroundReturn) {
		std::cout << termcolor::red << "ColorReturn string passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
		backgroundColor		= StringToBackgroundColorEnum(BackgroundReturn);
		BackgroundReturnStr = strCheckBackgroundExists(BackgroundReturn);
		return;
	}
	if (!EmptyColorReturn && EmptyBackgroundReturn) {
		std::cout << termcolor::red
				  << "BackgroundReturn string passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
		color		   = StringToColorEnum(ColorReturn);
		ColorReturnStr = strCheckColorExists(ColorReturn);
		return;
	}

	const bool colorDoNotExists = (bCheckColorExists(ColorReturn) == false);
	const bool colorBackgroundDoNoExists =
		(bCheckBackgroundExists(BackgroundReturn) == false);
	const bool bothDoNotExist = colorDoNotExists && colorBackgroundDoNoExists;

	if (bothDoNotExist) {
		std::cout
			<< termcolor::red
			<< "ColorReturn string passed does not correspond to any color\n"
			<< termcolor::reset;

		if (!InitializerCalled) Initializer();
		backgroundColor		= BackgroundColorEnum::none;
		BackgroundReturnStr = "none";
		return;
	}

	if (colorBackgroundDoNoExists && !colorDoNotExists) {
		std::cout << termcolor::red
				  << "BackgroundReturn string passed does not correspond to "
					 "any color\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
		color =
			bCheckColorExistsReturnColorEnum(StringToColorEnum(ColorReturn));
		ColorReturnStr = strCheckColorExists(ColorReturn);

		return;
	}

	if (!colorBackgroundDoNoExists && colorDoNotExists) {
		std::cout << termcolor::red
				  << "ColorReturn and BackgroundReturn string passed do not"
					 "correspond to any color\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();

		backgroundColor = enumBG_CheckBgColorExists(
			StringToBackgroundColorEnum(BackgroundReturn));
		BackgroundReturnStr = strCheckBackgroundExists(BackgroundReturn);
		return;
	}

	const bool NotOk =
		(EmptyColorReturn && EmptyBackgroundReturn && Empty &&
		 colorDoNotExists && colorBackgroundDoNoExists && bothDoNotExist);
	if (NotOk) {
		std::cout << termcolor::red << "An error has occurred at: " << __FILE__
				  << " line: " << __LINE__ << termcolor::reset << '\n';
		if (!InitializerCalled) Initializer();

		return;
	}

	if (!NotOk) {
		if (!InitializerCalled) Initializer();
		color =
			bCheckColorExistsReturnColorEnum(StringToColorEnum(ColorReturn));
		ColorReturnStr	= strCheckColorExists(ColorReturn);
		backgroundColor = enumBG_CheckBgColorExists(
			StringToBackgroundColorEnum(BackgroundReturn));
		BackgroundReturnStr = strCheckBackgroundExists(BackgroundReturn);
	}
}

const void Colors::SetClassColor(const ColorEnum &color) noexcept {
	this->color = color;
}

const void Colors::SetClassColor(const str &Txt) {
	if (Txt.empty() || bCheckColorExists(Txt) == false) {
		std::cout << termcolor::red;
		StaticError::Exit("Color does not exist.\n");
		std::cout << termcolor::reset;
		ColorReturnStr = "none";
		return;
	}
	ColorReturnStr = Txt;
}

const void Colors::SetClassBackgroundColor(
	const BackgroundColorEnum &BackgroundColor) {
	backgroundColor		= BackgroundColor;
	const str &result	= strEnumToStream(BackgroundColor);
	BackgroundReturnStr = result;
}

const void Colors::SetClassBackgroundColor(const str &BackgroundColor) {
	if (bCheckBackgroundExists(BackgroundColor)) {
		BackgroundReturnStr = "none";
	}
	BackgroundReturnStr = BackgroundColor;
}

const void Colors::SetLocale(const bool &locale) noexcept {
	if (locale == false || isLocalized == true) return;

	if (locale == true) {
		isLocalized = true;
		return;
	}
}

const ColorEnum &Colors::EnumGetColor() const noexcept { return color; }

const BackgroundColorEnum &Colors::EnumGetBackgroundColor() const noexcept {
	return this->backgroundColor;
}

const bool &Colors::bGetLocale() const { return this->isLocalized; }

const str &Colors::StrGetColor(const Colors &c) {

	if (bISClassEmpty(c) == true) {
		const str &err {str("Error: Class passed is empty.\n In Line: " +
							std::to_string(__LINE__) +
							"Func: " __FUNCTION__ "\n")};

		StaticError::Exit(err);
		return str();
	}
	return c.ColorReturnStr;
}

const str &Colors::StrGetColor() const noexcept { return this->ColorReturnStr; }

const str &Colors::StrGetBackgroundColor(const Colors &c) {
	if (bISClassEmpty(c) == true) {
		StaticError::Exit("Class passed is empty\n");
		constexpr const static char *none = "none";
		return none;
	}
	return c.ColorReturnStr;
}

const str &Colors::StrGetBackgroundColor() const noexcept {
	return this->BackgroundReturnStr;
}

const bool Colors::bHasColor(const ColorEnum &color) noexcept {
	if (color == ColorEnum::reset || color == ColorEnum::none) return false;
	return true;
}

const bool Colors::bHasColor(const BackgroundColorEnum &color) noexcept {
	if (color == BackgroundColorEnum::reset ||
		color == BackgroundColorEnum::none)
		return false;
	return true;
}

const bool Colors::bHasColor() const noexcept {
	if (this->color == ColorEnum::reset || this->color == ColorEnum::none)
		return false;
	return true;
}

const bool Colors::bHasBackgroundColor() const {
	const bool hasBackgroundColor {
		(this->backgroundColor == BackgroundColorEnum::reset ||
		 this->backgroundColor == BackgroundColorEnum::none)};

	if (hasBackgroundColor == false) return false;
	return true;
}

const bool Colors::bCheckInvalidColor(const ColorEnum &color) noexcept {
	switch (color) {
	case My::ColorEnum::none : return false;
	case My::ColorEnum::reset : return false;
	case My::ColorEnum::grey : return false;
	case My::ColorEnum::red : return false;
	case My::ColorEnum::green : return false;
	case My::ColorEnum::yellow : return false;
	case My::ColorEnum::blue : return false;
	case My::ColorEnum::magenta : return false;
	case My::ColorEnum::cyan : return false;
	case My::ColorEnum::white : return false;
	case My::ColorEnum::bright_grey : return false;
	case My::ColorEnum::bright_red : return false;
	case My::ColorEnum::bright_green : return false;
	case My::ColorEnum::bright_yellow : return false;
	case My::ColorEnum::bright_blue : return false;
	case My::ColorEnum::bright_magenta : return false;
	case My::ColorEnum::bright_cyan : return false;
	case My::ColorEnum::bright_white : return false;
	default : {
		std::cout << termcolor::red << "Invalid color passed\n"
				  << termcolor::reset;
		return true;
	}
	}
	const bool invalid {color < ColorEnum::bright_white};

	if (invalid) {
		std::cout << termcolor::red << "Invalid color passed\n"
				  << termcolor::reset;
		return true;
	}
}

const bool Colors::bCheckInvalidColor(
	const BackgroundColorEnum &color) noexcept {
	switch (color) {
	case My::BackgroundColorEnum::none : return false;
	case My::BackgroundColorEnum::reset : return false;
	case My::BackgroundColorEnum::on_grey : return false;
	case My::BackgroundColorEnum::on_red : return false;
	case My::BackgroundColorEnum::on_green : return false;
	case My::BackgroundColorEnum::on_yellow : return false;
	case My::BackgroundColorEnum::on_blue : return false;
	case My::BackgroundColorEnum::on_magenta : return false;
	case My::BackgroundColorEnum::on_cyan : return false;
	case My::BackgroundColorEnum::on_white : return false;
	case My::BackgroundColorEnum::on_bright_grey : return false;
	case My::BackgroundColorEnum::on_bright_red : return false;
	case My::BackgroundColorEnum::on_bright_green : return false;
	case My::BackgroundColorEnum::on_bright_yellow : return false;
	case My::BackgroundColorEnum::on_bright_blue : return false;
	case My::BackgroundColorEnum::on_bright_magenta : return false;
	case My::BackgroundColorEnum::on_bright_cyan : return false;
	case My::BackgroundColorEnum::on_bright_white : return false;
	default : {
		std::cout << termcolor::red << "Invalid Background color passed\n"
				  << termcolor::reset;
		return true;
	};
	}

	const bool invalid {color < BackgroundColorEnum::on_bright_white};

	if (invalid) {
		std::cout << termcolor::red << "Invalid Background color passed\n"
				  << termcolor::reset;
		return true;
	}
}

const ColorEnum &Colors::StringToColorEnum(const str &color) {
	if (!bCheckColorExists(color)) {
		std::cout << termcolor::red << "Invalid color passed\n"
				  << termcolor::reset;
		return ColorEnum::none;
	}

	if (color == "grey") return ColorEnum::grey;
	else if (color == "red") return ColorEnum::red;
	else if (color == "green") return ColorEnum::green;
	else if (color == "yellow") return ColorEnum::yellow;
	else if (color == "blue") return ColorEnum::blue;
	else if (color == "magenta") return ColorEnum::magenta;
	else if (color == "cyan") return ColorEnum::cyan;
	else if (color == "white") return ColorEnum::white;
	else if (color == "bright_grey") return ColorEnum::bright_grey;
	else if (color == "bright_red") return ColorEnum::bright_red;
	else if (color == "bright_green") return ColorEnum::bright_green;
	else if (color == "bright_yellow") return ColorEnum::bright_yellow;
	else if (color == "bright_blue") return ColorEnum::bright_blue;
	else if (color == "bright_magenta") return ColorEnum::bright_magenta;
	else if (color == "bright_cyan") return ColorEnum::bright_cyan;
	else if (color == "bright_white") return ColorEnum::bright_white;
	else {
		std::cout << termcolor::red << "Invalid color passed\n"
				  << termcolor::reset;
		return ColorEnum::none;
	}
}

const BackgroundColorEnum &Colors::StringToBackgroundColorEnum(
	const str &color) {
	if (!bCheckBackgroundExists(color)) {
		std::cout << termcolor::red << "Invalid Background color passed\n"
				  << termcolor::reset;
		return BackgroundColorEnum::none;
	}
	if (color == "on_grey") return BackgroundColorEnum::on_grey;
	else if (color == "on_red") return BackgroundColorEnum::on_red;
	else if (color == "on_green") return BackgroundColorEnum::on_green;
	else if (color == "on_yellow") return BackgroundColorEnum::on_yellow;
	else if (color == "on_blue") return BackgroundColorEnum::on_blue;
	else if (color == "on_magenta") return BackgroundColorEnum::on_magenta;
	else if (color == "on_cyan") return BackgroundColorEnum::on_cyan;
	else if (color == "on_white") return BackgroundColorEnum::on_white;
	else if (color == "on_bright_grey")
		return BackgroundColorEnum::on_bright_grey;
	else if (color == "on_bright_red")
		return BackgroundColorEnum::on_bright_red;
	else if (color == "on_bright_green")
		return BackgroundColorEnum::on_bright_green;
	else if (color == "on_bright_yellow")
		return BackgroundColorEnum::on_bright_yellow;
	else if (color == "on_bright_blue")
		return BackgroundColorEnum::on_bright_blue;
	else if (color == "on_bright_magenta")
		return BackgroundColorEnum::on_bright_magenta;
	else if (color == "on_bright_cyan")
		return BackgroundColorEnum::on_bright_cyan;
	else if (color == "on_bright_white")
		return BackgroundColorEnum::on_bright_white;
	else {
		std::cout << termcolor::red << "Invalid Background color passed\n"
				  << termcolor::reset;
		return BackgroundColorEnum::none;
	}
}

const str &Colors::strEnumToStream(const ColorEnum &color) {
	static std::ostringstream ss;
	static str				  result;

	if (color == ColorEnum::none || color == ColorEnum::reset) {
		const static std::ostream &reset {std::cout << "" << termcolor::reset};
		ss << reset.rdbuf();
	}

	if (!(color == ColorEnum::none || color == ColorEnum::reset)) {
		const static std::ostream &Return = ostrColorEnumToOstream(color);
		ss << Return.rdbuf();
	}
	result = ss.str();

	return result;
}

const str &Colors::strEnumToStream(const BackgroundColorEnum &color) {
	static strstrn ss {};
	static str			  result;

	if (color == BackgroundColorEnum::none ||
		color == BackgroundColorEnum::reset) {
		const static ostr &reset {std::cout << "" << termcolor::reset};
		ss << reset.rdbuf();
	}

	if (!(color == BackgroundColorEnum::none ||
		  color == BackgroundColorEnum::reset))
		ss << ostrBackgroundEnumToOstream(color).rdbuf();

	result = ss.str();

	return result;
}

const str &Colors::strEnumToTxt(const ColorEnum &color) {
	const static str &colorTxt = strEnumToText(color);
	return colorTxt;
}

const str &Colors::strEnumToTxt(const BackgroundColorEnum &BackgroundColor) {
	const static str &BackgroundColorTxt = strEnumToText(BackgroundColor);
	return BackgroundColorTxt;
}

const bool Colors::bISClassEmpty() noexcept {
	const bool emptyClass {bHasColor() == false &&
						   bHasBackgroundColor() == false &&
						   isLocalized == false && ColorReturnStr.empty() &&
						   BackgroundReturnStr.empty()};

	return emptyClass;
}

const bool Colors::bISClassEmpty(const Colors &c) noexcept {
	const bool emptyClass {(c.color == ColorEnum::none ||
							c.backgroundColor == BackgroundColorEnum::none) &&
						   c.isLocalized == false && c.ColorReturnStr.empty() &&
						   c.BackgroundReturnStr.empty()};

	return emptyClass;
}

const void Colors::ResetColor() { SetClassColor(ColorEnum::reset); }

const void Colors::ResetBackgroundColor() noexcept {
	SetClassBackgroundColor(BackgroundColorEnum::reset);
}

const std::ostream &Colors::Print(const str &msg, const ColorEnum &color) {
	return std::cout << Colors::UseColor(color) << msg
					 << Colors::UseColor(ColorEnum::reset);
}

const str &Colors::UseColor(const ColorEnum &color) {
	const static str &Color = strEnumToStream(color);
	return Color;
}

const str &Colors::UseColor(const BackgroundColorEnum &color) {
	return UseBackgroundColor(color);
}

const str &Colors::UseBackgroundColor(const BackgroundColorEnum &color) {
	const static str &BgColor = strEnumToStream(color);
	return BgColor;
}

// TODO: Implement this function const Colors Colors::GetColors(
// const ColorEnum &color, const BackgroundColorEnum &BackgroundColor)
const Colors Colors::GetColors(
	const ColorEnum			  &color,
	const BackgroundColorEnum &BackgroundColor) noexcept {
	return Colors();
}
const Colors *Colors::GetColorsPtr(ColorEnum				 &color,
								   const BackgroundColorEnum &BackgroundColor) {
	return nullptr;
}
// TODO: Implement this function const Colors Colors::GetColors(const Colors &c)
const Colors Colors::GetColors(const Colors &reference) noexcept {
	return Colors();
}

// TODO: Implement this function const Colors* Colors::GetColorsPtr(const Colors
// &c)
const Colors *Colors::GetColorsPtr(const Colors &c) noexcept { return &c; }

const Colors *Colors::GetColorsPtr(const Colors *Val) noexcept { return Val; }

// TODO: Implement this function
const Colors Colors::GetColors(std::unique_ptr<Colors> &ptr) noexcept {
	return Colors();
}

// TODO: Implement this function

const Colors *Colors::GetColorsPtr(std::unique_ptr<Colors> &ptr) noexcept {
	return nullptr;
}

// TODO: Implement this function
const Colors Colors::GetColors(std::shared_ptr<Colors> &ptr) noexcept {
	return Colors();
}

// TODO: Implement this function
const Colors *Colors::GetColorsPtr(std::shared_ptr<Colors> &ptr) noexcept {
	return nullptr;
}

// TODO: Implement this function
const Colors Colors::GetColors(const str &ColorReturn,
							   const str &BackgroundReturn) noexcept {
	// TODO: Implement this function
	return Colors();
}

// TODO: Implement this function
const Colors *Colors::GetColorsPtr(const str &ColorReturn,
								   const str &BackgroundReturn) {
	return nullptr;
}

// TODO: Implement this function
const Colors Colors::GetColors()
	const noexcept { // TODO: Implement this function
	return *this;
}

// TODO: Implement this function
const Colors *Colors::ColorsPtr() const noexcept {
	static Colors a = GetColors();
	return &a;
}

// TODO: Implement this function
const Colors *Colors::ColorsPtr(const str &ColorReturn,
								const str &BackgroundReturn) noexcept {
	return nullptr;
}

const bool &Colors::bCheckColorExists(const str &Color) {
	if (Color.empty()) return false;

	const bool ColorExists {
		((Color == "grey") || (Color == "red") || (Color == "green") ||
		 (Color == "yellow") || (Color == "blue") || (Color == "magenta") ||
		 (Color == "cyan") || (Color == "white") || (Color == "bright_grey") ||
		 (Color == "bright_red") || (Color == "bright_green") ||
		 (Color == "bright_yellow") || (Color == "bright_blue") ||
		 (Color == "bright_magenta") || (Color == "bright_cyan") ||
		 (Color == "bright_white"))};

	if (ColorExists == true) return true;
	else return false;
}

const bool &Colors::bCheckBackgroundExists(const str &BackgroundColor) {
	if (BackgroundColor.empty()) return false;

	const bool BackgroundExists {
		(BackgroundColor == "on_grey") || (BackgroundColor == "on_red") ||
		(BackgroundColor == "on_green") || (BackgroundColor == "on_yellow") ||
		(BackgroundColor == "on_blue") || (BackgroundColor == "on_magenta") ||
		(BackgroundColor == "on_cyan") || (BackgroundColor == "on_white") ||
		(BackgroundColor == "on_bright_grey") ||
		(BackgroundColor == "on_bright_red") ||
		(BackgroundColor == "on_bright_green") ||
		(BackgroundColor == "on_bright_yellow") ||
		(BackgroundColor == "ton_bright_blue") ||
		(BackgroundColor == "on_bright_magenta") ||
		(BackgroundColor == "on_bright_cyan") ||
		(BackgroundColor == "on_bright_white")};

	if (BackgroundExists == true) return true;
	return false;
}

const str &Colors::strCheckColorExists(const str &Color) {
	if (!bCheckColorExists(Color)) {
		std::cout << termcolor::red << "Color does not exist\n"
				  << termcolor::reset;
		return "none";
	} else return Color;
}

const str &Colors::strCheckBackgroundExists(const str &BackgroundColor) {
	if (!bCheckBackgroundExists(BackgroundColor)) {
		std::cout << termcolor::red << "Background color does not exist\n"
				  << termcolor::reset;
		return "none";
	} else return BackgroundColor;
}

const ColorEnum &Colors::ColorEnum_CheckColorExists(const str &Color) {
	if (!bCheckColorExists(Color)) {
		std::cout << termcolor::red << "Color does not exist\n"
				  << termcolor::reset;
		return ColorEnum::none;
	} else return StringToColorEnum(Color);
}

const ColorEnum &Colors::bCheckColorExistsReturnColorEnum(
	const ColorEnum &Color) {
	if (bCheckInvalidColor(Color)) {
		std::cout << termcolor::red << "Invalid ColorEnum passed\n"
				  << termcolor::reset;
		return ColorEnum::none;
	} else return Color;
}

const BackgroundColorEnum &Colors::enumBG_CheckBgColorExists(
	const str &BgColor) {
	if (!bCheckBackgroundExists(BgColor)) {
		std::cout << termcolor::red << "Background color does not exist\n"
				  << termcolor::reset;

		return BackgroundColorEnum::none;
	} else return StringToBackgroundColorEnum(BgColor);
}

const BgEnum &Colors::enumBG_CheckBgColorExists(const BgEnum &BgColor) {
	if (bCheckInvalidColor(BgColor)) {
		std::cout << termcolor::red << "Invalid BackgroundColorEnum passed\n"
				  << termcolor::reset;
		return BackgroundColorEnum::none;
	}
	return BgColor;
}

const std::ostream &Colors::ostrColorEnumToOstream(const ColorEnum &color) {
	switch (color) {
	case ColorEnum::none : [[fallthrough]];

	case ColorEnum::reset : {
		const static std::ostream &reset {std::cout << "" << termcolor::reset};
		return reset;
	}

	case ColorEnum::grey : {
		const static std::ostream &grey {std::cout << "" << termcolor::grey};
		return grey;
	}

	case ColorEnum::red : {
		const static std::ostream &red {std::cout << "" << termcolor::red};
		return red;
	}

	case ColorEnum::green : {
		const static std::ostream &green {std::cout << "" << termcolor::green};
		return green;
	}

	case ColorEnum::yellow : {
		const static std::ostream &yellow {std::cout << ""
													 << termcolor::yellow};
		return yellow;
	}

	case ColorEnum::blue : {
		const static std::ostream &blue {std::cout << "" << termcolor::blue};
		return blue;
	}

	case ColorEnum::magenta : {
		const static std::ostream &magenta {std::cout << ""
													  << termcolor::magenta};
		return magenta;
	}

	case ColorEnum::cyan : {
		const static std::ostream &cyan {std::cout << "" << termcolor::cyan};
		return cyan;
	}

	case ColorEnum::white : {
		const static std::ostream &white {std::cout << "" << termcolor::white};
		return white;
	}

	case ColorEnum::bright_grey : {
		const static std::ostream &bright_grey {
			std::cout << "" << termcolor::bright_grey};
		return bright_grey;
	}

	case ColorEnum::bright_red : {
		const static std::ostream &bright_red {std::cout
											   << "" << termcolor::bright_red};
		return bright_red;
	}

	case ColorEnum::bright_green : {
		const static std::ostream &bright_green {
			std::cout << "" << termcolor::bright_green};
		return bright_green;
	}

	case ColorEnum::bright_yellow : {
		const static std::ostream &bright_yellow {
			std::cout << "" << termcolor::bright_yellow};
		return bright_yellow;
	}

	case ColorEnum::bright_blue : {
		const static std::ostream &bright_blue {
			std::cout << "" << termcolor::bright_yellow};
		return bright_blue;
	}

	case ColorEnum::bright_magenta : {
		const static std::ostream &bright_magenta {
			std::cout << "" << termcolor::bright_magenta};
		return bright_magenta;
	}

	case ColorEnum::bright_cyan : {
		const static std::ostream &bright_cyan {
			std::cout << "" << termcolor::bright_cyan};
		return bright_cyan;
	}

	case ColorEnum::bright_white : {
		const static std::ostream &bright_white {
			std::cout << "" << termcolor::bright_white};
		return bright_white;
	}

	default : {
		constexpr const char *func = __func__;
		static str			  err;
		err = "Error at: \nfunction: " + *func;
		err + "In line: " + std::to_string(__LINE__) += '\n';
		return errOstr_ostrDefaultCase(err);
	};
	}
}

const std::ostream &Colors::ostrBackgroundEnumToOstream(
	const BackgroundColorEnum &color) {
	switch (color) {
	case BackgroundColorEnum::reset : [[fallthrough]];
	case BackgroundColorEnum::none : {
		const static std::ostream &none = std::cout << termcolor::reset;
		return none;
	}
	case BackgroundColorEnum::on_grey : {
		const static std::ostream &on_grey {std::cout << termcolor::on_grey};
		return on_grey;
	}
	case BackgroundColorEnum::on_red : {
		const static std::ostream &on_red {std::cout << termcolor::on_red};
		return on_red;
	}
	case BackgroundColorEnum::on_green : {
		const static std::ostream &on_green {std::cout << termcolor::on_green};
		return on_green;
	}
	case BackgroundColorEnum::on_yellow : {
		const static std::ostream &on_yellow {std::cout
											  << termcolor::on_yellow};
		return on_yellow;
	}
	case BackgroundColorEnum::on_blue : {
		const static std::ostream &on_blue {std::cout << termcolor::on_blue};
		return on_blue;
	}
	case BackgroundColorEnum::on_magenta : {
		const static std::ostream &on_magenta {std::cout
											   << termcolor::on_magenta};
		return on_magenta;
	}
	case BackgroundColorEnum::on_cyan : {
		const static std::ostream &on_cyan {std::cout << termcolor::on_cyan};
		return on_cyan;
	}
	case BackgroundColorEnum::on_white : {
		const static std::ostream &on_white {std::cout << termcolor::on_white};
		return on_white;
	}

	case BackgroundColorEnum::on_bright_grey : {
		const static std::ostream &on_bright_grey {
			std::cout << termcolor::on_bright_grey};
		return on_bright_grey;
	}

	case BackgroundColorEnum::on_bright_red : {
		const static std::ostream &on_bright_red {std::cout
												  << termcolor::on_bright_red};
		return on_bright_red;
	}

	case BackgroundColorEnum::on_bright_green : {
		const static std::ostream &on_bright_green {
			std::cout << termcolor::on_bright_green};
		return on_bright_green;
	}

	case BackgroundColorEnum::on_bright_yellow : {
		const static std::ostream &on_bright_yellow {
			std::cout << termcolor::on_bright_yellow};
		return on_bright_yellow;
	}

	case BackgroundColorEnum::on_bright_blue : {
		const static std::ostream &on_bright_blue {
			std::cout << termcolor::on_bright_blue};
		return on_bright_blue;
	}

	case BackgroundColorEnum::on_bright_magenta : {
		const static std::ostream &on_bright_magenta {
			std::cout << termcolor::on_bright_magenta};
		return on_bright_magenta;
	}

	case BackgroundColorEnum::on_bright_cyan : {
		const static std::ostream &on_bright_cyan {
			std::cout << termcolor::on_bright_cyan};
		return on_bright_cyan;
	}

	case BackgroundColorEnum::on_bright_white : {
		const static std::ostream &on_bright_white {
			std::cout << termcolor::on_bright_white};
		return on_bright_white;
	}

	default : {
		const char *func = __func__;
		static str	err;
		err = "Error at: \nfunction: " + *func;
		err + "In line: " + std::to_string(__LINE__) += '\n';
		return errOstr_ostrDefaultCase(err);
	};
	}
}

const str &Colors::strEnumToText(const ColorEnum &color) {
	switch (color) {
	case ColorEnum::none : {
		const static str &none {"none"};
		return none;
	}

	case ColorEnum::reset : {
		const static str &reset {"reset"};
		return reset;
	}
	case ColorEnum::grey : {
		const static str &grey {"grey"};
		return grey;
	}
	case ColorEnum::red : {
		const static str &red {"red"};
		return red;
	}
	case ColorEnum::green : {
		const static str &green {"green"};
		return green;
	}
	case ColorEnum::yellow : {
		const static str &yellow {"yellow"};
		return yellow;
	}
	case ColorEnum::blue : {
		const static str &blue {"blue"};
		return blue;
	}
	case ColorEnum::magenta : {
		const static str &magenta {"magenta"};
		return magenta;
	}
	case ColorEnum::cyan : {
		const static str &cyan {"cyan"};
		return cyan;
	}
	case ColorEnum::white : {
		const static str &white {"white"};
		return white;
	}
	case ColorEnum::bright_grey : {
		const static str &bright_grey {"bright_grey"};
		return bright_grey;
	}
	case ColorEnum::bright_red : {
		const static str &bright_red {"bright_red"};
		return bright_red;
	}
	case ColorEnum::bright_green : {
		const static str &bright_green {"bright_green"};
		return bright_green;
	}
	case ColorEnum::bright_yellow : {
		const static str &bright_yellow {"bright_yellow"};
		return bright_yellow;
	}
	case ColorEnum::bright_blue : {
		const static str &bright_blue {"bright_blue"};
		return bright_blue;
	}
	case ColorEnum::bright_magenta : {
		const static str &bright_magenta {"bright_magenta"};
		return bright_magenta;
	}
	case ColorEnum::bright_cyan : {
		const static str &bright_cyan {"bright_cyan"};
		return bright_cyan;
	}
	case ColorEnum::bright_white : {
		const static str &bright_white {"bright_white"};
		return bright_white;
	}

	default : {
		const char *func = __func__;
		static str	err;
		err = "Error at: \nfunction: " + *func;
		err + "In line: " + std::to_string(__LINE__) += '\n';
		return errStr_strDefaultCase(err);
	};
	}
}

const str &Colors::strEnumToText(const BackgroundColorEnum &color) {
	switch (color) {
	case BackgroundColorEnum::reset : [[fallthrough]];

	case BackgroundColorEnum::none : {
		const static str &none {"none"};
		return none;
	}

	case BackgroundColorEnum::on_grey : {
		const static str &on_grey {"on_grey"};
		return on_grey;
	}

	case BackgroundColorEnum::on_red : {
		const static str &on_red {"on_red"};
		return on_red;
	}

	case BackgroundColorEnum::on_green : {
		const static str &on_green {"on_green"};
		return on_green;
	}

	case BackgroundColorEnum::on_yellow : {
		const static str &on_yellow {"on_yellow"};
		return on_yellow;
	}

	case BackgroundColorEnum::on_blue : {
		const static str &on_blue {"on_blue"};
		return on_blue;
	}

	case BackgroundColorEnum::on_magenta : {
		const static str &on_magenta {"on_magenta"};
		return on_magenta;
	}

	case BackgroundColorEnum::on_cyan : {
		const static str &on_cyan {"on_cyan"};
		return on_cyan;
	}

	case BackgroundColorEnum::on_white : {
		const static str &on_white {"on_white"};
		return on_white;
	}

	case BackgroundColorEnum::on_bright_grey : {
		const static str &on_bright_grey {"on_bright_grey"};
		return on_bright_grey;
	}

	case BackgroundColorEnum::on_bright_red : {
		const static str &on_bright_red {"on_bright_red"};
		return on_bright_red;
	}

	case BackgroundColorEnum::on_bright_green : {
		const static str &on_bright_green {"on_bright_green"};
		return on_bright_green;
	}

	case BackgroundColorEnum::on_bright_yellow : {
		const static str &on_bright_yellow {"on_bright_yellow"};
		return on_bright_yellow;
	}

	case BackgroundColorEnum::on_bright_blue : {
		const static str &on_bright_blue {"on_bright_blue"};
		return on_bright_blue;
	}

	case BackgroundColorEnum::on_bright_magenta : {
		const static str &on_bright_magenta {"on_bright_magenta"};
		return on_bright_magenta;
	}

	case BackgroundColorEnum::on_bright_cyan : {
		const static str &on_bright_cyan {"on_bright_cyan"};
		return on_bright_cyan;
	}

	case BackgroundColorEnum::on_bright_white : {
		const static str &on_bright_white {"on_bright_white"};
		return on_bright_white;
	}

	default : {
		const char *func = __func__;
		static str	err;
		err = "Error at: \nfunction: " + *func;
		err + "In line: " + std::to_string(__LINE__) += '\n';
		return errStr_strDefaultCase(err);
	}
	}
}
const str &Colors::errStr_strDefaultCase() {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print("Invalid color\n");
	const static str &none = "none";
	return none;
}

const str &Colors::errStr_strDefaultCase(const str &msg) {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print(msg);
	const str &none ("none");
	return none;
}

const std::ostream &Colors::errOstr_ostrDefaultCase() {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print("Invalid color\n");
	const static std::ostream &none = std::cout << "Invalid color";
	return none;
}

const std::ostream &Colors::errOstr_ostrDefaultCase(const str &msg) {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print(msg);
	const static ostr &none = std::cout << "msg";
	return none;
}

const void Colors::Initializer() {
	InitializerCalled	= true;
	color				= ColorEnum::none;
	backgroundColor		= BackgroundColorEnum::none;
	ColorReturnStr		= "none";
	BackgroundReturnStr = "none";
	isLocalized			= false;
	buffer				= 0;
}

Colors &Colors::operator=(const Colors &other) {
	if (this == &other) return *this;

	else {
		color				= other.color;
		backgroundColor		= other.backgroundColor;
		isLocalized			= other.isLocalized;
		ColorReturnStr		= other.ColorReturnStr;
		BackgroundReturnStr = other.BackgroundReturnStr;
		return *this;
	}
}

Colors::~Colors() {
	color			= CEnum::none;
	backgroundColor = BgEnum::none;
	ColorReturnStr.clear();
	BackgroundReturnStr.clear();
	isLocalized		  = false;
	InitializerCalled = false;
}
} // namespace My