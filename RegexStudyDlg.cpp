
// RegexStudyDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RegexStudy.h"
#include "RegexStudyDlg.h"
#include "afxdialogex.h"
#include "CHelpDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_STATIC_VERSION0, GETAPP()->m_sApplicationInfo[0]);
	SetDlgItemText(IDC_STATIC_VERSION1, GETAPP()->m_sApplicationInfo[1]);
	SetDlgItemText(IDC_STATIC_VERSION2, GETAPP()->m_sApplicationInfo[3]);
	SetDlgItemText(IDC_STATIC_VERSION3, GETAPP()->m_sApplicationInfo[2]);
	SetDlgItemText(IDC_STATIC_VERSION4, GETAPP()->m_sApplicationInfo[4]);

	return TRUE;
}


// CRegexStudyDlg dialog



CRegexStudyDlg::CRegexStudyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGEXSTUDY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_richEdit.m_BkgColor = DARKTHEME_BKG_BLACK2;
	m_richEdit.m_TxtColor = DARKTHEME_TXT;
	m_richEdit.m_FontPointSize = 12; //set default font size(12pt)
}

void CRegexStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editRegex);
	DDX_Control(pDX, IDC_EDIT2, m_editInput);
	DDX_Control(pDX, IDC_COMBO1, m_cbRegexSample);
	DDX_Control(pDX, IDC_COMBO2, m_cbInputSample);
	DDX_Control(pDX, IDC_STATIC_LABEL1, m_staticLabel1);
	DDX_Control(pDX, IDC_STATIC_LABEL2, m_staticLabel2);
	DDX_Control(pDX, IDC_STATIC_LABEL3, m_staticLabel3);
	DDX_Control(pDX, IDC_STATIC_LABEL4, m_staticLabel4);
	DDX_Control(pDX, IDC_STATIC_LABEL5, m_staticLabel5);
	DDX_Control(pDX, IDC_BUTTON_MATCH, m_btnMatch);
	DDX_Control(pDX, IDC_BUTTON_REPLACE, m_btnReplace);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_btnHelp);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richEdit);
	DDX_Control(pDX, IDC_CHECK_OUTPUTMODE, m_chkOutputMode);
	DDX_Control(pDX, IDC_STATIC_LABEL6, m_staticLabel6);
}

BEGIN_MESSAGE_MAP(CRegexStudyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CRegexStudyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRegexStudyDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRegexStudyDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CRegexStudyDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_MATCH, &CRegexStudyDlg::OnBnClickedButtonMatch)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CRegexStudyDlg::OnBnClickedButtonHelp)
	ON_EN_CHANGE(IDC_EDIT1, &CRegexStudyDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CHECK_OUTPUTMODE, &CRegexStudyDlg::OnBnClickedCheckOutputmode)
END_MESSAGE_MAP()

//D:\아이콘모음\아이콘에 대한 모든 것\아이콘 모음\Iconfactory\Agua Stacks\Agua Stacks Win\Icons

// CRegexStudyDlg message handlers

BOOL CRegexStudyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//-----------------------------------------------------------
	SetWindowTheme(m_chkOutputMode.m_hWnd, _T(""), _T(""));
	//-----------------------------------------------------------
	m_chkOutputMode.SetCheck(TRUE);

	pIconBtn[0] = &m_btnMatch;
	pIconBtn[1] = &m_btnReplace;
	pIconBtn[2] = &m_btnHelp;

	UINT uID[CICONBTN_CNT] = { IDI_ICON_CHECKMARK, IDI_ICON_REFRESH, IDI_ICON_HELP};

	for (int i = 0; i < CICONBTN_CNT; i++)
	{
		pIconBtn[i]->SetIconOnID(uID[i]);
		pIconBtn[i]->SetIconOffID(uID[i]);
		pIconBtn[i]->SetIconSize(32, 32);
		pIconBtn[i]->SetState(FALSE);
	}

	//-----ready dialog background fill brush
	m_backBrush.CreateSolidBrush(DARKTHEME_BKG_BLACK1);
	m_backBrush2.CreateSolidBrush(DARKTHEME_BKG_BLACK2);

	//-----Regex관련 컨트롤 폰트 설정
//	VERIFY(m_fontRegex.CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Courier New")));
	VERIFY(m_fontRegex.CreateFont(22, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, FONTFACE));
	m_editRegex.SetFont(&m_fontRegex);

	//-----regex input 초기값대입
	m_cbRegexSample.AddString(_T("[a-zA-Z]{3,7}day")); //요일 검색 검색
	m_cbRegexSample.AddString(_T("([A-Z])\\w+")); //대문자 단어 검색
	m_cbRegexSample.AddString(_T("([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})")); //IP 검색 (단순형식만검사. 값검사는 못함)
	m_cbRegexSample.AddString(_T("\\s(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\s"));//IP 검색
	m_cbRegexSample.AddString(_T("\\w+@\\w+\\.\\w+(\\.\\w+)?")); //E-Mail
	m_cbRegexSample.AddString(_T("([Gg]0?[01]) *(([XxYyZz]) *(-?\\d+.?\\d*)) *(([XxYyZz]) *(-?\\d+.?\\d*))? *(([XxYyZz]) *(-?\\d+.?\\d*))? *(([Ff]) *(-?\\d+.?\\d*))?")); //GCODE
	m_cbRegexSample.AddString(_T("<\\!--[a-zA-Z\\s]+-->")); //html comment
	m_cbRegexSample.AddString(_T("[0-9]*")); //숫자
	m_cbRegexSample.AddString(_T("[a-zA-Z]*")); //영문자
	m_cbRegexSample.AddString(_T("[가-힣]*$")); //한글
	m_cbRegexSample.AddString(_T("\\d{2,3}-\\d{3,4}-\\d{4}")); //전화번호
	m_cbRegexSample.AddString(_T("[A-Za-z0-9]{6,12}")); //
	m_cbRegexSample.AddString(_T("[A-Za-z0-9]{6,12}")); //휴대전화번호
	m_cbRegexSample.AddString(_T("\\d{2}([0]\\d|[1][0-2])([0][1-9]|[1-2]\\d|[3][0-1])[-]*[1-4]\\d{6}")); //주민등록번호
	m_cbRegexSample.AddString(_T("\\d{3}-\\d{2}")); //우편번호
	m_cbRegexSample.AddString(_T("010-\\d{4}-\\d{4}")); //휴대폰 번호
	m_cbRegexSample.AddString(_T("([0-9]+.[0-9]*)|([0-9]*.[0-9+)|([0-9]+)")); // 실수판별
	m_cbRegexSample.AddString(_T("(?:\\A|.*\\\\)([^\\\\]+)"));
	m_cbRegexSample.AddString(_T("\\A(\\d{3,4})[- ]?(\\d{4})[- ]?(\\d{4})[- ]?(\\d{4})\\z"));
	m_cbRegexSample.AddString(_T("\\d{2}([0]\\d|[1][0-2])([0][1-9]|[1-2]\\d|[3][0-1])[-]*[1-4]\\d{6}"));
	m_cbRegexSample.AddString(_T("^(([A-Z]{1,2}[0-9]{1,2})|([A-Z]{1,2}[0-9][A-Z]))\\s?([0-9][A-Z]{2})$"));
	m_cbRegexSample.AddString(_T("[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*.[a-zA-Z]{2,3}"));
	m_cbRegexSample.AddString(_T("(((경기|강원|경상[가-힣]|전라[가-힣]|충청[가-힣]|제주[가-힣]+)도|(서울|인천|대전|대구|울산|광주|부산)([가-힣]+)?시)\\s+([가-힣]+시|[가-힣]+구|[가-힣]+군)\\s+([가-힣]+구)?)|(세종([가-힣]+)?시)"));
	m_staticLabel6.SetWindowText(_T("expression check message here"));

	//-----대화상자 최대화
	ShowWindow(SW_MAXIMIZE);
#if(1)
	ControlLayout();
#else
	/// Popup to the window Center
	int wndW = APPSIZE_WIDTH_MIN, wndH = APPSIZE_HEIGHT_MIN;
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow((screenW- wndW)/2, (screenH - wndH) / 2, wndW, wndH);
#endif


	//초기선택값 설정
	m_cbRegexSample.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//-----input 초기값대입
	//초기선택값 설정
	m_cbInputSample.SetCurSel(0);
	OnCbnSelchangeCombo2();

	//-----초기에 우측 결과 상자값 설정
	CString s;
	m_editInput.GetWindowText(s);

	//-----초기에 설정된 대로 정규식 검사한번 때려본다
	OnEnChangeEdit1();

	//-----초기에 정규식 입력상자에 포커스를 줌
	m_editRegex.SetFocus();

	return TRUE; 
}

void CRegexStudyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	//=================================================
	// Windows 종료[x] 버튼으로 대화상자 종료가능하게 함.
	//2024.12.28 추가
	else if ((nID & 0xFFF0) == SC_CLOSE)
	{
		EndDialog(IDCANCEL);
	}
	//=================================================
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegexStudyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegexStudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CRegexStudyDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}

/*------------------------------------------------------------------------------------*/
// RichEdit에서 발생하는 메세지는 여기로 날라오지 않는다. 주의해라!!!
// 간혹 라디오버튼, 체크박스등 의 컨트롤은 투명이 적용이 안돼는 경우가 있다.
// XP테마의 버그라고 한다. 해결 방법은 #pragma comment(lib, "UxTheme.lib") 를 추가하고, 
// 다이얼로그 초기화(Initdialog)에서 SetWindowTheme(컨트롤변수.m_hWnd, L"", L""); 를 추가 해준다.
// 컨틀롤과 브러시는 아래와 같이 정의되어 있습니다.
//#define CTLCOLOR_MSGBOX     0
//#define CTLCOLOR_EDIT       1
//#define CTLCOLOR_LISTBOX    2
//#define CTLCOLOR_BTN        3
//#define CTLCOLOR_DLG        4
//#define CTLCOLOR_SCROLLBAR  5
//#define CTLCOLOR_STATIC     6
//#define CTLCOLOR_MAX        7
//#define WHITE_BRUSH         0
//#define LTGRAY_BRUSH        1
//#define GRAY_BRUSH          2
//#define DKGRAY_BRUSH        3
//#define BLACK_BRUSH         4
//#define NULL_BRUSH          5
//#define HOLLOW_BRUSH        NULL_BRUSH
//#define WHITE_PEN           6
//#define BLACK_PEN           7
//#define NULL_PEN            8
//#define OEM_FIXED_FONT      10
//#define ANSI_FIXED_FONT     11
//#define ANSI_VAR_FONT       12
//#define SYSTEM_FONT         13
//#define DEVICE_DEFAULT_FONT 14
//#define DEFAULT_PALETTE     15
//#define SYSTEM_FIXED_FONT   16
/*------------------------------------------------------------------------------------*/
HBRUSH CRegexStudyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd == (CWnd*)&m_editInput)
	{
		// 다이얼로그 배경색 변경
		pDC->SetTextColor(DARKTHEME_TXT);
		pDC->SetBkColor(DARKTHEME_BKG_BLACK2);
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)m_backBrush2;
	}
	else if (pWnd == (CWnd*)&m_staticLabel6)
	{
		// 다이얼로그 배경색 변경
		pDC->SetTextColor(COLOR_RED);
		pDC->SetBkColor(DARKTHEME_BKG_BLACK1);
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)m_backBrush;
	}
	else
	{
		//폰트 색상설정
		if (pWnd == (CWnd*)&m_editRegex) pDC->SetTextColor(RGB(0xFF,0xFF,00));
		else                             pDC->SetTextColor(DARKTHEME_TXT);

		// 다이얼로그 배경색 변경
		pDC->SetBkColor(DARKTHEME_BKG_BLACK1);
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)m_backBrush;
	}
	return hbr;
}

void CRegexStudyDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}

void CRegexStudyDlg::OnBnClickedCancel()
{
	//CDialogEx::OnCancel();
}

void CRegexStudyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	ControlLayout();
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Expression Sample         Input Sample
// [....................]    [.................]                 [MatchButton]   [ReplaceButton]
// Expression
// [....................]
// Input String								       Result String
// +-----------------------------------------+     +------------------------------------------------------+
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// |                                         |     |                                                      |
// +-----------------------------------------+     +------------------------------------------------------+

CRect CRegexStudyDlg::GetRect(CWnd& wnd)
{
	CRect rt = CRect(0,0,0,0);
	if (wnd.GetSafeHwnd())
	{
		wnd.GetWindowRect(rt);
		ScreenToClient(rt);
	}
	return rt;
}

void CRegexStudyDlg::ControlLayout()
{
	if (m_staticLabel1.GetSafeHwnd() == NULL) return;
	if (m_staticLabel2.GetSafeHwnd() == NULL) return;
	if (m_staticLabel3.GetSafeHwnd() == NULL) return;
	if (m_staticLabel4.GetSafeHwnd() == NULL) return;
	if (m_staticLabel5.GetSafeHwnd() == NULL) return;
	if (m_cbRegexSample.GetSafeHwnd() == NULL) return;
	if (m_cbInputSample.GetSafeHwnd() == NULL) return;
	if (m_editRegex.GetSafeHwnd() == NULL) return;
	if (m_editInput.GetSafeHwnd() == NULL) return;
	if (m_staticLabel6.GetSafeHwnd() == NULL) return;
	if (m_richEdit.GetSafeHwnd() == NULL) return;
	if (m_btnMatch.GetSafeHwnd() == NULL) return;
	if (m_btnReplace.GetSafeHwnd() == NULL) return;
	if (m_btnHelp.GetSafeHwnd() == NULL) return;
	if (m_chkOutputMode.GetSafeHwnd() == NULL) return;

	CRect rtMain;
	CRect rtTemp;
	CRect rtCtrlOrg, rtCtrl, rtRef, rtRef2;
	int CTRLMgn = 5;

	CRect rectWorkArea;
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	::GetMonitorInfo(::MonitorFromWindow(GetSafeHwnd(), MONITOR_DEFAULTTONEAREST), &mi);
	rectWorkArea = mi.rcWork;
	int SCREEN_W = rectWorkArea.Width();
	int SCREEN_H = rectWorkArea.Height();
	//int SCREEN_W = GetSystemMetrics(SM_CXSCREEN);
	//int SCREEN_H = GetSystemMetrics(SM_CYSCREEN);
	int MGN = 30;
	//(1)-----컨트롤이 정렬될 내부 영역 설정
	GetWindowRect(rtMain);
	ScreenToClient(rtMain);
	rtMain.left += MGN;
	rtMain.top += MGN+20;
	rtMain.right -= 10;
	rtMain.bottom -= 10;

	//---IDC_STATIC_LABEL1
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = rtMain;
	rtCtrlOrg = GetRect(m_staticLabel1);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.top;
	rtCtrl.right = rtCtrl.left + rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_staticLabel1.MoveWindow(rtCtrl);

	//---Expression Sample Combobox
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel1);
	rtCtrlOrg = GetRect(m_cbRegexSample);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtCtrl.left + rtMain.Width() / 2 - MGN - 100;
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_cbRegexSample.MoveWindow(rtCtrl);

	//---Expression String
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_cbRegexSample);
	rtCtrlOrg = GetRect(m_staticLabel3);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_staticLabel3.MoveWindow(rtCtrl);

	//---Expression Editbox
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel3);
	rtCtrlOrg = GetRect(m_editRegex);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtMain.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_editRegex.MoveWindow(rtCtrl);

	//---Error Message String
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_editRegex);
	rtCtrlOrg = GetRect(m_staticLabel6);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtMain.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_staticLabel6.MoveWindow(rtCtrl);

	//---Input String
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel6);
	rtCtrlOrg = GetRect(m_staticLabel4);//note! left,top는정상으로 얻어지지만, right,bottom은 잘못 리턴됨!(mfc 버그로 추정)
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn*5;
	rtCtrl.right = rtCtrl.left + 120;// rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_staticLabel4.MoveWindow(rtCtrl);

	//---Input Editbox
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel4);
	rtCtrlOrg = GetRect(m_editInput);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtCtrl.left + rtMain.Width() / 2 - MGN;
	rtCtrl.bottom = rtMain.Height();
	m_editInput.MoveWindow(rtCtrl);

	//---Match String
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel4);
	rtCtrlOrg = GetRect(m_staticLabel5);//note! left,top는정상으로 얻어지지만, right,bottom은 잘못 리턴됨!(mfc 버그로 추정)
	//시작 위치, 크기 조정
	rtCtrl.left = rtMain.Width() / 2;
	rtCtrl.top = rtRef.top;
	rtCtrl.right = rtCtrl.left + 120;// rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtRef.Height();
	m_staticLabel5.MoveWindow(rtCtrl);

	//---Output Mode Checkbox
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel5);
	rtCtrlOrg = GetRect(m_chkOutputMode);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.right + MGN;
	rtCtrl.top = rtRef.top;
	rtCtrl.right = rtCtrl.left + rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtRef.Height();
	m_chkOutputMode.MoveWindow(rtCtrl);

	//---Output Editbox
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel5);
	rtCtrlOrg = GetRect(m_richEdit);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtMain.Width();
	rtCtrl.bottom = rtMain.Height();
	m_richEdit.MoveWindow(rtCtrl);

	//---Input Sample String
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel1);
	rtRef2 = GetRect(m_cbRegexSample);
	rtCtrlOrg = GetRect(m_staticLabel2);
	//시작 위치, 크기 조정
	rtCtrl.left = rtRef2.right+MGN/2;
	rtCtrl.top = rtRef.top;
	rtCtrl.right = rtCtrl.left + rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_staticLabel2.MoveWindow(rtCtrl);

	//---Input Sample Combobox
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_staticLabel2);
	rtCtrlOrg = GetRect(m_cbInputSample);
	rtCtrl.left = rtRef.left;
	rtCtrl.top = rtRef.bottom + CTRLMgn;
	rtCtrl.right = rtCtrl.left + rtCtrlOrg.Width();
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_cbInputSample.MoveWindow(rtCtrl);

	//---Match Button
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_cbInputSample);
	rtCtrlOrg = GetRect(m_btnMatch);
	rtCtrl.left = rtRef.right + MGN/2;
	rtCtrl.right = rtCtrl.left + rtCtrlOrg.Width();
	rtCtrl.top = rtRef.top;
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_btnMatch.MoveWindow(rtCtrl);

	//---Replace Button
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_btnMatch);
	rtCtrlOrg = GetRect(m_btnReplace);
	rtCtrl.left = rtRef.right + MGN/2;
	rtCtrl.right = rtCtrl.left + rtCtrlOrg.Width();
	rtCtrl.top = rtRef.top;
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_btnReplace.MoveWindow(rtCtrl);

	//---Help Button
	//배치에 참조할 컨트롤의 위치 얻기
	rtRef = GetRect(m_btnReplace);
	rtCtrlOrg = GetRect(m_btnHelp);
	rtCtrl.right = rtMain.Width();
	rtCtrl.left = rtCtrl.right - rtCtrlOrg.Width();
	rtCtrl.top = rtRef.top;
	rtCtrl.bottom = rtCtrl.top + rtCtrlOrg.Height();
	m_btnHelp.MoveWindow(rtCtrl);


	//-----Multiline 속성을 갖는 EditBox 정렬이슈 해결.
	//에딧박스의 좌우상하로부터 5픽셀씩을 안쪽 유효영역으로 설정(;좁혀줌)
	CDC* pDC = GetDC();
	CString csText;
	CRect rt;
	CSize szText, szClient;
	CEdit* pEditCtrl[2] = {&m_editInput, &m_editRegex};

	for (int i = 0; i<2; i++)
	{
		if (pEditCtrl[i]->GetSafeHwnd() == NULL) continue;

		pDC->SelectObject(pEditCtrl[i]->GetFont());
		pEditCtrl[i]->GetWindowText(csText);
		szText = pDC->GetTextExtent(csText);
		pEditCtrl[i]->GetClientRect(&rt);
		szClient = rt.Size();
		rt.left += 5;
		rt.right -= 5;
		rt.top += 5;
		rt.bottom -= -5;
		pEditCtrl[i]->SetRect(&rt);
	}
	//-----rich edit control
	pDC->SelectObject(m_richEdit.GetFont());
	m_richEdit.GetWindowText(csText);
	szText = pDC->GetTextExtent(csText);
	m_richEdit.GetClientRect(&rt);
	szClient = rt.Size();
	rt.left += 5;
	rt.right -= 5;
	rt.top += 5;
	rt.bottom -= -5;
	m_richEdit.SetRect(&rt);

	ReleaseDC(pDC);
}

void CRegexStudyDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = APPSIZE_WIDTH_MIN;
	lpMMI->ptMinTrackSize.y = APPSIZE_HEIGHT_MIN;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

/*------------------------------------------------------------------------------*/
//Note. return값에 대한 고찰
//  0: 메시지가 계속 처리하기를 원한다면, 1(0이 아닌 값): 메시지가 처리되지 않길 원한다면
/*------------------------------------------------------------------------------*/
BOOL CRegexStudyDlg::PreTranslateMessage(MSG* pMsg)
{
	//-----------------------------------------------------------------------
	// Dark UI를 구현하고자 ON_WM_CTLCOLOR를 Override 했다. 이 상태에서
	// 편집창에 편집이 발생하면 뒤쪽으로 업데이트가 일어나면서 새로운 값이 화면에 반영
	// 되어야 하지만, 이전에 뿌려졌던 값들과 중복되어 출력되는 문제가 발생하고 있음.
	// 이 현상을 제거하고자, 매 편집이 발생될때마다 편집컨트롤을 다시 업데이트해 줌.
	// 2024.12.31 ytlim. commented
	if (pMsg->message == WM_KEYDOWN/*WM_CHAR*/)
	{
		if (pMsg->hwnd == m_editRegex.GetSafeHwnd()) m_editRegex.Invalidate();
		if (pMsg->hwnd == m_editInput.GetSafeHwnd()) m_editInput.Invalidate();
		if (pMsg->hwnd == m_richEdit.GetSafeHwnd()) m_richEdit.Invalidate();
	}
	//-----------------------------------------------------------------------
	if (pMsg->hwnd == m_editRegex.GetSafeHwnd() && 
		pMsg->message == WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		OnEnChangeEdit1();
		m_editRegex.SetFocus();
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

/*--------------------------------------------------------------------------*/
// 정규식이 한글자라도 변경되면 매번 검사루틴 호출
/*--------------------------------------------------------------------------*/
void CRegexStudyDlg::OnEnChangeEdit1()
{
	OnBnClickedButtonMatch();
	m_editRegex.SetFocus();
}

/*------------------------------------------------------------------------------*/
//	Regex Sample
/*------------------------------------------------------------------------------*/
void CRegexStudyDlg::OnCbnSelchangeCombo1()
{
	CString s;
	m_cbRegexSample.GetLBText(m_cbRegexSample.GetCurSel(), s);
	m_editRegex.SetWindowText(s);
	OnEnChangeEdit1();
}

void CRegexStudyDlg::OnBnClickedButtonHelp()
{
	CHelpDialog dlg;
	dlg.DoModal();
}

//http://www.regexper.com
//https://regexr.com
//https://www.nextree.co.kr/p4327
/*--------------------------------------------------------------------------------------*/
//	UNICODE 스트링에 대한 Regex Matching
/*--------------------------------------------------------------------------------------*/
void CRegexStudyDlg::OnBnClickedButtonMatch()
{
	CWaitCursor cursor;

	BOOL bOutputViewModeComplete = (BOOL)m_chkOutputMode.GetCheck();
	bool bret = 0;
	CString s, sError, sPattern, sInput, sResult;
	_tstring strptn, stemp;
	std::vector<_tstring> strin;

	//(1)-----좌측 스트링 얻기
	for (int i = 0; i < m_editInput.GetLineCount(); i++)
	{
		TCHAR buffer[1024] = { 0, };
		m_editInput.GetLine(i, buffer, sizeof(buffer));
		if (m_editInput.GetLineCount() > 1)
		{
			wcscat_s(buffer, _T("\r\n"));
		}
		s = buffer;
		stemp = CStringToStdWStr(s);
		strin.push_back(stemp);
	}

	//(2)-----정규식 스트링 얻기
	m_editRegex.GetWindowText(sPattern);
	strptn   = sPattern.GetString();

	//(3)-----정규식스트링 검증
	try 
	{
		_tregex re(strptn);
		sError = "";
	}
	catch (std::regex_error& e) 
	{
		CString sRootCause;
		switch (e.code())
		{
			case std::regex_constants::error_backref: sRootCause = _T("식에 잘못된 역참조가 포함되었습니다. The expression contained an invalid back reference"); break;
			case std::regex_constants::error_badbrace: sRootCause = _T("식에 잘못된 개수의 { } 식이 포함되었습니다. The expression contained an invalid count in a { } expression"); break;
			case std::regex_constants::error_badrepeat: sRootCause = _T("반복 실행 식(대부분의 컨텍스트에서 '*', '?', '+', '{' 중 하나)이 식 뒤에 오지 않았습니다. A repeat expression (one of '*', '', '+', '{' in most contexts) was not preceded by an expression"); break;
			case std::regex_constants::error_brace: sRootCause = _T("식에 일치하지 않는 '(' 또는 ')'가 포함되었습니다. The expression contained an unmatched '{' or '}'"); break;
			case std::regex_constants::error_brack: sRootCause = _T("식에 일치하지 않는 '[' 또는 ']'가 포함되었습니다. The expression contained an unmatched '[' or ']'"); break;
			case std::regex_constants::error_collate: sRootCause = _T("식에 잘못된 데이터 정렬 요소 이름이 포함되었습니다. The expression contained an invalid collating element name"); break;
			case std::regex_constants::error_complexity: sRootCause = _T("시도된 일치가 너무 복잡하여 실패했습니다. An attempted match failed because it was too complex"); break;
			case std::regex_constants::error_ctype: sRootCause = _T("식에 잘못된 문자 클래스 이름이 포함되었습니다. The expression contained an invalid character class name"); break;
			case std::regex_constants::error_escape: sRootCause = _T("식에 잘못된 이스케이프 시퀀스가 포함되었습니다. The expression contained an invalid escape sequence"); break;
			case std::regex_constants::error_paren: sRootCause = _T("식에 일치하지 않는 '(' 또는 ')'가 포함되었습니다. The expression contained an unmatched '(' or ')'"); break;
			case std::regex_constants::error_parse: sRootCause = _T("식을 구문 분석하지 못했습니다. The expression failed to parse"); break;
			case std::regex_constants::error_range: sRootCause = _T("식에 잘못된 문자 범위 지정자가 포함되었습니다. The expression contained an invalid character range specifier"); break;
			case std::regex_constants::error_space: sRootCause = _T("사용 가능한 리소스가 부족하여 정규식을 구문 분석하지 못했습니다. Parsing a regular expression failed because there were not enough resources available"); break;
			case std::regex_constants::error_stack: sRootCause = _T("사용 가능한 메모리가 부족하여 시도된 일치가 실패했습니다. Attempted match failed because there was not enough memory available"); break;
			case std::regex_constants::error_syntax: sRootCause = _T("구문 오류를 구문 분석하지 못했습니다. Parsing failed on a syntax error"); break;
			default:sRootCause = _T("알수없는 오류. Error_unknown"); break;
		}
		m_staticLabel6.SetWindowText(sRootCause);
		return;
	}

	int		nLineBeginPos = 0, nMarkStart = 0, nMarkEnd = 0;
	CString SLINE, sTrace;

	//(4)-----한줄단위로 정규식 검사하고 그 검사결과를 richedit에 표시
	_tregex re(strptn);
	_tsmatch smatch;
	m_richEdit.Clear();
	m_richEdit.SetWindowText(_T(""));
	m_staticLabel6.SetWindowText(_T(""));

	m_richEdit.LockWindowUpdate(); //일시적으로 윈도우 업데이트 금지(고속처리를 위해 필요)

	for (int i = 0; i < (int)strin.size(); i++)
	{
		Sleep(0);

		sTrace.Format(_T("\r\nLine:%d----------"), i); TRACE(sTrace);

		_tstring sline = strin.at(i);
		SLINE = StdWStrToCString(sline);
		nMarkStart = nLineBeginPos;

		if (bOutputViewModeComplete == TRUE)
		{
			m_richEdit.TextOut(SLINE, DARKTHEME_TXT);
		}

		while (std::regex_search(sline, smatch, re))
		{
			_tstring stemp;
			stemp = smatch.str();
			if (stemp.size() == 0)	break; //it is shold be checked!!!
			nMarkStart += (int)sline.find(stemp);
			nMarkEnd    = nMarkStart + (int)stemp.size();
			sline = smatch.suffix();
			//(5)-----검사결과 표시
			sTrace.Format(_T("\r\nLineStartPos=%d, MatchBegin=%d, MatchEnd=%d   "), nLineBeginPos, nMarkStart, nMarkEnd); TRACE(sTrace);
			s = StdWStrToCString(stemp);
			if (bOutputViewModeComplete == TRUE)
			{
				///입력중에서 매칭된것에 색깔을 입히는 방식
				m_richEdit.MarkText(nMarkStart, nMarkEnd, COLOR_LIME);
			}
			else
			{
				///매칭된 문자만 개별적으로 출력하는 방식
				m_richEdit.TextOut(s + CRLF, DARKTHEME_TXT);
			}
			nMarkStart = nMarkEnd;
		}
		nLineBeginPos += SLINE.GetLength()-1;
	}
	m_richEdit.UnlockWindowUpdate(); //일시적으로 윈도우 업데이트 금지(고속처리를 위해 필요)
}


/*------------------------------------------------------------------------------*/
//	Input Sample
/*------------------------------------------------------------------------------*/
void CRegexStudyDlg::OnCbnSelchangeCombo2()
{
	CString s;
	int nSel = m_cbInputSample.GetCurSel();
	switch (nSel)
	{
	case 0:
		s = _T("안녕하세요? Hello, everybody! 大家好！") _T("\r\n")
			_T("It was created by Young Taek, Lim. iscool2@gmail.com") _T("\r\n")
			_T("Sunday Monday Tuesday Wednesday Thursday Friday Saturday It's my day") _T("\r\n")
			_T("File file EDIT CopyFile Filezilla Apple is not apple") _T("\r\n")
			_T("PLC Local Adress should be 192.168.0.1 and SM 255.255.255.0 Gateway 172.16.0.1") _T("\r\n")
			_T("Invalid IP = 300.168.0.1 or 192.168.0 or 192.168.0.1.2 192.168.0.1/24 ") _T("\r\n")
			_T("TEST-NET-1 Spec ") _T("\r\n")
			_T("010-1234-5678; 010-3333-7788; +82)010-1234-5678") _T("\r\n")
			_T("2055-8200~1 <fax>2055-8229; 2055-8202~4; 2055-8213; 2055-8210") _T("\r\n")
			_T("111 1024 -3500 +222 123456789") _T("\r\n")
			_T("0.5 55.77 555 555.777 3.141592 -3.141592 010.005") _T("\r\n")
			_T("hacker22@hanmail.net") _T("\r\n")
			_T("User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64)Chrome") _T("\r\n")
			_T("Accept-Encoding: gzip, deflate") _T("\r\n")
			_T("Server : Microsoft - IIS / 8.5") _T("\r\n")
			_T("Set - Cookie : 5f17001adb80f = 1595342874;") _T("\r\n")
			_T("X - Powered - By : ASP.NET") _T("\r\n")
			_T("Date : Tue, 21 Jul 2020 14 : 47 : 53 GMT") _T("\r\n")
			_T("Content - Length : 175150")
			;
		break;

	case 1:
		s = _T("10 : 56 : 38.272 MiscSEQ : Mover Move to 2F LEFT Align Started") _T("\r\n")
			_T("10 : 56 : 38.573 MMT_MoveAbsolute : OK. (MoverID = 827, Pos = 2167.0)") _T("\r\n")
			_T("10 : 56 : 38.580 MiscSEQ : Mover827, Move to  P10 OK") _T("\r\n")
			_T("10 : 56 : 38.590 MMT_MoveAbsolute : OK. (MoverID = 828, Pos = 3067.0)") _T("\r\n")
			_T("10 : 56 : 38.597 MiscSEQ : Mover828, Move to  P09 OK") _T("\r\n")
			_T("10 : 56 : 38.607 MMT_MoveAbsolute : OK. (MoverID = 829, Pos = 3967.0)") _T("\r\n")
			_T("10 : 56 : 38.614 MiscSEQ : Mover829, Move to  P08 OK") _T("\r\n")
			_T("10 : 56 : 38.623 MMT_MoveAbsolute : OK. (MoverID = 830, Pos = 4867.0)") _T("\r\n")
			_T("10 : 56 : 38.680 MiscSEQ : Mover830, Move to  P07 OK") _T("\r\n")
			_T("10 : 56 : 38.689 MMT_MoveAbsolute : Failed! (MoverID = 831, Pos = 5767.0)") _T("\r\n")
			_T("10 : 56 : 38.696 MiscSEQ : Mover831, Move to  P06 Failed!") _T("\r\n")
			_T("10 : 56 : 38.705 MMT_MoveAbsolute : Failed! (MoverID = 832, Pos = 6667.0)") _T("\r\n")
			_T("10 : 56 : 38.713 MiscSEQ : Mover832, Move to  P05 Failed!") _T("\r\n")
			_T("10 : 56 : 38.723 MMT_MoveAbsolute : OK. (MoverID = 833, Pos = 7567.0)") _T("\r\n")
			_T("10 : 56 : 38.730 MiscSEQ : Mover833, Move to  P04 OK") _T("\r\n")
			_T("10 : 56 : 38.739 MMT_MoveAbsolute : OK. (MoverID = 834, Pos = 8467.0)") _T("\r\n")
			_T("10 : 56 : 38.747 MiscSEQ : Mover834, Move to  P03 OK") _T("\r\n")
			_T("10 : 56 : 38.756 MMT_MoveAbsolute : Failed! (MoverID = 835, Pos = 9367.0)") _T("\r\n")
			_T("10 : 56 : 38.813 MiscSEQ : Mover835, Move to  P02 Failed!") _T("\r\n")
			_T("10 : 56 : 38.823 MMT_MoveAbsolute : OK. (MoverID = 843, Pos = 10267.0)") _T("\r\n")
			_T("10 : 56 : 38.830 MiscSEQ : Mover843, Move to  P01 OK") _T("\r\n")
			_T("10 : 56 : 38.838 * ****2F ALL MOVER LEFT ALIGN : All Done * ****") _T("\r\n")
			_T("10 : 56 : 38.858 MiscSEQ : End") _T("\r\n")
			_T("10 : 57 : 07.067 MiscSEQ : Auto Unload Started") _T("\r\n")
			_T("10 : 57 : 07.083 TRACK_SET : TrackPlane() OK. (Track = 2, Slot = 1)") _T("\r\n")
			_T("10 : 57 : 07.151 MMT_MoveAbsolute : OK. (MoverID = 826, Pos = 370.0)") _T("\r\n")
			_T("10 : 57 : 09.139 MiscSEQ : Mover826, Move to P12 OK") _T("\r\n")
			_T("10 : 57 : 09.154 LIFT Control : Left Down flag change Request") _T("\r\n")
			_T("10 : 57 : 50.133 MiscSEQ : Lift Down Done") _T("\r\n")
			_T("10 : 57 : 50.138 TRACK_SET : MoverPlane() OK. (Track = 2, Slot = 0)") _T("\r\n")
			_T("10 : 57 : 50.168 MMT_MoveAbsolute : OK. (MoverID = 826, Pos = 3967.0)") _T("\r\n")
			_T("10 : 57 : 57.548 MiscSEQ : Mover826, Move to P17 OK") _T("\r\n")
			_T("10 : 57 : 57.577 MiscSEQ : Lift Up") _T("\r\n")
			_T("10 : 57 : 57.581 LIFT Control : Left Up flag change Request") _T("\r\n")
			_T("10 : 58 : 00.623 LIFT Control : Left Up flag change Request") _T("\r\n")
			_T("10 : 58 : 38.467 MiscSEQ : Lift Up Done") _T("\r\n")
			_T("10 : 58 : 38.473 TRACK_SET : TrackPlane() Failed! (Track = 2, Slot = 1)") _T("\r\n")
			_T("10 : 58 : 38.480 * ****AUTO UNLOAD : End * ****") _T("\r\n")
			_T("10 : 59 : 25.315 MiscSEQ : Auto Load Started") _T("\r\n")
			_T("10 : 59 : 25.319 LIFT Control : Right Down flag change Request") _T("\r\n")
			_T("11 : 00 : 06.305 MiscSEQ : Lift Down Done") _T("\r\n")
			_T("11 : 00 : 06.324 TRACK_SET : TrackPlane() OK. (Track = 4, Slot = 0)") _T("\r\n")
			_T("11 : 00 : 06.340 MMT_MoveAbsolute : Failed! (MoverID = 842, Pos = 11167.0)") _T("\r\n")
			_T("11 : 00 : 08.328 MiscSEQ : Mover842, Move to P25 OK") _T("\r\n")
			_T("11 : 00 : 08.389 LIFT Control : Right Up flag change Request") _T("\r\n")
			_T("11 : 00 : 49.284 MiscSEQ : Lift Up Done") _T("\r\n")
			_T("11 : 00 : 49.292 TRACK_SET : MoverPlane() OK. (Track = 4, Slot = 1)") _T("\r\n")
			_T("11 : 00 : 49.323 MMT_MoveAbsolute : OK. (MoverID = 842, Pos = 10267.0)") _T("\r\n")
			_T("11 : 00 : 51.312 MiscSEQ : Mover842, Move to P01 OK") _T("\r\n")
			_T("11 : 00 : 51.369 * ****AUTO LOAD : End * ****")
			;
		break;

	case 2:
		s = _T("Login email; Identifier; One - time password; Recovery code; First name; Last name; Department; Location") _T("\r\n")
			_T("rachel@example.com; 9012; 12se74; rb9012; Rachel; Booker; Sales; Manchester") _T("\r\n")
			_T("laura@example.com; 2070; 04ap67; lg2070; Laura; Grey; Depot; London") _T("\r\n")
			_T("craig@example.com; 4081; 30no86; cj4081; Craig; Johnson; Depot; London") _T("\r\n")
			_T("mary@example.com; 9346; 14ju73; mj9346; Mary; Jenkins; Engineering; Manchester") _T("\r\n")
			_T("jamie@example.com; 5079; 09ja61; js5079; Jamie; Smith; Engineering; Manchester") _T("\r\n")
			_T("booker12; rachel@example.com; 9012; Rachel; Booker") _T("\r\n")
			_T("grey07;; 2070; Laura; Grey") _T("\r\n")
			_T("johnson81;; 4081; Craig; Johnson") _T("\r\n")
			_T("jenkins46; mary@example.com; 9346; Mary; Jenkins") _T("\r\n")
			_T("smith79; jamie@example.com; 5079; Jamie; Smith")
			;
		break;

	case 3:
		s = _T("<HTML>") _T("\r\n")
			_T("    <HEAD>") _T("\r\n")
			_T("        <TITLE> Plant-o-matic Web Page </TITLE>") _T("\r\n")
			_T("    </HEAD> ") _T("\r\n")
			_T("    <BODY bgcolor=\"yellow\">     <!-- background color add to BODY tag -->") _T("\r\n")
			_T("    <!-- examples of headings -->") _T("\r\n")
			_T("        <h1> Plant-o-matic </h1>") _T("\r\n")
			_T("        <h3 align=\"right\"> New Automatic Plant Feeding and Watering System </h3>") _T("\r\n")
			_T("    <!-- examples of font tags -->") _T("\r\n")
			_T("        <p><font color=\"green\" face=\"Comic Sans MS\" size=\"2\">") _T("\r\n")
			_T("        Be the first in your neighborhood Plant-o-matic</font></p>") _T("\r\n")
			_T("        <p align=\"center\"><font color=\"#00FFFF\" face=\"arial\" size=\"5\"> Don't Wait!!</font>") _T("\r\n")
			_T("    <!-- horizontal rule or line -->") _T("\r\n")
			_T("        <hr color=\"purple\"> </p>") _T("\r\n")
			_T("    <!-- bold, underline, italics and paragraph vs break tags -->") _T("\r\n")
			_T("        This new <b>product</b> will save you <u>time</u>, <p> <em>money</em>, <br>") _T("\r\n")
			_T("        and will keep your plants <i>alive</i>. <!-- more italics -->") _T("\r\n")
			_T("        <p>") _T("\r\n")
			_T("    <!-- link example site on the internet -->") _T("\r\n")
			_T("        <a href=\"http://www.google.com\">GOOGLE it yourself! </a>") _T("\r\n")
			_T("        <p>") _T("\r\n")
			_T("    <!-- link example email -->") _T("\r\n")
			_T("        <a href=\"mailto:ism3011@coba.usf.edu\">or email for a testimonial.</a>") _T("\r\n")
			_T("        <p>") _T("\r\n")
			_T("    <!-- link example web page in your folder -->") _T("\r\n")
			_T("        <a href=\"example2.html\"> also see our Tree-o-matic product </a>") _T("\r\n")
			_T("        <p>") _T("\r\n")
			_T("    <!-- unordered list example -->") _T("\r\n")
			_T("        Recommended by:") _T("\r\n")
			_T("        <ul>") _T("\r\n")
			_T("        <li>Nursery owners across the country</li>") _T("\r\n")
			_T("        </ul>") _T("\r\n")
			_T("    </BODY>") _T("\r\n")
			_T("</HTML>")
			;

	case 4:
		s = _T("G1 X706.667302666667 Y427.420514") _T("\r\n")
			_T("G1 X306.517903333333 Y393.618880666666") _T("\r\n")
			_T("G1 X706.667302666667 Y196.279458") _T("\r\n")
			_T("g1 X706.667302666667 Y95.7889139999997") _T("\r\n")
			_T(" ") _T("\r\n")
			_T("G00 Z5.000000") _T("\r\n")
			_T("g00 X2543.548518 Y8481.323367") _T("\r\n")
			_T(" ") _T("\r\n")
			_T("G01 Z -0.125000 F100.0") _T("\r\n")
			_T("G01 X2662.507227 Y8362.364680 Z -0.125000 F400.000000") _T("\r\n")
			_T("G00 Z5.000000")
			;
		break;
	}


	m_editInput.SetWindowText(s);
}



void CRegexStudyDlg::OnBnClickedCheckOutputmode()
{
	OnEnChangeEdit1();
}
