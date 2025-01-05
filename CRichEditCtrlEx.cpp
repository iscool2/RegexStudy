#include "pch.h"
#include "CRichEditCtrlEx.h"

void CRichEditCtrlEx::TxtColor(COLORREF clr)
{
	m_TxtColor = clr;
	CHARFORMAT2 cf;
	::ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = m_TxtColor;
	cf.dwEffects = 0;

	CString txt;
	int txtLen = GetTextLength();
	GetTextRange(0, txtLen, txt);
	SetSel(0, txtLen);
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cf);	SetSel(0, 0); //free selection
}

void CRichEditCtrlEx::TxtBackColor(COLORREF clr)
{
	m_BkgColor = clr;
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_BACKCOLOR;
	cf.crBackColor = m_BkgColor;
	cf.dwEffects = 0;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void CRichEditCtrlEx::SectionBkColor(long nStartChar, long nEndChar, COLORREF crBackColor)
{
	CHARFORMAT2 cf;
	::ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_BACKCOLOR;
	cf.crBackColor = crBackColor;
	SetSel(nStartChar, nEndChar);
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cf);
	SetSel(0, 0); //free selection
}

void CRichEditCtrlEx::TxtBold()
{
	CHARFORMAT boldfont;
	boldfont.cbSize = sizeof(CHARFORMAT);
	boldfont.dwMask = CFM_BOLD;
	boldfont.dwEffects = CFE_BOLD;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&boldfont);
}

void CRichEditCtrlEx::TxtUnderlined()
{
	CHARFORMAT2 underlinedfont;
	underlinedfont.cbSize = sizeof(CHARFORMAT);
	underlinedfont.dwMask = CFM_UNDERLINE;
	underlinedfont.dwEffects = CFM_UNDERLINE;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&underlinedfont);
}

void CRichEditCtrlEx::TxtItalic()
{
	CHARFORMAT Kursivfont;
	Kursivfont.cbSize = sizeof(CHARFORMAT);
	Kursivfont.dwMask = CFM_ITALIC;
	Kursivfont.dwEffects = CFM_ITALIC;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&Kursivfont);
}

void CRichEditCtrlEx::TxtStrikeout()
{
	CHARFORMAT underlinedfont;
	underlinedfont.cbSize = sizeof(CHARFORMAT);
	underlinedfont.dwMask = CFM_STRIKEOUT;
	underlinedfont.dwEffects = CFM_STRIKEOUT;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&underlinedfont);
}

void CRichEditCtrlEx::Subscript()
{
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFE_SUBSCRIPT;
	cf.dwEffects = CFE_SUBSCRIPT;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void CRichEditCtrlEx::Superscript()
{
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_SUPERSCRIPT;
	cf.dwEffects = CFM_SUPERSCRIPT;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void CRichEditCtrlEx::SetTxtFont(TCHAR* Font)
{
	wsprintf(m_FontName, Font);
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof cf);
	cf.cbSize = sizeof cf;
	cf.dwMask = CFM_FACE;
	wsprintf(cf.szFaceName, m_FontName);
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void CRichEditCtrlEx::FontSize(int nPointSize)
{
	m_FontPointSize = abs(nPointSize);
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof cf);
	cf.cbSize = sizeof cf;
	cf.dwMask = CFM_SIZE;
	cf.yHeight = m_FontPointSize * 20;
	LRESULT lresult = SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

/*------------------------------------------------------------------------------------------*/
//	IME Mode Change
//	Note. Back slash의 경우, IME에 따라(;한글/중문/영문 입력 모드) 표시가 달라짐에 주의.
//	dwMode :
//			IME_CMODE_ALPHANUMERIC
//			IME_CMODE_NATIVE
/*------------------------------------------------------------------------------------------*/
void CRichEditCtrlEx::ChangeIMEMode(DWORD dwMode)
{
	HIMC himc = ImmGetContext(this->GetSafeHwnd());
	ImmSetConversionStatus(himc, dwMode, IME_SMODE_CONVERSATION);
	ImmReleaseContext(this->GetSafeHwnd(), himc);
}

void CRichEditCtrlEx::PreSubclassWindow()
{
	SetBackgroundColor(FALSE, m_BkgColor);

	CRichEditCtrl::PreSubclassWindow();
}

void CRichEditCtrlEx::AddText(CString text, COLORREF color, bool bold, bool italic)
{
	CHARFORMAT cf = { 0 };
	int txtLen = GetTextLength();
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_COLOR;
	cf.dwEffects = (bold ? CFE_BOLD : 0) | (italic ? CFE_ITALIC : 0);
	cf.crTextColor = color;
	SetSel(txtLen, -1); // Set the cursor to the end of the text area and deselect everything.
	ReplaceSel(text); // Inserts when nothing is selected.
	// Apply formating to the just inserted text.
	SetSel(txtLen, GetTextLength());
	SetSelectionCharFormat(cf);
}

void CRichEditCtrlEx::TextOut(LPCTSTR text, COLORREF color, bool bold, bool italic)
{
	// 마지막 행으로 이동하기
	int first_pos = LineIndex(GetLineCount());
	SetSel(first_pos, first_pos);
	CPoint point;
	point = PosFromChar(first_pos);
	SetCaretPos(point);
	SetFocus();

	// 문자출력
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_COLOR;
	cf.dwEffects = (bold ? CFE_BOLD : 0) | (italic ? CFE_ITALIC : 0);
	cf.crTextColor = color;
	SetSelectionCharFormat(cf);
	ReplaceSel(text);
}

void CRichEditCtrlEx::Init(TCHAR* Font, int fontSize, COLORREF color)
{
	//set font face
	wsprintf(m_FontName, Font);
	//set font size
	m_FontPointSize = abs(fontSize);

	CHARFORMAT cf = { 0, };
	PARAFORMAT pf = { 0, };
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
	cf.dwEffects = CFE_BOLD | CFM_ITALIC;
	cf.yHeight = m_FontPointSize * 20;
	cf.crTextColor = color;
	cf.bCharSet = DEFAULT_CHARSET;
	cf.bPitchAndFamily = FF_SWISS;
	lstrcpy(cf.szFaceName, m_FontName);
	SetSel(0, GetTextLength());
	SetSelectionCharFormat(cf);
	pf.cbSize = sizeof(pf);
	pf.dwMask = PFM_ALIGNMENT;
	SetSel(0, GetTextLength());
	SetParaFormat(pf);
}

void CRichEditCtrlEx::MarkText(int nStart, int nEnd, COLORREF color)
{
	CHARFORMAT cf = { 0, };
	PARAFORMAT pf = { 0, };
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
	cf.dwEffects = CFE_BOLD | CFM_ITALIC;
	cf.yHeight = m_FontPointSize * 20;
	cf.crTextColor = color;
	cf.bCharSet = DEFAULT_CHARSET;
	cf.bPitchAndFamily = FF_SWISS;
	lstrcpy(cf.szFaceName, m_FontName);
	SetSel(nStart, nEnd);
	SetSelectionCharFormat(cf);
}
