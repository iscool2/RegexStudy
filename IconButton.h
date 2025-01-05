/**
@file IconButton.h
@brief Class header file.
@author The Next System
@date January 1, 2012
@version 1.00
*/
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                              Copyright (c) 2012
//                  The Next System - SEOUL, REPUBLIC OF KOREA
//                         mailto: iscool2@gmail.com
//
// This program is the property of the The Next System. and it shall not be reproduced, 
// distributed or used without permission of an authorized Company official. 
// This is an unpublished work subject to Trade Secret and Copyright protection.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
const int TIPBGRCOLOR = RGB ( 255, 255, 0 );
/**
@class CIconButton
@brief UI class to enable the use of icon images for MFC standard CButton.
*/
class CIconButton : public CButton
{
public:
	CIconButton();
	virtual ~CIconButton();

	void SetItalic ( bool bVal = true )				{ m_TextMetrics.tmItalic = bVal; NewFont(); };
	void SetUnderline ( bool bVal = true )			{ m_TextMetrics.tmUnderlined = bVal; NewFont(); };
	void SetStrikeOut ( bool bVal = true )			{ m_TextMetrics.tmStruckOut = bVal; NewFont(); };
	void SetFaceName ( const CString &sVal )		{ m_sFaceName = sVal; NewFont (); };
	void SetWeight ( const int nVal )				{ m_TextMetrics.tmWeight = nVal; NewFont(); };
	void SetHeight ( const int nVal)				{ m_TextMetrics.tmHeight = nVal; NewFont(); };
	void SetWidth ( const int nVal)					{ m_TextMetrics.tmMaxCharWidth = nVal; NewFont(); };
	
	void SetIconOnID ( const UINT nID )				{ m_nIconOnID = nID; m_bOnState = TRUE; InvalidateRect(NULL); };		//ytlim. changed
	void SetIconOffID ( const UINT nID )			{ m_nIconOffID = nID; m_bOnState = FALSE; InvalidateRect(NULL); };	    //ytlim. changed 
	void SetTextColor ( const COLORREF color )		{ m_nColor = color; };
	void SetIconSize ( const int x, const int y )	{ m_nIcon.cx = x; m_nIcon.cy = y; };
	void SetIconRight ( bool bVal = true )			{ m_bIconRight = bVal; };
	void Disable ( void );
	void Enable ( void );
	void SetState(BOOL bState)                      { if (bState) SetIconOnID(m_nIconOnID); else SetIconOffID(m_nIconOffID);  m_bOnState = bState; }	 //ytlim. changed
	BOOL GetState (void)							{ return m_bOnState; }							 //ytlim. added
	void SetFlat(BOOL bEnable)						{ m_bFlatDraw = bEnable; }						 //ytlim. added

	void SetTipText ( const CString &sTxt )			{ m_sTip = sTxt; m_bWithTip = true; };
	void SetFocusedRectDraw(BOOL bEnable)			{ m_bFocusedRectDraw = bEnable; }

	//{{AFX_VIRTUAL(CIconButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL


protected:
	//{{AFX_MSG(CIconButton)
	afx_msg LRESULT  OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	 //ytlim. added
	virtual void PreSubclassWindow();						 //ytlim. added
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	void	NewFont ( void );
	int		DelAmpersand ( CString &sTxt );
	void	HideTip ( void );
	void	ShowTip ( void );
	void	GetCurrentTextMetric ( void );
	void	DrawTipBoxAndText ( void );
	bool	RestoreBitmap ( void );
	bool	SaveBitmap ( void );
	//
	bool			m_bIconLeft;
	bool			m_bIconRight;
	TEXTMETRIC		m_TextMetrics;
	CSize			m_nIcon;
	UINT			m_nIconOnID;	//icon id for Enabled. ytlim. changed
	UINT			m_nIconOffID;	//icon id for Disabled. ytlim. added	
	COLORREF		m_nColor;
	CFont			m_fnt;
	CString			m_sFaceName;
	//
	bool			m_bWithTip;
	bool			m_bTipIsOpen;
	CString			m_sTip;
	CSize			m_TipDim;
	CPoint			m_TipPos;
	CRect			m_TipRect;
	HBITMAP			m_hMemBmp;
	HDC				m_hMemDC;
	HDC				m_hOwnerDC;
	BOOL			m_bOnState;
	BOOL			m_bFocusedRectDraw; //ytlim. added
	BOOL			m_bFlatDraw;		//ytlim. added
};
