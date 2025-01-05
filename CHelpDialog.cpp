// CHelpDialog.cpp: 구현 파일
//

#include "pch.h"
#include "RegexStudy.h"
#include "afxdialogex.h"
#include "CHelpDialog.h"

#define HELPDLG_BKG_COLOR	RGB(0xFF,0xFF,0xFF)
#define HELPDLG_TXT_COLOR	RGB(0x00,0x00,0x00)

// CHelpDialog 대화 상자

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	m_richEdit.m_BkgColor = HELPDLG_BKG_COLOR;
	m_richEdit.m_TxtColor = HELPDLG_TXT_COLOR;
	m_richEdit.m_FontPointSize = 10; //set default font size(12pt)
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richEdit);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDialog 메시지 처리기
BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_backBrush.CreateSolidBrush(HELPDLG_BKG_COLOR);
	ControlLayout();

	//-----exe에서 파일을 풀어내고 로컬 폴더에 파일생성
	CString sFullPath = GETAPP()->m_sModulePath + _T("Help.txt");
	if (PathFileExists(sFullPath) == TRUE)
	{
		DeleteFile(sFullPath);
	}
	HANDLE hFile = CreateFile((LPCTSTR)sFullPath, GENERIC_ALL, 0, 0, CREATE_ALWAYS, 0, 0);
	int resid = IDR_BIN_HELP_TXT;
	GETAPP()->ExtractBinFileFromResource(hFile, _T("BIN"), resid);

	//-----초기 설정
	CString s;
	s = GETAPP()->READ_UNICODE_FILE(sFullPath);
	m_richEdit.TextOut(s, HELPDLG_TXT_COLOR);
	m_richEdit.Init(FONTFACE, 10, HELPDLG_TXT_COLOR);

	return TRUE;
}


void CHelpDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	ControlLayout();
	Invalidate();
}


HBRUSH CHelpDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// 다이얼로그 배경색 변경
	pDC->SetTextColor(HELPDLG_TXT_COLOR);
	pDC->SetBkColor(HELPDLG_BKG_COLOR);
	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)m_backBrush;

	return hbr;

}
CRect CHelpDialog::GetRect(CWnd* pWnd)
{
	CRect rt = CRect(0, 0, 0, 0);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
	}
	return rt;
}

void CHelpDialog::ControlLayout()
{
	if (m_richEdit.GetSafeHwnd() == NULL) return;

	CRect rt;
	GetClientRect(rt);
	rt.left +=5;
	rt.top += 5;
	rt.right -= 5;
	rt.bottom -= 5;

	//시작 위치, 크기 조정
	m_richEdit.MoveWindow(rt);

	CString s;
	s.Format(_T("richEdit Rect(l,t,r,b)=%d, %d, %d, %d\n"), 
		rt.left, rt.top, rt.right, rt.bottom);
	TRACE(s);
}