#pragma once
#include "afxdialogex.h"
#include "CRichEditCtrlEx.h"

// CHelpDialog 대화 상자

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHelpDialog();
	void ControlLayout();
	CRect GetRect(CWnd* pWnd);
	CBrush m_backBrush;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRichEditCtrlEx m_richEdit;
};
