#pragma once

#include "MyTypes.hpp"

#include <iosfwd>
#include <memory>

namespace My {

enum class ColorEnum {

	none,
	reset,
	grey,
	red,
	green,
	yellow,
	blue,
	magenta,
	cyan,
	white,
	bright_grey,
	bright_red,
	bright_green,
	bright_yellow,
	bright_blue,
	bright_magenta,
	bright_cyan,
	bright_white
};

enum class BackgroundColorEnum {

	none,
	reset,
	on_grey,
	on_red,
	on_green,
	on_yellow,
	on_blue,
	on_magenta,
	on_cyan,
	on_white,
	on_bright_grey,
	on_bright_red,
	on_bright_green,
	on_bright_yellow,
	on_bright_blue,
	on_bright_magenta,
	on_bright_cyan,
	on_bright_white
};

using CEnum = ColorEnum;
using BgEnum = BackgroundColorEnum;

class Colors;
class StaticColors;

class Colors {
	
public:
	// Default constructor
	Colors() noexcept;

	// Constructor with ColorEnum and BackgroundColorEnum
	Colors(const ColorEnum&			  color,
		   const BackgroundColorEnum& BackgroundColor) noexcept;

	// Constructor with ColorEnum and BackgroundColorEnum as strings
	Colors(const str& ColorReturn,
		   const str& BackgroundReturn) noexcept;

	// copy constructor
	Colors(const Colors& c) noexcept;
	// copy pointer constructor
	Colors(const Colors* ptr) noexcept;
	// copy constructor with unique_ptr
	Colors(const class std::unique_ptr<Colors>& ptr) noexcept;
	// copy constructor with shared_ptr
	Colors(const class std::shared_ptr<Colors>& ptr) noexcept;

protected:
	CEnum  color;
	BgEnum backgroundColor;
	str	   ColorReturnStr;
	str	   BackgroundReturnStr;
	bool   isLocalized;
	bool   InitializerCalled = false;

public:
	// Add a constructor that accepts an int
	const void SetClassColor(const ColorEnum& color) noexcept;
	const void SetClassColor(const str& Txt);
	const void
	SetClassBackgroundColor(const BackgroundColorEnum& BackgroundColor);
	const void SetClassBackgroundColor(const str& BackgroundColor);
	const void SetLocale(const bool& locale) noexcept;

	const CEnum&  EnumGetColor() const noexcept;
	const BgEnum& EnumGetBackgroundColor() const noexcept;

	const bool& bGetLocale() const;
	const bool& bCheckColorExists(const str& Color);
	const bool& bCheckBackgroundExists(const str& BackgroundColor);

	const CEnum&  ColorEnum_CheckColorExists(const str& Color);
	const CEnum&  bCheckColorExistsReturnColorEnum(const ColorEnum& Color);
	const BgEnum& enumBG_CheckBgColorExists(const str& BgColor);
	const BgEnum& enumBG_CheckBgColorExists(const BgEnum& BgColor);

	const str& StrGetColor() const noexcept;
	const str& strCheckColorExists(const str& Color);
	const str& StrGetColor(const Colors& C);
	const str& StrGetBackgroundColor() const noexcept;
	const str& StrGetBackgroundColor(const Colors& c);
	const str& strCheckBackgroundExists(const str& BackgroundColor);

private:
	int buffer;
	Colors(int i) noexcept : Colors() { buffer = i; }

	const void Initializer();

	const str& errStr_strDefaultCase();
	const str& errStr_strDefaultCase(const str& msg);

	const std::ostream& errOstr_ostrDefaultCase();
	const std::ostream& errOstr_ostrDefaultCase(const str& msg);

protected:
	const bool bHasColor(const ColorEnum& color) noexcept;
	const bool bHasColor(const BackgroundColorEnum& color) noexcept;
	const bool bHasColor() const noexcept;
	const bool bHasBackgroundColor() const;

	const bool bCheckInvalidColor(const ColorEnum& color) noexcept;
	const bool bCheckInvalidColor(const BackgroundColorEnum& color) noexcept;

	const ColorEnum& StringToColorEnum(const str& color);
	const BackgroundColorEnum&
	StringToBackgroundColorEnum(const str& color);

	const std::ostream& ostrColorEnumToOstream(const ColorEnum& color);
	const std::ostream&
	ostrBackgroundEnumToOstream(const BackgroundColorEnum& color);

	const str& strEnumToText(const ColorEnum& color);
	const str& strEnumToText(const BackgroundColorEnum& color);

	const str& strEnumToStream(const ColorEnum& color);
	const str& strEnumToStream(const BackgroundColorEnum& color);

	const bool bISClassEmpty() noexcept;
	const bool bISClassEmpty(const Colors& c) noexcept;

public:
	const void ResetColor();
	const void ResetBackgroundColor() noexcept;

	const std::ostream&
	Print(const str& msg, const ColorEnum& color = ColorEnum::reset);

	const str& UseColor(const ColorEnum& color);

	const str& UseColor(const BackgroundColorEnum& color);

	const str& UseBackgroundColor(const BackgroundColorEnum& color);

	const Colors GetColors() const noexcept;

	const Colors* ColorsPtr() const noexcept;

	virtual const Colors GetColors(const Colors& reference) noexcept;

	const Colors GetColors(const str& ColorReturn,
						   const str& BackgroundReturn) noexcept;

	const Colors* ColorsPtr(const str& ColorReturn,
							const str& BackgroundReturn) noexcept;

	const Colors GetColors(const ColorEnum&			  color,
						   const BackgroundColorEnum& BackgroundColor) noexcept;

	const Colors*
	GetColorsPtr(ColorEnum& color, const BackgroundColorEnum& BackgroundColor);

	const Colors*
	GetColorsPtr(const ColorEnum&			color,
				 const BackgroundColorEnum& BackgroundColor) noexcept;

	const Colors* GetColorsPtr(const Colors& reference) noexcept;

	const Colors* GetColorsPtr(const Colors* Val) noexcept;

	const Colors GetColors(std::unique_ptr<Colors>& ptr) noexcept;

	const Colors* GetColorsPtr(std::unique_ptr<Colors>& ptr) noexcept;

	const Colors GetColors(std::shared_ptr<Colors>& ptr) noexcept;

	const Colors* GetColorsPtr(std::shared_ptr<Colors>& ptr) noexcept;

	const Colors* GetColorsPtr(const str& ColorReturn,
							   const str& BackgroundReturn);

	const str& strEnumToTxt(const ColorEnum& color);

	const str& strEnumToTxt(const BackgroundColorEnum& BackgroundColor);

	Colors& operator=(const Colors& other);

	~Colors();
};

} // namespace My