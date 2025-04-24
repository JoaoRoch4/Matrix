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
const static ColorEnum			 CeNone = ColorEnum::none;
const static BackgroundColorEnum BgNone = BackgroundColorEnum::none;

Colors::Colors() noexcept
  : color(ColorEnum::none),
	backgroundColor(BackgroundColorEnum::none),
	ColorReturnStr(str()),
	BackgroundReturnStr(str()),
	isLocalized(false),
	InitializerCalled(false) {}

Colors::Colors(const Colors &c) noexcept {
	if (bISClassEmpty(c) && !InitializerCalled) Initializer();

	if (!bISClassEmpty(c)) {
		color				= CnumCheckColorExists(c.color);
		backgroundColor		= BgNumCheckBgColorExists(c.backgroundColor);
		isLocalized			= c.isLocalized;
		ColorReturnStr		= strCheckColorExists(c.ColorReturnStr);
		BackgroundReturnStr = strCheckBackgroundExists(c.BackgroundReturnStr);
	}

}

Colors::Colors(const Colors *ptr) noexcept {

	if (ptr == nullptr) {

		std::cout << termcolor::red << "pointer passed is a null pointer\n"
				  << termcolor::reset;

		Colors err = Colors();

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
		color			= CnumCheckColorExists(ptr->color);
		backgroundColor = BgNumCheckBgColorExists(ptr->backgroundColor);
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

		color			= CnumCheckColorExists(ptr->color);
		backgroundColor = BgNumCheckBgColorExists(ptr->backgroundColor);
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
		color			= CnumCheckColorExists(ptr->color);
		backgroundColor = BgNumCheckBgColorExists(ptr->backgroundColor);
		isLocalized		= ptr->isLocalized;
		ColorReturnStr	= strCheckColorExists(ptr->ColorReturnStr);
		BackgroundReturnStr =
			strCheckBackgroundExists(ptr->BackgroundReturnStr);
	}
}

Colors::Colors(const ColorEnum			 &color,
			   const BackgroundColorEnum &BackgroundColor) noexcept {

	const bool colorDoNotExists {bCheckInvalidColor(color)};
	const bool colorBackgroundDoNoExists {bCheckInvalidColor(BackgroundColor)};

	const bool bothDoNotExist {colorDoNotExists && colorBackgroundDoNoExists};

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
	}

	if (EmptyColorReturn && !EmptyBackgroundReturn) {
		std::cout << termcolor::red << "ColorReturn string passed is empty\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();
		backgroundColor		= StringToBgEnum(BackgroundReturn);
		BackgroundReturnStr = strCheckBackgroundExists(BackgroundReturn);
	}

	if (!EmptyColorReturn && EmptyBackgroundReturn) {

		std::cout << termcolor::red
				  << "BackgroundReturn string passed is empty\n"
				  << termcolor::reset;

		if (!InitializerCalled) Initializer();

		color		   = StrToCnum(ColorReturn);
		ColorReturnStr = strCheckColorExists(ColorReturn);
	}

	const bool colorDoNotExists = (bCheckColorExists(ColorReturn) == false);
	const bool colorBackgroundDoNoExists =
		(bCheckBgExists(BackgroundReturn) == false);
	const bool bothDoNotExist = colorDoNotExists && colorBackgroundDoNoExists;

	if (bothDoNotExist) {
		std::cout << termcolor::red
				  << "ColorReturn string passed does not correspond to any "
					 "color\n"
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

		if (bCheckColorExists(ColorReturn)) color = StrToCnum(ColorReturn);

		ColorReturnStr = strCheckColorExists(ColorReturn);

		return;
	}

	if (!colorBackgroundDoNoExists && colorDoNotExists) {
		std::cout << termcolor::red
				  << "ColorReturn and BackgroundReturn string passed do not"
					 "correspond to any color\n"
				  << termcolor::reset;
		if (!InitializerCalled) Initializer();

		backgroundColor =
			BgNumCheckBgColorExists(StringToBgEnum(BackgroundReturn));
		BackgroundReturnStr = strCheckBackgroundExists(BackgroundReturn);
		return;
	}

	const bool NotOk = (EmptyColorReturn &&
						EmptyBackgroundReturn &&
						Empty &&
						colorDoNotExists &&
						colorBackgroundDoNoExists &&
						bothDoNotExist);

	if (NotOk) {

		std::cout << termcolor::red << "An error has occurred at: " << __FILE__
				  << " line: " << __LINE__ << termcolor::reset << '\n';

		if (!InitializerCalled) Initializer();
	}

	if (!NotOk) {
		if (!InitializerCalled) Initializer();
		if (bCheckColorExists(ColorReturn)) color = StrToCnum(ColorReturn);
		ColorReturnStr = strCheckColorExists(ColorReturn);
		backgroundColor =
			BgNumCheckBgColorExists(StringToBgEnum(BackgroundReturn));
		BackgroundReturnStr = strCheckBackgroundExists(BackgroundReturn);
	}
}

void Colors::SetClassColor(const str &Txt) {

	if (Txt.empty() || bCheckColorExists(Txt) == false) {

		return StaticError::Exit("Color does not exist.\n");
	}
	ColorReturnStr = Txt;
}

void Colors::SetClassBackgroundColor(const str &BackgroundColor) {
	if (bCheckBgExists(BackgroundColor)) { BackgroundReturnStr = "none"; }
	BackgroundReturnStr = BackgroundColor;
}

void Colors::SetClassBackgroundColor(
	const BackgroundColorEnum &BackgroundColor) {
	backgroundColor		= BackgroundColor;
	const str &result	= strEnumToStream(BackgroundColor);
	BackgroundReturnStr = result;
}

void Colors::SetLocale(const bool &locale) noexcept {
	if (locale == false || isLocalized == true) return;

	if (locale == true) isLocalized = true;
}

bool Colors::bGetLocale() { return isLocalized; }

str Colors::StrGetColor(const Colors &c) {

	if (bISClassEmpty(c) == true) {

		const static str &err = "Error: Class passed is empty. " +
			std::to_string(__LINE__) +
			__func__ +
			'\n';
		constexpr const static char *none = "none";

		StaticError::Exit(err);
		return str();
	}
	return c.ColorReturnStr;
}

str Colors::StrGetColor() const noexcept { return ColorReturnStr; }

str Colors::StrGetBackgroundColor(const Colors &c) {

	if (bISClassEmpty(c) == true) {

		StaticError::Exit("Class passed is empty\n");
	}
	return c.ColorReturnStr;
}

str Colors::StrGetBackgroundColor() const noexcept {
	return this->BackgroundReturnStr;
}
bool Colors::bHasColor(const ColorEnum &color) noexcept {
	if (color == ColorEnum::reset || color == ColorEnum::none) return false;
	return true;
}

bool Colors::bHasColor() const noexcept {
	if (this->color == ColorEnum::reset || this->color == ColorEnum::none)
		return false;
	return true;
}

bool Colors::bHasBgColor(const BackgroundColorEnum &BgColor) noexcept {
	if (BgColor == BackgroundColorEnum::reset ||
		BgColor == BackgroundColorEnum::none)
		return false;
	return true;
}

bool Colors::bHasBackgroundColor() const {
	const bool hasBackgroundColor {
		(this->backgroundColor == BackgroundColorEnum::reset ||
		 this->backgroundColor == BackgroundColorEnum::none)};

	if (hasBackgroundColor == false) return false;
	return true;
}

bool Colors::bCheckInvalidColor(const ColorEnum &color) noexcept {
	switch (color) {
		case ColorEnum::none		   : return false;
		case ColorEnum::reset		   : return false;
		case ColorEnum::grey		   : return false;
		case ColorEnum::red			   : return false;
		case ColorEnum::green		   : return false;
		case ColorEnum::yellow		   : return false;
		case ColorEnum::blue		   : return false;
		case ColorEnum::magenta		   : return false;
		case ColorEnum::cyan		   : return false;
		case ColorEnum::white		   : return false;
		case ColorEnum::bright_grey	   : return false;
		case ColorEnum::bright_red	   : return false;
		case ColorEnum::bright_green   : return false;
		case ColorEnum::bright_yellow  : return false;
		case ColorEnum::bright_blue	   : return false;
		case ColorEnum::bright_magenta : return false;
		case ColorEnum::bright_cyan	   : return false;
		case ColorEnum::bright_white   : return false;
		default :
			{
				std::cout << termcolor::red << "Invalid color passed\n"
						  << termcolor::reset;
				return true;
			}
			return false;
	}

	const bool invalid {color < ColorEnum::bright_white};

	if (invalid) {
		std::cout << termcolor::red << "Invalid color passed\n"
				  << termcolor::reset;
		return true;
	}
}

bool Colors::bCheckInvalidColor(const BackgroundColorEnum &color) noexcept {
	switch (color) {

		case BackgroundColorEnum::none				: return false;
		case BackgroundColorEnum::reset				: return false;
		case BackgroundColorEnum::on_grey			: return false;
		case BackgroundColorEnum::on_red			: return false;
		case BackgroundColorEnum::on_green			: return false;
		case BackgroundColorEnum::on_yellow			: return false;
		case BackgroundColorEnum::on_blue			: return false;
		case BackgroundColorEnum::on_magenta		: return false;
		case BackgroundColorEnum::on_cyan			: return false;
		case BackgroundColorEnum::on_white			: return false;
		case BackgroundColorEnum::on_bright_grey	: return false;
		case BackgroundColorEnum::on_bright_red		: return false;
		case BackgroundColorEnum::on_bright_green	: return false;
		case BackgroundColorEnum::on_bright_yellow	: return false;
		case BackgroundColorEnum::on_bright_blue	: return false;
		case BackgroundColorEnum::on_bright_magenta : return false;
		case BackgroundColorEnum::on_bright_cyan	: return false;
		case BackgroundColorEnum::on_bright_white	: return false;
		default :
			{
				std::cout << termcolor::red
						  << "Invalid Background color passed\n"
						  << termcolor::reset;
				return true;
			};
	}
}

ColorEnum Colors::StrToCnum(const str &color) {

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

		return CeNone;
	}
}

BackgroundColorEnum Colors::StringToBgEnum(const str &BgColor) {

	if (!bCheckBgExists(BgColor)) {

		if (BgColor == "on_grey") return BackgroundColorEnum::on_grey;
		else if (BgColor == "on_red") return BackgroundColorEnum::on_red;
		else if (BgColor == "on_green") return BackgroundColorEnum::on_green;
		else if (BgColor == "on_yellow") return BackgroundColorEnum::on_yellow;
		else if (BgColor == "on_blue") return BackgroundColorEnum::on_blue;
		else if (BgColor == "on_magenta")
			return BackgroundColorEnum::on_magenta;
		else if (BgColor == "on_cyan") return BackgroundColorEnum::on_cyan;
		else if (BgColor == "on_white") return BackgroundColorEnum::on_white;
		else if (BgColor == "on_bright_grey")
			return BackgroundColorEnum::on_bright_grey;
		else if (BgColor == "on_bright_red")
			return BackgroundColorEnum::on_bright_red;
		else if (BgColor == "on_bright_green")
			return BackgroundColorEnum::on_bright_green;
		else if (BgColor == "on_bright_yellow")
			return BackgroundColorEnum::on_bright_yellow;
		else if (BgColor == "on_bright_blue")
			return BackgroundColorEnum::on_blue;
		else if (BgColor == "on_bright_magenta")
			return BackgroundColorEnum::on_bright_magenta;
		else if (BgColor == "on_bright_cyan")
			return BackgroundColorEnum::on_bright_cyan;
		else if (BgColor == "on_bright_white")
			return BackgroundColorEnum::on_bright_white;
		else {
			std::cout << termcolor::red << "Invalid Background color passed\n"
					  << termcolor::reset;
			return BackgroundColorEnum::none;
		}
	} else {

		std::cout << termcolor::red << "Invalid Background color passed\n"
				  << termcolor::reset;
		return BackgroundColorEnum::none;
	}
}

std::ostream Colors::strEnumToStream(const ColorEnum &color) {

	std::ostringstream ss;

	if (color == ColorEnum::none || color == ColorEnum::reset) {
		const std::ostream &reset {std::cout << "" << termcolor::reset};
		ss << reset.rdbuf();

	} else if (!(color == ColorEnum::none || color == ColorEnum::reset)) {
		const std::ostream &Return = ostrColorEnumToOstream(color);
		ss << Return.rdbuf();
	}

	return std::ostream(ss.rdbuf());
}

str Colors::strEnumToStream(const BackgroundColorEnum &color) {

	static std::stringstream ss {};
	static str				 result;

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

str Colors::strEnumToTxt(const ColorEnum &color) {
	const static str &colorTxt = strEnumToText(color);
	return colorTxt;
}

str Colors::strEnumToTxt(const BackgroundColorEnum &BackgroundColor) {
	const static str &BackgroundColorTxt = strEnumToText(BackgroundColor);
	return BackgroundColorTxt;
}

bool Colors::bISClassEmpty() noexcept {
	const bool emptyClass {bHasColor() == false &&
						   bHasBackgroundColor() == false &&
						   isLocalized == false &&
						   ColorReturnStr.empty() &&
						   BackgroundReturnStr.empty()};

	return emptyClass;
}

bool Colors::bISClassEmpty(const Colors &c) noexcept {
	const bool emptyClass {(c.color == ColorEnum::none ||
							c.backgroundColor == BackgroundColorEnum::none) &&
						   c.isLocalized == false &&
						   c.ColorReturnStr.empty() &&
						   c.BackgroundReturnStr.empty()};

	return emptyClass;
}

void Colors::ResetBackgroundColor() noexcept {
	return SetClassBackgroundColor(BackgroundColorEnum::reset);
}

void Colors::Print(const str &msg, const ColorEnum &color) {

	// std::cout << UseColor(color) << msg << termcolor::reset;
}

void Colors::Print(const ColorEnum &color, const str &msg, ...) {


}

void Colors::Print(const BgEnum &color, const str &msg, ...) {}

void Colors::PrintColor(const ColorEnum &color) {

	switch (color) {

		case ColorEnum::none	: [[fallthrough]];
		case ColorEnum::reset	: std::cout << termcolor::reset; break;
		case ColorEnum::grey	: std::cout << termcolor::grey; break;
		case ColorEnum::red		: std::cout << termcolor::red; break;
		case ColorEnum::green	: std::cout << termcolor::green; break;
		case ColorEnum::yellow	: std::cout << termcolor::yellow; break;
		case ColorEnum::blue	: std::cout << termcolor::blue; break;
		case ColorEnum::magenta : std::cout << termcolor::magenta; break;
		case ColorEnum::cyan	: std::cout << termcolor::cyan; break;
		case ColorEnum::white	: std::cout << termcolor::white; break;

		case ColorEnum::bright_grey :
			std::cout << termcolor::bright_grey;
			break;
		case ColorEnum::bright_red : std::cout << termcolor::bright_red; break;
		case ColorEnum::bright_green :
			std::cout << termcolor::bright_green;
			break;
		case ColorEnum::bright_yellow :
			std::cout << termcolor::bright_yellow;
			break;
		case ColorEnum::bright_blue :
			std::cout << termcolor::bright_blue;
			break;
		case ColorEnum::bright_magenta :
			std::cout << termcolor::bright_magenta;
			break;
		case ColorEnum::bright_cyan :
			std::cout << termcolor::bright_cyan;
			break;
		case ColorEnum::bright_white :
			std::cout << termcolor::bright_white;
			break;
		default : std::cout << "Invalid color"; break;
	};
}

void Colors::PrintColor(const BgEnum &color) {}

void Colors::PrintMsgColor(const str &msg, const ColorEnum &color,
						   const bool &reset) {
	switch (color) {

		case ColorEnum::none	: [[fallthrough]];
		case ColorEnum::reset	: std::cout << termcolor::reset; break;
		case ColorEnum::grey	: std::cout << termcolor::grey; break;
		case ColorEnum::red		: std::cout << termcolor::red; break;
		case ColorEnum::green	: std::cout << termcolor::green; break;
		case ColorEnum::yellow	: std::cout << termcolor::yellow; break;
		case ColorEnum::blue	: std::cout << termcolor::blue; break;
		case ColorEnum::magenta : std::cout << termcolor::magenta; break;
		case ColorEnum::cyan	: std::cout << termcolor::cyan; break;
		case ColorEnum::white	: std::cout << termcolor::white; break;
		case ColorEnum::bright_grey :
			std::cout << termcolor::bright_grey;
			break;
		case ColorEnum::bright_red : std::cout << termcolor::bright_red; break;
		case ColorEnum::bright_green :
			std::cout << termcolor::bright_green;
			break;
		case ColorEnum::bright_yellow :
			std::cout << termcolor::bright_yellow;
			break;
		case ColorEnum::bright_blue :
			std::cout << termcolor::bright_blue;
			break;
		case ColorEnum::bright_magenta :
			std::cout << termcolor::bright_magenta;
			break;
		case ColorEnum::bright_cyan :
			std::cout << termcolor::bright_cyan;
			break;
		case ColorEnum::bright_white :
			std::cout << termcolor::bright_white;
			break;
		default : std::cout << "Invalid color"; break;
	};

	std::cout << msg;

	if (reset) std::cout << termcolor::reset;
}

void Colors::PrintMsgColor(const str &msg, const BgEnum &color,
						   const bool &reset) {}

str Colors::UseColor(const ColorEnum &color) {
	// return strEnumToStream(color);
	return str();
}

str Colors::UseColor(const BackgroundColorEnum &BgColor) {
	return UseBackgroundColor(BgColor);
}

str Colors::UseBackgroundColor(const BackgroundColorEnum &color) {
	return strEnumToStream(color);
}

// TODO: Implement this function const Colors Colors::GetColors(
// const ColorEnum &color, const BackgroundColorEnum
// &BackgroundColor)
const Colors
Colors::GetColors(const ColorEnum			&color,
				  const BackgroundColorEnum &BackgroundColor) noexcept {
	return Colors();
}
const Colors *Colors::GetColorsPtr(ColorEnum				 &color,
								   const BackgroundColorEnum &BackgroundColor) {
	return nullptr;
}
// TODO: Implement this function const Colors
// Colors::GetColors(const Colors &c)
const Colors Colors::GetColors(const Colors &reference) noexcept {
	return Colors();
}

// TODO: Implement this function const Colors*
// Colors::GetColorsPtr(const Colors &c)
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
const Colors *
Colors::GetColorsPtr(const str &ColorReturn, const str &BackgroundReturn) {
	return nullptr;
}

// TODO: Implement this function
const Colors
Colors::GetColors() const noexcept { // TODO: Implement this function
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

bool Colors::bCheckColorExists(const str &Color) {

	if (Color.empty()) return false;

	const bool ColorExists {((Color == "grey") ||
							 (Color == "red") ||
							 (Color == "green") ||
							 (Color == "yellow") ||
							 (Color == "blue") ||
							 (Color == "magenta") ||
							 (Color == "cyan") ||
							 (Color == "white") ||
							 (Color == "bright_grey") ||
							 (Color == "bright_red") ||
							 (Color == "bright_green") ||
							 (Color == "bright_yellow") ||
							 (Color == "bright_blue") ||
							 (Color == "bright_magenta") ||
							 (Color == "bright_cyan") ||
							 (Color == "bright_white"))};

	if (ColorExists == true) return true;
	else return false;
}

bool Colors::bCheckBgExists(const str &BgColor) {

	if (BgColor.empty()) {
		Print("Invalid Background color passed: \n "
			  "BgColor = " +
				  BgColor +
				  " is empty \n",
			  CEnum::red);
		return false;
	}

	const bool BackgroundExists((BgColor == "on_grey") ||
								(BgColor == "on_red") ||
								(BgColor == "on_green") ||
								(BgColor == "on_yellow") ||
								(BgColor == "on_blue") ||
								(BgColor == "on_magenta") ||
								(BgColor == "on_cyan") ||
								(BgColor == "on_white") ||
								(BgColor == "on_bright_grey") ||
								(BgColor == "on_bright_red") ||
								(BgColor == "on_bright_green") ||
								(BgColor == "on_bright_yellow") ||
								(BgColor == "ton_bright_blue") ||
								(BgColor == "on_bright_magenta") ||
								(BgColor == "on_bright_cyan") ||
								(BgColor == "on_bright_white"));

	if (BackgroundExists == true) return true;

	if (BackgroundExists == false)
		Print("Invalid Background color passed: \n "
			  "BgColor = " +
				  BgColor +
				  " is not valid \n",
			  CEnum::red);

	return false;
}

bool Colors::bCheckBgExists(const BgEnum &BgColor) {

	switch (BgColor) {
		case BgEnum::none			   : return false;
		case BgEnum::reset			   : return true;
		case BgEnum::on_grey		   : return true;
		case BgEnum::on_red			   : return true;
		case BgEnum::on_green		   : return true;
		case BgEnum::on_yellow		   : return true;
		case BgEnum::on_blue		   : return true;
		case BgEnum::on_magenta		   : return true;
		case BgEnum::on_cyan		   : return true;
		case BgEnum::on_white		   : return true;
		case BgEnum::on_bright_grey	   : return true;
		case BgEnum::on_bright_red	   : return true;
		case BgEnum::on_bright_green   : return true;
		case BgEnum::on_bright_yellow  : return true;
		case BgEnum::on_bright_blue	   : return true;
		case BgEnum::on_bright_magenta : return true;
		case BgEnum::on_bright_cyan	   : return true;
		case BgEnum::on_bright_white   : return true;
		default :
			{

				std::cout << termcolor::red
						  << "Invalid Background color Enum passed: "
						  << " BgColor = " << static_cast<int>(BgColor) << '\n'
						  << termcolor::reset;
				return false;
			};
	}
}

str Colors::strCheckColorExists(const str &Color) {
	if (!bCheckColorExists(Color)) {
		std::cout << termcolor::red << "Color does not exist\n"
				  << termcolor::reset;
		return "none";
	} else return Color;
}

str Colors::strCheckBackgroundExists(const str &BackgroundColor) {

	if (!bCheckBgExists(BackgroundColor)) {

		std::cout << termcolor::red << "Background color does not exist\n"
				  << termcolor::reset;
		return "none";
	} else return BackgroundColor;
}

CEnum Colors::CnumCheckColorExists(const str &Color) {

	if (!bCheckColorExists(Color)) {
		std::cout << termcolor::red << "Color does not exist\n"
				  << termcolor::reset;

		return ColorEnum::none;

	} else return StrToCnum(Color);
}

CEnum Colors::CnumCheckColorExists(const ColorEnum &Color) {

	if (bCheckInvalidColor(Color)) {

		std::cout << termcolor::red << "Invalid ColorEnum passed\n"
				  << termcolor::reset;

		return ColorEnum::none;

	} else return Color;
}

BackgroundColorEnum Colors::BgNumCheckBgColorExists(const str &BgColor) {

	if (!bCheckBgExists(BgColor)) {

		std::cout << termcolor::red << "Background color does not exist\n"
				  << termcolor::reset;

		return BackgroundColorEnum::none;
	} else return StringToBgEnum(BgColor);
}

BgEnum Colors::BgNumCheckBgColorExists(const BgEnum &BgColor) {
	if (bCheckInvalidColor(BgColor)) {
		std::cout << termcolor::red << "Invalid BackgroundColorEnum passed\n"
				  << termcolor::reset;
		return BackgroundColorEnum::none;
	}
	return BgColor;
}

bool Colors::bCheckColorExists(const ColorEnum &Color) {

	if (bCheckInvalidColor(Color)) {

		std::cout << termcolor::red << "Invalid ColorEnum passed\n"
				  << termcolor::reset;

		return false;

	} else return true;
}

std::ostream Colors::ostrColorEnumToOstream(const ColorEnum &color) {

	std::ostringstream ss {};

	switch (color) {
		case ColorEnum::none		   : [[fallthrough]];
		case ColorEnum::reset		   : ss << termcolor::reset; break;
		case ColorEnum::grey		   : ss << termcolor::grey; break;
		case ColorEnum::red			   : ss << termcolor::red; break;
		case ColorEnum::green		   : ss << termcolor::green; break;
		case ColorEnum::yellow		   : ss << termcolor::yellow; break;
		case ColorEnum::blue		   : ss << termcolor::blue; break;
		case ColorEnum::magenta		   : ss << termcolor::magenta; break;
		case ColorEnum::cyan		   : ss << termcolor::cyan; break;
		case ColorEnum::white		   : ss << termcolor::white; break;
		case ColorEnum::bright_grey	   : ss << termcolor::bright_grey; break;
		case ColorEnum::bright_red	   : ss << termcolor::bright_red; break;
		case ColorEnum::bright_green   : ss << termcolor::bright_green; break;
		case ColorEnum::bright_yellow  : ss << termcolor::bright_yellow; break;
		case ColorEnum::bright_blue	   : ss << termcolor::bright_blue; break;
		case ColorEnum::bright_magenta : ss << termcolor::bright_magenta; break;
		case ColorEnum::bright_cyan	   : ss << termcolor::bright_cyan; break;
		case ColorEnum::bright_white   : ss << termcolor::bright_white; break;
		default						   : ss << "Invalid color"; break;
	};

	return ostr(ss.rdbuf());
}

std::ostream
Colors::ostrBackgroundEnumToOstream(const BackgroundColorEnum &BgColor) {

	static std::ostringstream ss;

	// Clear the stringstream before use
	ss.str("");

	// Reset any error flags
	ss.clear();

#define trmc termcolor

	switch (BgColor) {

		case BgEnum::reset			   : [[fallthrough]];
		case BgEnum::none			   : ss << trmc::reset; break;
		case BgEnum::on_grey		   : ss << trmc::on_grey; break;
		case BgEnum::on_red			   : ss << trmc::on_red; break;
		case BgEnum::on_green		   : ss << trmc::on_green; break;
		case BgEnum::on_yellow		   : ss << trmc::on_yellow; break;
		case BgEnum::on_blue		   : ss << trmc::on_blue; break;
		case BgEnum::on_magenta		   : ss << trmc::on_magenta; break;
		case BgEnum::on_cyan		   : ss << trmc::on_cyan; break;
		case BgEnum::on_white		   : ss << trmc::on_white; break;
		case BgEnum::on_bright_grey	   : ss << trmc::on_bright_grey; break;
		case BgEnum::on_bright_red	   : ss << trmc::on_bright_red; break;
		case BgEnum::on_bright_green   : ss << trmc::on_bright_green; break;
		case BgEnum::on_bright_yellow  : ss << trmc::on_bright_yellow; break;
		case BgEnum::on_bright_blue	   : ss << trmc::on_bright_blue; break;
		case BgEnum::on_bright_magenta : ss << trmc::on_bright_magenta; break;
		case BgEnum::on_bright_cyan	   : ss << trmc::on_bright_cyan; break;
		case BgEnum::on_bright_white   : ss << trmc::on_bright_white; break;

#undef trmc

		default :
			{
				const char *func = __func__;
				static str	err;
				err = "Error at: \nfunction: " + *func;
				err + "In line: " + std::to_string(__LINE__) += '\n';
				return errOstr_ostrDefaultCase(err);
			}
	};

	return std::ostream(ss.rdbuf());
}

str Colors::strEnumToText(const ColorEnum &color) {
	switch (color) {
		case ColorEnum::none :
			{
				const static str &none {"none"};
				return none;
			}

		case ColorEnum::reset :
			{
				const static str &reset {"reset"};
				return reset;
			}
		case ColorEnum::grey :
			{
				const static str &grey {"grey"};
				return grey;
			}
		case ColorEnum::red :
			{
				const static str &red {"red"};
				return red;
			}
		case ColorEnum::green :
			{
				const static str &green {"green"};
				return green;
			}
		case ColorEnum::yellow :
			{
				const static str &yellow {"yellow"};
				return yellow;
			}
		case ColorEnum::blue :
			{
				const static str &blue {"blue"};
				return blue;
			}
		case ColorEnum::magenta :
			{
				const static str &magenta {"magenta"};
				return magenta;
			}
		case ColorEnum::cyan :
			{
				const static str &cyan {"cyan"};
				return cyan;
			}
		case ColorEnum::white :
			{
				const static str &white {"white"};
				return white;
			}
		case ColorEnum::bright_grey :
			{
				const static str &bright_grey {"bright_grey"};
				return bright_grey;
			}
		case ColorEnum::bright_red :
			{
				const static str &bright_red {"bright_red"};
				return bright_red;
			}
		case ColorEnum::bright_green :
			{
				const static str &bright_green {"bright_green"};
				return bright_green;
			}
		case ColorEnum::bright_yellow :
			{
				const static str &bright_yellow {"bright_yellow"};
				return bright_yellow;
			}
		case ColorEnum::bright_blue :
			{
				const static str &bright_blue {"bright_blue"};
				return bright_blue;
			}
		case ColorEnum::bright_magenta :
			{
				const static str &bright_magenta {"bright_magenta"};
				return bright_magenta;
			}
		case ColorEnum::bright_cyan :
			{
				const static str &bright_cyan {"bright_cyan"};
				return bright_cyan;
			}
		case ColorEnum::bright_white :
			{
				const static str &bright_white {"bright_white"};
				return bright_white;
			}

		default :
			{
				const char *func = __func__;
				static str	err;
				err = "Error at: \nfunction: " + *func;
				err + "In line: " + std::to_string(__LINE__) += '\n';
				return errStr_strDefaultCase(err);
			}
	}
}

str Colors::strEnumToText(const BackgroundColorEnum &color) {
	switch (color) {
		case BackgroundColorEnum::reset : [[fallthrough]];

		case BackgroundColorEnum::none :
			{
				const str &none {"none"};
				return none;
			}

		case BackgroundColorEnum::on_grey :
			{
				const static str &on_grey {"on_grey"};
				return on_grey;
			}

		case BackgroundColorEnum::on_red :
			{
				const static str &on_red {"on_red"};
				return on_red;
			}

		case BackgroundColorEnum::on_green :
			{
				const static str &on_green {"on_green"};
				return on_green;
			}

		case BackgroundColorEnum::on_yellow :
			{
				const static str &on_yellow {"on_yellow"};
				return on_yellow;
			}

		case BackgroundColorEnum::on_blue :
			{
				const static str &on_blue {"on_blue"};
				return on_blue;
			}

		case BackgroundColorEnum::on_magenta :
			{
				const static str &on_magenta {"on_magenta"};
				return on_magenta;
			}

		case BackgroundColorEnum::on_cyan :
			{
				const static str &on_cyan {"on_cyan"};
				return on_cyan;
			}

		case BackgroundColorEnum::on_white :
			{
				const static str &on_white {"on_white"};
				return on_white;
			}

		case BackgroundColorEnum::on_bright_grey :
			{
				const static str &on_bright_grey {"on_bright_grey"};
				return on_bright_grey;
			}

		case BackgroundColorEnum::on_bright_red :
			{
				const static str &on_bright_red {"on_bright_red"};
				return on_bright_red;
			}

		case BackgroundColorEnum::on_bright_green :
			{
				const static str &on_bright_green {"on_bright_green"};
				return on_bright_green;
			}

		case BackgroundColorEnum::on_bright_yellow :
			{
				const static str &on_bright_yellow {"on_bright_yellow"};
				return on_bright_yellow;
			}

		case BackgroundColorEnum::on_bright_blue :
			{
				const static str &on_bright_blue {"on_bright_blue"};
				return on_bright_blue;
			}

		case BackgroundColorEnum::on_bright_magenta :
			{
				const static str &on_bright_magenta {"on_bright_magenta"};
				return on_bright_magenta;
			}

		case BackgroundColorEnum::on_bright_cyan :
			{
				const static str &on_bright_cyan {"on_bright_cyan"};
				return on_bright_cyan;
			}

		case BackgroundColorEnum::on_bright_white :
			{
				const static str &on_bright_white {"on_bright_white"};
				return on_bright_white;
			}

		default :
			{
				const char *func = __func__;
				static str	err;
				err = "Error at: \nfunction: " + *func;
				err + "In line: " + std::to_string(__LINE__) += '\n';
				return errStr_strDefaultCase(err);
			}
	}
}
str Colors::errStr_strDefaultCase() {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print("Invalid color\n");
	const static str &none = "none";
	return none;
}

str Colors::errStr_strDefaultCase(const str &msg) {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print(msg);
	const str &none("none");
	return none;
}

std::ostream Colors::errOstr_ostrDefaultCase() {
	__debugbreak();
	SetClassColor(ColorEnum::reset);
	StaticError::Print("Invalid color\n");
	const static std::ostream &none = std::cout << "Invalid color";
	return std::ostream(none.rdbuf());
}

std::ostream Colors::errOstr_ostrDefaultCase(const str &msg) {

	__debugbreak();

	// undone
	SetClassColor(ColorEnum::reset);
	StaticError::Print(msg);
	std::stringstream none {};
	none << msg;
	return std::ostream(none.rdbuf());
}

void Colors::Initializer() noexcept {

	color				= ColorEnum::none;
	backgroundColor		= BackgroundColorEnum::none;
	ColorReturnStr		= str();
	BackgroundReturnStr = str();
	isLocalized			= false;
	InitializerCalled	= true;
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
