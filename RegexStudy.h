
// RegexStudy.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#pragma comment (lib, "version.lib")

///////////////////////////////////////////////////////////////////////////////////////////////////
// Regex 라이브러리는 UNICIDE와 ANSI로 구분되어 있으며, 프로젝트가 UNICODE인지 MBCS인지에 따라서
// 구분되지 않음. 동일한 코드로 Regex를 사용하기 위함.
// regex_iterator (for char and wchar_t)			--> _tcregex_iterator
// regex_iterator (for string and wstring)			--> _tsregex_iterator
// regex_token_iterator (for char and wchar_t)		--> _tcregex_token_iterator
// regex_token_iterator (for string and wstring)	--> _tsregex_token_iterator
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <regex>
#include <vector>
#include <iostream>
#include <string>

#ifdef _UNICODE
typedef wchar_t _tchar;
typedef std::wstring _tstring;
typedef std::wregex _tregex;
typedef std::wcmatch _tmatch;
typedef std::wsmatch _tsmatch;
#else
typedef char _tchar;
typedef std::string _tstring;
typedef std::regex _tregex;
typedef std::cmatch _tmatch;
typedef std::smatch _tsmatch;
#endif

typedef std::regex_iterator<const char*> cregex_iterator;
typedef std::regex_iterator<const wchar_t*> wcregex_iterator;
typedef std::regex_iterator<std::string::const_iterator> sregex_iterator;
typedef std::regex_iterator<std::wstring::const_iterator> wsregex_iterator;

#ifdef _UNICODE
typedef wcregex_iterator _tcregex_iterator;
typedef wsregex_iterator _tsregex_iterator;
#else
typedef cregex_iterator _tcregex_iterator;
typedef sregex_iterator _tsregex_iterator;
#endif

typedef std::regex_token_iterator<const char*> cregex_token_iterator;
typedef std::regex_token_iterator<const wchar_t*> wcregex_token_iterator;
typedef std::regex_token_iterator<std::string::const_iterator> sregex_token_iterator;
typedef std::regex_token_iterator<std::wstring::const_iterator> wsregex_token_iterator;

#ifdef _UNICODE
typedef wcregex_token_iterator _tcregex_token_iterator;
typedef wsregex_token_iterator _tsregex_token_iterator;
#else
typedef cregex_token_iterator _tcregex_token_iterator;
typedef sregex_token_iterator _tsregex_token_iterator;
#endif

#define CRLF		_T("\r\n")
#define FONTFACE	_T("Microsoft YaHei")

///////////////////////////////////////////////////////////////////////////////////////////////////
// String Conversion MACRO (MFC CString/std::string/std::wstring each others)
///////////////////////////////////////////////////////////////////////////////////////////////////
// std::string <-- CString
inline std::string CStringToStdStr(CString in) { return std::string(CT2CA(in.operator LPCWSTR())); }
// std::wstring <-- CString
inline std::wstring CStringToStdWStr(CString in) { return std::wstring(in.operator LPCWSTR()); }
// CString <-- std::string
inline CString StdStrToCString(std::string in) { return CString::CStringT(CA2CT(in.c_str())); }
// CString <-- std::wstring
inline CString StdWStrToCString(std::wstring in) { return CString::CStringT(in.c_str()); }
// std::wstring <-- std::string
inline std::wstring StdStrToStdWStr(std::string in) { return std::wstring(CA2CT(in.c_str())); }
// std::string <-- std::wstring
inline std::string StdWStrToStdStr(std::wstring in) { return std::string(CT2CA(in.c_str())); }


///////////////////////////////////////////////////////////////////////////////////////////////////
#include "resource.h"		// main symbols

#ifndef UTILITY_COLOR
#define UTILITY_COLOR
// These are some basic colors
#define COLOR_BLACK5			(RGB(240, 240, 240))
#define COLOR_BLACK10			(RGB(230, 230, 230))
#define COLOR_BLACK20			(RGB(204, 204, 204))
#define COLOR_BLACK30			(RGB(179, 179, 179))
#define COLOR_BLACK40			(RGB(153, 153, 153))
#define COLOR_BLACK50			(RGB(128, 128, 128))
#define COLOR_BLACK60			(RGB(102, 102, 102))
#define COLOR_BLACK70			(RGB( 76,  76,  76))
#define COLOR_BLACK80			(RGB( 51,  51,  51))
#define COLOR_BLACK90			(RGB( 25,  25,  25))
#define COLOR_ARMY_GREEN		(RGB(102, 153, 102))
#define COLOR_AUTUMN_ORANGE		(RGB(255, 102,  51))
#define COLOR_AVOCADO_GREEN		(RGB(102, 153,  51))
#define COLOR_BABY_BLUE			(RGB(102, 153, 255))
#define COLOR_BANANA_YELLOW		(RGB(204, 204,  51))
#define COLOR_BLACK				(RGB(  0,   0,   0))
#define COLOR_BLUE				(RGB(  0,   0, 255))
#define COLOR_BLUE_PURPLE		(RGB(153,   0, 255))
#define COLOR_BLUE_VIOLET		(RGB(153, 102, 255))
#define COLOR_BRICK_RED			(RGB(204,  51,   0))
#define COLOR_BROWN				(RGB(153, 102,  51))
#define COLOR_LIGHT_BROWN		(RGB(128, 128,   0))
#define COLOR_CHALK				(RGB(255, 255, 153))
#define COLOR_CHARTREUSE2		(RGB(153, 255,   0))
#define COLOR_CRIMSON			(RGB(153,  51, 102))
#define COLOR_CYAN				(RGB(  0, 255, 255))
#define COLOR_DARK_BROWN		(RGB(102,  51,  51))
#define COLOR_DARK_GREEN2		(RGB(  0,  51,  51))
#define COLOR_DEEP_AZURE		(RGB(102,  51, 255))
#define COLOR_DEEP_BLUE			(RGB( 51,   0, 204))
#define COLOR_DEEP_NAVY_BLUE 	(RGB(  0,   0, 102))
#define COLOR_DEEP_PINK			(RGB(255, 102, 153))
#define COLOR_DEEP_PURPLE		(RGB( 51,   0, 102))
#define COLOR_DEEP_RIVER		(RGB(102,   0, 204))
#define COLOR_DEEP_ROSE			(RGB(204,  51, 153))
#define COLOR_DEEP_VIOLET		(RGB(153,   0, 153))
#define COLOR_DEEP_YELLOW		(RGB(255, 204,   0))
#define COLOR_DESERT_BLUE		(RGB( 51, 102, 153))
#define COLOR_DULL_GREEN		(RGB(153, 204, 102))
#define COLOR_DUSTY_PLUM		(RGB(153, 102, 153))
#define COLOR_DUSTY_ROSE		(RGB(204, 102, 153))
#define COLOR_EASTER_PURPLE		(RGB(204, 153, 255))
#define COLOR_ELECTRIC_BLUE		(RGB(102, 102, 255))
#define COLOR_FADED_GREEN		(RGB(153, 204, 153))
#define COLOR_FADED_PINK		(RGB(255, 204, 204))
#define COLOR_FOREST_GREEN		(RGB(  0, 102,  51))
#define COLOR_GHOST_GREEN		(RGB(204, 255, 204))
#define COLOR_GOLD				(RGB(204, 153,  51))
#define COLOR_GRAPE				(RGB(102,  51, 153))
#define COLOR_GRASS_GREEN		(RGB(  0, 153,  51))
#define COLOR_GREEN				(RGB(  0, 255,   0))
#define COLOR_HOT_PINK			(RGB(255,  51, 153))
#define COLOR_ICE_BLUE			(RGB(153, 255, 255))
#define COLOR_KENTUCKY_GREEN 	(RGB( 51, 153, 102))
#define COLOR_KHAKI				(RGB(153, 153, 102))
#define COLOR_LIGHT_BLUE_GREEN	(RGB(153, 204, 204))
#define COLOR_LIGHT_GREEN		(RGB( 51, 204, 102))
#define COLOR_LIME_LIGHT		(RGB(181, 230,  29))
#define COLOR_LIGHT_ORANGE		(RGB(255, 153,  51))
#define COLOR_LIGHT_PURPLE		(RGB(204, 102, 255))
#define COLOR_LIGHT_VIOLET		(RGB(255, 153, 255))
#define COLOR_LIGHT_YELLOW		(RGB(255, 255, 102))
#define COLOR_MAGENTA			(RGB(255,   0, 255))
#define COLOR_MAJESTIC_PURPLE	(RGB(153,  51, 204))
#define COLOR_MARTIAN_GREEN		(RGB(153, 204,  51))
#define COLOR_MINT_GREEN		(RGB(153, 255, 153))
#define COLOR_MOON_GREEN		(RGB(204, 255, 102))
#define COLOR_MOSS_GREEN		(RGB( 51, 102, 102))
#define COLOR_MURKY_GREEN		(RGB( 51,  51,   0))
#define COLOR_NAVY_BLUE			(RGB(  0,  51, 153))
#define COLOR_NEON_PURPLE		(RGB(204,  51, 255))
#define COLOR_NEON_RED			(RGB(255,   0, 102))
#define COLOR_OCEAN_GREEN		(RGB(102, 153, 153))
#define COLOR_OLIVE				(RGB(153, 153,  51))
#define COLOR_OLIVE_DRAB		(RGB(102, 102,  51))
#define COLOR_ORANGE 			(RGB(255, 102,   0))
#define COLOR_PALE_PURPLE		(RGB(204, 153, 204))
#define COLOR_PALE_YELLOW		(RGB(255, 255, 204))
#define COLOR_PASTEL_BLUE		(RGB(153, 153, 255))
#define COLOR_STEEL_BLUE		(RGB( 70, 130, 180))
#define COLOR_ROYAL_BLUE		(RGB( 65, 105, 255))
#define COLOR_CORNFLOWER_BLUE	(RGB(100, 149, 237))
#define COLOR_PEACH				(RGB(255, 153, 102))
#define COLOR_PINK				(RGB(255, 153, 204))
#define COLOR_PLUM				(RGB(102,   0, 102))
#define COLOR_POWDER_BLUE		(RGB(204, 204, 255))
#define COLOR_PURPLE 			(RGB(153,   0, 204))
#define COLOR_RED				(RGB(255,   0,   0))
#define COLOR_RED_BROWN			(RGB(204, 102,  51))
#define COLOR_REGAL_RED			(RGB(204,  51, 102))
#define COLOR_RUBY_RED			(RGB(153,   0,   0))
#define COLOR_SAND				(RGB(255, 204, 153))
#define COLOR_DARK_RED 			(RGB(128, 0  ,   0))
#define COLOR_DARK_BLUE			(RGB( 44,  67, 110))
#define COLOR_SEA_GREEN			(RGB( 51, 204, 153))
#define COLOR_SKY_BLUE			(RGB(  0, 204, 255))
#define COLOR_CHART_BLUE		(RGB(  0, 128, 255))
#define COLOR_SOFT_PINK			(RGB(255, 153, 153))
#define COLOR_SPRING_GREEN		(RGB( 51, 204,  51))
#define COLOR_STORM_BLUE		(RGB( 51,   0, 153))
#define COLOR_TROPICAL_PINK		(RGB(255, 102, 102))
#define COLOR_TURQUOISE			(RGB(102, 255, 204))
#define COLOR_TWILIGHT_BLUE		(RGB(102, 102, 204))
#define COLOR_TWILIGHT_VIOLET	(RGB(153, 102, 204))
#define COLOR_VIOLET 			(RGB(204, 102, 204))
#define COLOR_WALNUT 			(RGB(102,  51,   0))
#define COLOR_WHITE				(RGB(255, 255, 255))
#define COLOR_YELLOW 			(RGB(255, 255,   0))

// system like colors
#define COLOR_REAL_LTGRAY 		(RGB(224, 224, 224))
#define COLOR_LTGRAY 			(RGB(192, 192, 192))
#define COLOR_GRAY				(RGB(150, 150, 150))
#define COLOR_DKGRAY 			(RGB(100, 100, 100))
#define COLOR_REAL_DKGRAY		(RGB(128, 128, 128))

// Special control colors.	                 
#define COLOR_STATUSBAR			(RGB(192, 192, 192))
#define COLOR_SELECTED			(RGB(0  , 200,   0))
#define COLOR_FOCUS	   			(RGB(230, 230, 230))
#define COLOR_COMMANDBKG		(RGB(  4,  56,  40))

///////////////////////////////////////////////////////////////////////////////
// 16 COLOR DEFINE
#define COLOR_GRAY_L6			RGB(0xF0,0xF0,0xF0)
#define COLOR_GRAY_L5			RGB(0xE0,0xE0,0xE0)
#define COLOR_GRAY_L4			RGB(0xD0,0xD0,0xD0)
#define COLOR_BTN_DEFAULT		RGB(0xEC,0xE9,0xD8)
#define COLOR_SILVER			RGB(0xC0,0xC0,0xC0)
#define COLOR_GRAY_L3			RGB(0xC0,0xC0,0xC0)
#define COLOR_GRAY_L2			RGB(0xA0,0xA0,0xA0)
#define COLOR_GRAY0				RGB(0x80,0x80,0x80)
#define COLOR_GRAY1				RGB(0x60,0x60,0x60)
#define COLOR_GRAY2				RGB(0x40,0x40,0x40)
#define COLOR_GRAY3				RGB(0x30,0x30,0x30)
#define COLOR_GRAY4				RGB(0x20,0x20,0x20)
#define COLOR_GRAY5				RGB(0x10,0x10,0x10)
#define COLOR_MAROON			RGB(0x80,0x00,0x00)
#define COLOR_LIME				RGB(0x00,0xFF,0x00)
#define COLOR_AQUA 				RGB(0x00,0xFF,0xFF)
#define COLOR_AQUA2				RGB(0x00,0xC0,0xC0)
#define COLOR_TEAL 				RGB(0x00,0x80,0x80)
#define COLOR_NAVY 				RGB(0x00,0x00,0x80)
#define COLOR_YELLOW_LIGHT		RGB(0xFF,0xFF,0xE0)
#define COLOR_AQUA_LIGHT		RGB(0xE0,0xFF,0xFF)
#define COLOR_PINK_LIGHT		RGB(0xFF,0xE0,0xFF)
#define COLOR_AQUA_LIGHT2		RGB(0xC0,0xFF,0xFF)
#define COLOR_CHARTREUSE		RGB(0x00,0x7F,0xFF)
#define COLOR_DARK_GREEN		RGB(0x00,0x7F,0x00)
#define COLOR_LIGHT_GRAY		RGB(0x77,0x88,0x99)
#define COLOR_SLATE_GRAY		RGB(0x70,0x80,0x90)
#define COLOR_DARK_SLATE_GRAY	RGB(0x2F,0x4F,0x4F)
#define DLG_BKG_COLOR			COLOR_CORNFLOWER_BLUE

///////////////////////////////////////////////////////////////////////////////
// default 16 color of plot graph
static COLORREF gPlotColor[] =
{
	COLOR_RED,
	COLOR_BLUE,
	COLOR_DARK_GREEN,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_CYAN,
	COLOR_DEEP_PURPLE,
	COLOR_DEEP_YELLOW,
	COLOR_ELECTRIC_BLUE,
	COLOR_VIOLET,
	COLOR_FADED_GREEN,
	COLOR_HOT_PINK,
	COLOR_MARTIAN_GREEN,
	COLOR_NAVY_BLUE,
	COLOR_ORANGE,
	COLOR_WHITE,
};

#define DARKTHEME_BKG_BLACK1		RGB(0x18,0x18,0x18)
#define DARKTHEME_BKG_BLACK2		RGB(0x1f,0x1f,0x1f)
#define DARKTHEME_TXT				RGB(0xE8,0xEA,0xF6)

#endif //UTILITY_COLOR

#define GETAPP()			(static_cast<CRegexStudyApp*>(AfxGetApp()))
#//define GETFRM()			(static_cast<CMainFrame*>(AfxGetMainWnd()))
//#define GETVIEW()			(static_cast<CSim3DView*>(GETFRM()->GetActiveView()))
//#define printlog(s1)		(GETFRM()->PRINTLOG(s1))
//#define printlog2(s1,s2)	(GETFRM()->PRINTLOG2(s1,s2))


class CRegexStudyApp : public CWinApp
{
public:
	CString		m_sApplicationInfo[7];
	bool		GetApplicationInfo();
	CString		GetVsVersionInfo(CString sKey);

public:
	CRegexStudyApp();
	BOOL ExtractBinFileFromResource(HANDLE hFile, CString sResFolder, int nID);
	CString		m_sModulePath;
	void		GETMODULEPATH();
	CString		READ_UNICODE_FILE(CString sFileName);
	bool		IsUTF8(const void* pBuffer, long size);
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRegexStudyApp theApp;
