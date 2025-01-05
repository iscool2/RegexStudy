/**
@file IconButton.cpp
@brief Class implementation file.
@author The Next System
@date January 1, 2012
@version 1.00
*/
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                              Copyright (c) 2023
//                  The Next System - SEOUL, REPUBLIC OF KOREA
//                         mailto: iscool2@gmail.com
//
// This program is the property of the The Next System. and it shall not be reproduced, 
// distributed or used without permission of an authorized Company official. 
// This is an unpublished work subject to Trade Secret and Copyright protection.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
//#include "stdafx.h"
#include "IconButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
constructor with default settings.
@param None
@return None
*/
CIconButton::CIconButton()
{
	m_fnt.FromHandle ( (HFONT)GetStockObject ( SYSTEM_FONT ) );
	memset ( &m_TextMetrics, 0, sizeof ( TEXTMETRIC ) );
	m_bOnState			= FALSE;
	m_bIconRight		= false;
	m_bFocusedRectDraw	 = FALSE;
	m_bFlatDraw			= TRUE;
	m_nIconOnID			= 0;									// no icon
	m_nIconOffID		= 0;									// no icon
	m_nIcon.cx			= ::GetSystemMetrics ( SM_CXICON );		// systemsize
	m_nIcon.cy			= ::GetSystemMetrics ( SM_CYICON );
	m_nColor			= ::GetSysColor ( COLOR_BTNTEXT );		// systemcolor
	//
	// init for tip
	//
	m_sTip = "";												// no tiptext
	m_bTipIsOpen = false;										// don't show
	m_bWithTip = false;											// no tip
	m_bIconLeft = TRUE; //2024.3.9 ytlim added.
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
destructor.
@param None
@return None
*/
CIconButton::~CIconButton()
{
	m_fnt.DeleteObject(); 
}


BEGIN_MESSAGE_MAP(CIconButton, CButton)
	//{{AFX_MSG_MAP(CIconButton)
	ON_WM_NCHITTEST()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////////////////////////////
/**
자동으로 OnwerDraw 속성주기.
- ytlim added.
@param None
@return None
*/
void CIconButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	// 자동으로 OnwerDraw 속성주기
	ModifyStyle(0, BS_OWNERDRAW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
called by the framework when a visual aspect of an owner-drawn button has changed. 
an owner-drawn button has the bs_ownerdrawn style set.
@param[in] LPDRAWITEMSTRUCT lpDrawItemStruct
@return None
*/
void CIconButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect		rect		= lpDrawItemStruct->rcItem;
	CDC			*pDC		= CDC::FromHandle ( lpDrawItemStruct->hDC );
	UINT		state		= lpDrawItemStruct->itemState;
	UINT		uStyle		= DFCS_BUTTONPUSH;
	bool		bWithStr	= true;
	HICON		hIcon		= NULL;
	int			nHotkeyPos	= 0;
	CString		strText;
	CPoint		TextPos;
	CPoint		RecPos;
	CSize		TextExtent;
	CPen		HighlightPen	( PS_SOLID | PS_COSMETIC, 1, ::GetSysColor ( COLOR_3DHIGHLIGHT ) );
	CPen		DarkShadowPen	( PS_SOLID | PS_COSMETIC, 1, ::GetSysColor ( COLOR_3DDKSHADOW ) );
	int			centerAlignTextoutX = 0;
	//
	ASSERT ( lpDrawItemStruct->CtlType == ODT_BUTTON );
	//
	// first check if tip is open, -> close before other action
	//
	if ( state & ODS_SELECTED ) 
	{
		if ( ( m_bWithTip ) && ( m_bTipIsOpen ) )
		{
			HideTip ();
		}
	}
	//
	if ( lpDrawItemStruct->itemState & ODS_SELECTED )
	  uStyle |= DFCS_PUSHED;
	// 
	// fit the buttonheight to the iconsize
	//
	CRect	r = rect;
	r.bottom = m_nIcon.cy + 6;
	r.right	= pDC->GetTextExtent ( strText ).cx + m_nIcon.cx + 6;
	pDC->SelectStockObject ( NULL_BRUSH );
	pDC->FillSolidRect ( rect, ::GetSysColor ( COLOR_BTNFACE ) );
	//
	// draw a frame around the button
	//
	if (m_bFlatDraw)
		::DrawFrameControl ( lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle );
	//
	GetWindowText ( strText );
	bWithStr = ! strText.IsEmpty ();
	//
	if (bWithStr)
	{
		nHotkeyPos = DelAmpersand(strText);
		pDC->SelectObject(m_fnt);
		TextExtent = pDC->GetTextExtent(strText);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_nColor);
		
		//-----2024.3.9 ytlim added. 원래 Left 정렬기능이 없었음. 추가.
		centerAlignTextoutX = (int)(rect.left + rect.Width()/2 - TextExtent.cx/2);
		if (m_bIconLeft)
		{
			if (m_bOnState) //ytlim. added
			{
				if (m_nIconOnID)
				{
					TextPos = CPoint((int)(rect.left + m_nIcon.cx + 16),(int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
				//
				// without icon -> center text
				//
				else
				{
					TextPos = CPoint(centerAlignTextoutX, (int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
			}
			else
			{
				if (m_nIconOffID)
				{
					if (m_nIconOnID)
					{
						TextPos = CPoint((int)(rect.left + m_nIcon.cx + 16), (int)(rect.bottom / 2 - TextExtent.cy / 2));
					}
					//
					// without icon -> center text
					//
					else
					{
						TextPos = CPoint((int)(rect.left / 2 + rect.right / 2), (int)(rect.bottom / 2 - TextExtent.cy / 2));
					}
				}
				//
				// without icon -> center text
				//
				else
				{
					TextPos = CPoint(centerAlignTextoutX, (int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
			}
			// 
			// calculate iconposition acording to the m_bIconRight-flag
			//
			if (m_bIconRight)
				RecPos = CPoint((rect.right - m_nIcon.cx - 6), (rect.Height() - m_nIcon.cy + 1) / 2);
			else
				RecPos = CPoint(6, (rect.Height() - m_nIcon.cy + 1) / 2);
		}
		else
		{
			if (m_bOnState) //ytlim. added
			{
				if (m_nIconOnID)
				{
					if (m_bIconRight)
						TextPos = CPoint((int)((rect.right - m_nIcon.cx) / 2 - TextExtent.cx / 2),(int)(rect.bottom / 2 - TextExtent.cy / 2));
					else
						TextPos = CPoint((int)((rect.right - m_nIcon.cx) / 2 - TextExtent.cx / 2) + m_nIcon.cx,	(int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
				//
				// without icon -> center text
				//
				else
				{
					TextPos = CPoint(centerAlignTextoutX, (int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
			}
			else
			{
				if (m_nIconOffID)
				{
					if (m_bIconRight)
						TextPos = CPoint((int)((rect.right - m_nIcon.cx) / 2 - TextExtent.cx / 2),(int)(rect.bottom / 2 - TextExtent.cy / 2));
					else
						TextPos = CPoint((int)((rect.right - m_nIcon.cx) / 2 - TextExtent.cx / 2) + m_nIcon.cx,	(int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
				//
				// without icon -> center text
				//
				else
				{
					TextPos = CPoint(centerAlignTextoutX, (int)(rect.bottom / 2 - TextExtent.cy / 2));
				}
			}
			// 
			// calculate iconposition acording to the m_bIconRight-flag
			//
			if (m_bIconRight)
				RecPos = CPoint((rect.right - m_nIcon.cx - 6), (rect.Height() - m_nIcon.cy + 1) / 2);
			else
				RecPos = CPoint(6, (rect.Height() - m_nIcon.cy + 1) / 2);
		}
	}
	//
	// without text -> center icon
	//
	else
	{
		RecPos = CPoint (	(int)( ( rect.right - m_nIcon.cx ) / 2 ),
							(int)( ( rect.bottom - m_nIcon.cy ) / 2 ) );
	}
	//
	if(m_bOnState)
	{
		if ( m_nIconOnID != NULL ) hIcon = AfxGetApp()->LoadIcon ( MAKEINTRESOURCE ( m_nIconOnID ) );
	}
	else
	{
		if ( m_nIconOffID != NULL ) hIcon = AfxGetApp()->LoadIcon ( MAKEINTRESOURCE ( m_nIconOffID ) );
	}
	//
	// move icon and text a little bit
	//
	if ( state & ODS_SELECTED ) 
	{
		TextPos.Offset ( 1, 1 );
		RecPos.Offset ( 1, 1);
	}
	//
	if ( state & ODS_DISABLED ) 
	{
		CSize  size ( m_nIcon.cx, m_nIcon.cy );
		if ( bWithStr ) 
			pDC->DrawState ( TextPos, TextExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		if ( hIcon != NULL )
		{
			HICON	hHelper = (HICON)CopyImage ( hIcon, IMAGE_ICON, m_nIcon.cx, m_nIcon.cy, LR_MONOCHROME );
			pDC->DrawState ( RecPos, size, hHelper, DSS_DISABLED, (HBRUSH)NULL );
			DestroyIcon ( (HICON)hHelper );
		}
	}
	else 
	{
		pDC->TextOut ( TextPos.x, TextPos.y, strText );
		//
		// draw the icon
		//
		if ( hIcon != NULL )
		{
			DrawIconEx ( pDC->GetSafeHdc (), rect.left + RecPos.x, rect.top + RecPos.y, 
							hIcon, (m_nIcon.cx) ? m_nIcon.cx : 32, (m_nIcon.cy) ? m_nIcon.cy : 32, 
							0, NULL, DI_NORMAL );
		}
	}

	//
	// if the button have the focus, draw the focus rect
	//
	if(m_bFocusedRectDraw) //ytlim. added
	{
		if ( state & ODS_FOCUS ) 
		{
			CBrush brush;
			brush.CreateSysColorBrush ( COLOR_3DDKSHADOW );
			pDC->FrameRect ( rect, &brush );
			rect.DeflateRect ( 4, 4, 4, 4 );
			pDC->DrawFocusRect ( rect );
		}
	}

	//
	if ( lpDrawItemStruct->itemState & ODS_SELECTED )
	{	
		pDC->SelectObject ( DarkShadowPen );
		pDC->MoveTo ( CPoint ( lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.bottom-1 ) );
		pDC->LineTo ( CPoint ( lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top ) );
		pDC->LineTo ( CPoint ( lpDrawItemStruct->rcItem.right-1, lpDrawItemStruct->rcItem.top ) );
		pDC->SelectObject ( HighlightPen );
		pDC->LineTo ( CPoint ( lpDrawItemStruct->rcItem.right-1, lpDrawItemStruct->rcItem.bottom-1 ) );
		pDC->LineTo ( CPoint ( lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.bottom-1 ) );
	}
	//
	// at the end, mark hotkey
	//
	if ( ( nHotkeyPos != -1 ) && ( bWithStr ) )
	{
		CString sHlp = strText.Mid ( nHotkeyPos, 1 );
		CSize nWidth = pDC->GetTextExtent ( sHlp );
		sHlp = strText.Left ( nHotkeyPos );
		CSize nStart = pDC->GetTextExtent ( sHlp );
		//
		if ( state & ODS_DISABLED ) ; // no line -> plainest
		else
		{
			CPen HotkeyPen ( PS_SOLID | PS_COSMETIC, 1, m_nColor );
			pDC->SelectObject ( HotkeyPen );
			pDC->MoveTo ( TextPos.x + nStart.cx, TextPos.y + TextExtent.cy  );
			pDC->LineTo ( TextPos.x + nStart.cx + nWidth.cx, TextPos.y + TextExtent.cy  );
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
create a special font for the button.
@param None
@return None
@see specifies the pitch and family of the font "roman". 
*/
void CIconButton::NewFont()
{
	m_fnt.DeleteObject ();
	m_fnt.CreateFont  (	m_TextMetrics.tmHeight,			// nHeight
						m_TextMetrics.tmMaxCharWidth,	// nWidth
						0,								// nEscapement
						0,								// nOrientation
						m_TextMetrics.tmWeight,			// nWeight
						m_TextMetrics.tmItalic,			// bItalic
						m_TextMetrics.tmUnderlined,		// bUnderline
						m_TextMetrics.tmStruckOut,		// bStrikeOut
						m_TextMetrics.tmCharSet,		// nCharSet
						OUT_DEFAULT_PRECIS,				// nOutPrecision
						CLIP_DEFAULT_PRECIS,			// nClipPrecision
						DEFAULT_QUALITY,				// nQuality
						m_TextMetrics.tmPitchAndFamily,	// nPitchAndFamily
						(LPCTSTR)m_sFaceName );			// lpszFacename
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
disable the button an force the system to repaint the button.
@param None
@return None
*/
void CIconButton::Disable ( void )
{ 
	EnableWindow ( false );
	Invalidate ();
	UpdateWindow ();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
enable the button an force the system to repaint the button.
@param None
@return None
*/
void CIconButton::Enable ( void )
{ 
	EnableWindow ( true );
	Invalidate ();
	UpdateWindow ();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
remove the ampersdand from buttontext.
@param CString& sTxt reference to the buttontext.
@return int 1st found position
*/
int CIconButton::DelAmpersand ( CString &sTxt )
{
	int nPos = 0;
	if ( ( nPos = sTxt.Find ( _T("&") )	) != -1 )
	{
		CString sLeft = sTxt.Left ( nPos );
		CString sRight = sTxt.Mid ( nPos + 1 );
		sTxt = sLeft + sRight;
	}
	return nPos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
Hide buton tip string.
@param None
@return None
*/
void CIconButton::HideTip ( void )
{
	RestoreBitmap ();
	m_bTipIsOpen = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
Show buton tip string.
@param None
@return None
*/
void CIconButton::ShowTip ( void )
{
	if ( m_bWithTip )
	{
		SetCapture ();
		GetCurrentTextMetric ();
		DrawTipBoxAndText ();
			m_bTipIsOpen = true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
Used internally. Find curren text extent information (cx and cy)
@param None
@return None
*/
void CIconButton::GetCurrentTextMetric ( void )
{
	if ( m_bWithTip )
	{
		CDC	*pDC = GetParent ()->GetDC ();
		if ( pDC )
		{
			m_TipDim.cx = pDC->GetTextExtent ( m_sTip ).cx + 4;
			m_TipDim.cy = pDC->GetTextExtent ( m_sTip ).cy + 4;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
Draw button tip box and print tip's string.
@param None
@return None
*/
void CIconButton::DrawTipBoxAndText ( void )
{
	if ( m_bWithTip )
	{
		if ( ! m_bTipIsOpen ) 
		{
			//CDC *pDC = GetDC ();
			CDC *pDC = GetOwner ()->GetDC ();
			if ( pDC )
			{
				CBrush BkGrBrush ( TIPBGRCOLOR );
				CBrush *pOldBrush = pDC->SelectObject ( &BkGrBrush );
				CPen BlackPen ( PS_SOLID, 1, RGB ( 0, 0, 0 ) );
				CPen *pOldPen = pDC->SelectObject ( &BlackPen );
				//
				m_TipRect.SetRect ( 0, 0, m_TipDim.cx, m_TipDim.cy );
				m_TipRect.OffsetRect ( m_TipPos.x, m_TipPos.y );
				//
				CRect ParentRect;
				GetParent ()->GetWindowRect ( ParentRect );
				if ( m_TipRect.right > ParentRect.right )
				{
					int nDiv = m_TipRect.right - ParentRect.right + 5;
					m_TipRect.right -= nDiv;
					m_TipRect.left -= nDiv;
				}
				//
				GetOwner ()->ScreenToClient ( m_TipRect );
				SaveBitmap ();
				pDC->Rectangle ( m_TipRect );
				pDC->SetBkMode ( TRANSPARENT );
				pDC->DrawText ( m_sTip, m_TipRect, DT_CENTER );
				pDC->SelectObject ( pOldBrush );
				pDC->SelectObject ( pOldPen );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
NC area hit event handler.
@param[in] CPoint point mouse clcked position.
@return LRESULT
*/
LRESULT CIconButton::OnNcHitTest(CPoint point) 
{
	if ( m_bWithTip )
	{
		if ( ! m_bTipIsOpen )
		{
			m_TipPos = point;
			ShowTip ();
		}
	}
	return CButton::OnNcHitTest(point);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
Mouse move event handler.
@param[in] UINT nFlags mouse status.
@param[in] CPoint point mouse position.
@return None
*/
void CIconButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect ClientRect;
	GetClientRect ( &ClientRect );
	if ( ! ClientRect.PtInRect ( point ) )	
	{	
		HideTip ();
		ReleaseCapture ();
	}
	CButton::OnMouseMove ( nFlags, point );
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
Draw momory context to screen DC.
@param None.
@return bool
*/
bool CIconButton::RestoreBitmap ( void )
{
	bool bResult = false;
	//
	::BitBlt (	m_hOwnerDC,
				m_TipRect.left, m_TipRect.top, 
				m_TipDim.cx, m_TipDim.cy,
				m_hMemDC,
				0, 0,
				SRCCOPY );
	DeleteObject ( m_hMemBmp );
	DeleteDC ( m_hMemDC );
	DeleteDC ( m_hOwnerDC );
	//
	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
Use Internally. Get current screen dc button image and create a memory dc bitmap
@param None.
@return bool
*/
bool CIconButton::SaveBitmap ( void )
{
	bool bResult = true;
	//
 	m_hOwnerDC	= GetOwner ()->GetDC ()->m_hDC;				
	m_hMemDC	= ::CreateCompatibleDC ( m_hOwnerDC );
	m_hMemBmp	= ::CreateCompatibleBitmap ( m_hOwnerDC, m_TipDim.cx, m_TipDim.cy );
	SelectObject ( m_hMemDC, m_hMemBmp );
	::BitBlt (	m_hMemDC,
				0, 0,
				m_TipDim.cx, m_TipDim.cy,
				m_hOwnerDC,
				m_TipRect.left, m_TipRect.top,
				SRCCOPY );
	//
	return bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/**
Mouse button up event handler.
- ytlim added.
@param None.
@return bool
*/
void CIconButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    m_bOnState = !m_bOnState;
    InvalidateRect(NULL);
    CButton::OnLButtonUp(nFlags, point);
}