#pragma once
#include <afxcmn.h>

#include <imm.h>
#pragma comment(lib, "imm32.lib")

#ifndef FONTFACE
#define FONTFACE	_T("Microsoft YaHei")
#endif

class CRichEditCtrlEx : public CRichEditCtrl
{
public:
	COLORREF m_TxtColor, m_BkgColor;

	CRichEditCtrlEx()
	{
		m_BkgColor = RGB(255,255,255);
		m_TxtColor = RGB(0,0,0);
		m_FontPointSize = 10;
		lstrcpy(m_FontName, FONTFACE);
	};

	CRichEditCtrlEx(COLORREF clrBkg, COLORREF clrTxt)
	{
		m_BkgColor = clrBkg;
		m_TxtColor = clrTxt;
	};
	int		m_FontPointSize;
	TCHAR	m_FontName[32];

public:
	void SectionBkColor(long nStartChar, long nEndChar, COLORREF crBackColor);
	void TxtBold();
	void TxtUnderlined();
	void TxtItalic();
	void TxtStrikeout();
	void Subscript();
	void Superscript();
	void SetTxtFont(TCHAR* Font);
	void FontSize(int size);
	void TxtColor(COLORREF clr);
	void TxtBackColor(COLORREF clr);
	void ChangeIMEMode(DWORD dwMode);
	void Init(TCHAR* Font, int fontSize, COLORREF color);
	void TextOut(LPCTSTR text, COLORREF color,bool bold=FALSE, bool italic = FALSE);
	void AddText(CString text, COLORREF color, bool bold = FALSE, bool italic = FALSE);
	void MarkText(int nMarkStart, int nMarkEnd, COLORREF color);

	virtual void PreSubclassWindow();
};

