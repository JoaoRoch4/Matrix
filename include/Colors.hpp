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

using CEnum	 = ColorEnum;
using BgEnum = BackgroundColorEnum;

class Colors;
class StaticColors;

class Colors {

public:

	// Default constructor
	Colors() noexcept;

	// Constructor with ColorEnum and BackgroundColorEnum
	Colors(const ColorEnum			 &color,
		   const BackgroundColorEnum &BackgroundColor) noexcept;

	// Constructor with ColorEnum and BackgroundColorEnum as strings
	Colors(const str &ColorReturn, const str &BackgroundReturn) noexcept;
	// copy constructor
	Colors(const Colors &c) noexcept;
	// copy pointer constructor
	Colors(const Colors *ptr) noexcept;
	// copy constructor with unique_ptr
	Colors(const class std::unique_ptr<Colors> &ptr) noexcept;
	// copy constructor with shared_ptr
	Colors(const class std::shared_ptr<Colors> &ptr) noexcept;

private:

	CEnum  color;
	BgEnum backgroundColor;
	str	   ColorReturnStr;
	str	   BackgroundReturnStr;
	bool   isLocalized;
	bool   InitializerCalled;

public:

	// Add a constructor that accepts an int
	void SetClassColor(const CEnum &Color) noexcept { color = Color; };
	void	 SetClassColor(const str &Txt);
	void	 SetClassBackgroundColor(const BgEnum &BackgroundColor);
	void	 SetClassBackgroundColor(const str &BackgroundColor);
	void	 SetLocale(const bool &locale) noexcept;

	inline CEnum  EnumGetColor() const noexcept { return color; };
	inline BgEnum EnumGetBackgroundColor() const noexcept {
		return backgroundColor;
	}

	bool bGetLocale();

	bool   bCheckColorExists(const str &Color);
	bool   bCheckColorExists(const ColorEnum &Color);
	bool   bCheckBgExists(const BgEnum &BgColor);
	bool   bCheckBgExists(const str &BgColor);

	CEnum  CnumCheckColorExists(const str &Color);
	CEnum  CnumCheckColorExists(const ColorEnum &Color);
	BgEnum BgNumCheckBgColorExists(const str &BgColor);
	BgEnum BgNumCheckBgColorExists(const BgEnum &BgColor);

	str StrGetColor() const noexcept;
	str strCheckColorExists(const str &Color);
	str StrGetColor(const Colors &C);
	str StrGetBackgroundColor() const noexcept;
	str StrGetBackgroundColor(const Colors &c);
	str strCheckBackgroundExists(const str &BackgroundColor);

protected:

	void Initializer() noexcept;

	str errStr_strDefaultCase();
	str errStr_strDefaultCase(const str &msg);

	std::ostream errOstr_ostrDefaultCase();
	std::ostream errOstr_ostrDefaultCase(const str &msg);

	bool bHasColor(const ColorEnum &color) noexcept;
	bool bHasBgColor(const BackgroundColorEnum &BgColor) noexcept;
	bool bHasColor() const noexcept;
	bool bHasBackgroundColor() const;

	bool bCheckInvalidColor(const ColorEnum &color) noexcept;
	bool bCheckInvalidColor(const BackgroundColorEnum &color) noexcept;

	CEnum  StrToCnum(const str &color);
	BgEnum StringToBgEnum(const str &BgColor);

	std::ostream ostrColorEnumToOstream(const ColorEnum &color);
	std::ostream ostrBackgroundEnumToOstream(
		const BackgroundColorEnum &BgColor);

	str strEnumToText(const ColorEnum &color);
	str strEnumToText(const BackgroundColorEnum &color);

	std::ostream strEnumToStream(const ColorEnum &color);
	str strEnumToStream(const BackgroundColorEnum &color);

	bool bISClassEmpty() noexcept;
	bool bISClassEmpty(const Colors &c) noexcept;

public:

	inline void ResetColor() noexcept;
	inline void	ResetBackgroundColor() noexcept;

	void Print(const str &msg,
							  const ColorEnum &color);

	void Print(const ColorEnum &color, const str &msg, ...);
	void Print(const BgEnum &color, const str &msg, ...);

	void PrintColor(const ColorEnum &color);
	void PrintColor(const BgEnum &color);

	void
	PrintMsgColor(const str &msg, const ColorEnum &color, const bool& reset = false);
	void PrintMsgColor(const str &msg, const BgEnum &color, const bool& reset = false);

	str UseColor(const ColorEnum &color);
	str UseColor(const BackgroundColorEnum &color);
	
	str UseBackgroundColor(const BackgroundColorEnum &color);

	const Colors GetColors() const noexcept;

	const Colors *ColorsPtr() const noexcept;

	const Colors GetColors(const Colors &reference) noexcept;

	const Colors GetColors(const str &ColorReturn,
						   const str &BackgroundReturn) noexcept;

	const Colors *ColorsPtr(const str &ColorReturn,
							const str &BackgroundReturn) noexcept;

	const Colors GetColors(const ColorEnum			 &color,
						   const BackgroundColorEnum &BackgroundColor) noexcept;

	const Colors *GetColorsPtr(ColorEnum				 &color,
							   const BackgroundColorEnum &BackgroundColor);

	const Colors *GetColorsPtr(
		const ColorEnum			  &color,
		const BackgroundColorEnum &BackgroundColor) noexcept;

	const Colors *GetColorsPtr(const Colors &reference) noexcept;
	const Colors *GetColorsPtr(const Colors *Val) noexcept;
	const Colors  GetColors(std::unique_ptr<Colors> &ptr) noexcept;
	const Colors *GetColorsPtr(std::unique_ptr<Colors> &ptr) noexcept;
	const Colors  GetColors(std::shared_ptr<Colors> &ptr) noexcept;
	const Colors *GetColorsPtr(std::shared_ptr<Colors> &ptr) noexcept;

	const Colors *GetColorsPtr(const str &ColorReturn,
							   const str &BackgroundReturn);

	str strEnumToTxt(const ColorEnum &color);

	str strEnumToTxt(const BackgroundColorEnum &BackgroundColor);
	Colors	  &operator=(const Colors &other);

	virtual ~Colors();
};

} // namespace My
