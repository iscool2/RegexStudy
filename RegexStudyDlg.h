
// RegexStudyDlg.h : header file
//

#pragma once

#include "CRichEditCtrlEx.h"
#include "IconButton.h"

//----------------------------------------------------------------------------------
// Xp테마버그 해결 (다이얼로그버튼, 체크박스등 OnCtlColor 메세지 호출안되는 이슈)
#pragma comment(lib, "UxTheme.lib")
//----------------------------------------------------------------------------------


#define CICONBTN_CNT		(3)			// 버튼의 갯수에 맞게 설정
#define APPSIZE_WIDTH_MIN	(1366)		// 어플리케이션 최소폭
#define APPSIZE_HEIGHT_MIN	(768)		// 어플리케이션 최소높이


// CRegexStudyDlg dialog
class CRegexStudyDlg : public CDialogEx
{
// Construction
public:
	CRegexStudyDlg(CWnd* pParent = nullptr);	// standard constructor
	CBrush m_backBrush;
	CBrush m_backBrush2;
	void ControlLayout();
	CRect GetRect(CWnd& wnd);
	CFont m_fontRegex;
	CIconButton* pIconBtn[CICONBTN_CNT];

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGEXSTUDY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_editRegex;
	CEdit m_editInput;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CComboBox m_cbRegexSample;
	CComboBox m_cbInputSample;
	CStatic m_staticLabel1;
	CStatic m_staticLabel2;
	CStatic m_staticLabel3;
	CStatic m_staticLabel4;
	CStatic m_staticLabel5;

	CIconButton m_btnMatch;
	CIconButton m_btnReplace;
	CIconButton m_btnHelp;
	CRichEditCtrlEx m_richEdit;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButtonMatch();
	afx_msg void OnBnClickedButtonHelp();
	CButton m_chkOutputMode;
	CStatic m_staticLabel6;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheckOutputmode();
};
