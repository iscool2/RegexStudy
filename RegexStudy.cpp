
// RegexStudy.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "RegexStudy.h"
#include "RegexStudyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegexStudyApp

BEGIN_MESSAGE_MAP(CRegexStudyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRegexStudyApp construction

CRegexStudyApp::CRegexStudyApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CRegexStudyApp object

CRegexStudyApp theApp;


// CRegexStudyApp initialization

BOOL CRegexStudyApp::InitInstance()
{
// TODO: richedit2 라이브러리를 초기화하려면 AfxInitRichEdit2()을(를) 호출합니다.\n"	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	
	GetApplicationInfo();

	GETMODULEPATH();

	AfxEnableControlContainer();
	//---------------------------------------------------------
	// 2024.12.29 ytlim. added. for using MFC RichEdit Control
	AfxInitRichEdit();
	//---------------------------------------------------------

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CRegexStudyDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


/*-----------------------------------------------------------------------------------------------*/
//	리소스에서 Binary 추출하여 파일에 기록해줌
//	hFile=파일핸들로서 아래처럼 파일을 생성한후 본 함수를 호출하도록 함
//		HANDLE hFile = CreateFile((LPCTSTR)sPath,GENERIC_ALL,0,0,CREATE_ALWAYS,0,0);
//	sResFolder=리소스가 포함된 리소스 뷰상의 폴더명
//	nID=리소스 ID
//	<주의!>
//	확장자 .exe 이고, 기록하는 파일이 이미 실행상태라면 Write안될수 있으므로,
//  if(PathFileExists(sPath1)==false) {...} 
//  이런 식으로 먼저 검사하여 존재하지 않을때만 본 함수를 호출하라!!!
/*-----------------------------------------------------------------------------------------------*/
BOOL CRegexStudyApp::ExtractBinFileFromResource(HANDLE hFile, CString sResFolder, int nID)
{
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	//(1)---리소스 사용을 위해 리소스를 lock 해둠
	HRSRC h = FindResource(0/*AfxGetResourceHandle()*/, MAKEINTRESOURCE(nID), (LPCTSTR)sResFolder);
	HANDLE hRes = LoadResource(0, h);
	CONST CHAR* p = (CONST CHAR*)LockResource(hRes);

	//(2)---extract binary data
	DWORD dw, cb = SizeofResource(0, h);
	WriteFile(hFile, p, cb, &dw, 0);
	FlushFileBuffers(hFile);

	//(3)---It's very important to avoid file sharing right
	CloseHandle(hFile);

	//(4)--- unlock my resources
	UnlockResource(hRes);
	return TRUE;
}

/*-------------------------------------------------------------------------*/
//	현재 실행파일의 패스를 얻어옴.
//	예) // "C:\Project\ABC\Debug\"
/*-------------------------------------------------------------------------*/
void CRegexStudyApp::GETMODULEPATH()
{
	// make current executable file info
	TCHAR path[_MAX_DIR];				// "C:\Project\ABC\Debug\test.exe"
	TCHAR cbuf[_MAX_DIR] = { 0 };
	TCHAR m_cModulePath[_MAX_DIR];		// "C:\Project\ABC\Debug\"
	m_cModulePath[0] = NULL;

	::GetModuleFileName(GetModuleHandle(NULL), path, _MAX_DIR);

	// path => "C:\Project\TESTCOM\TESTCOM\.\Debug\TESTCOM.exe"  처럼
	// "\.\" 으로 나뉘는 경우가 있다. 이것을 "\" 으로 변경하자!
	CString s = path;
	s.Replace(_T("\\.\\"), _T("\\"));
	m_sModulePath = s.Left(s.ReverseFind(_T('\\')));
	m_sModulePath += _T("\\");
}

/*-------------------------------------------------------------------------*/
//	PC에 저장된 텍스트 파일을 읽어서 그 형식과 관계없이 스트링으로 얻어오는 함수
/*-------------------------------------------------------------------------*/
CString CRegexStudyApp::READ_UNICODE_FILE(CString sFileName)
{
	enum encoding { ANSI, UTF8, UTF8_BOM, UTF16_LE, UTF16_BE };
	encoding enc = ANSI;
	CString sContent;

	CString sFilePath = sFileName;
	CFile hFile;
	if (hFile.Open(sFilePath, CFile::modeRead))
	{
		int nLen = (int)hFile.GetLength();
		TCHAR* pData = new TCHAR[nLen + 2];
		memset(pData, 0, (nLen + 2));

		LONG nReadSize = hFile.Read(pData, nLen);
		if (nReadSize == nLen)
		{
			// 인코딩 검사
			char* szBOM = new char[3];
			memset(szBOM, 0, 3);
			memmove(szBOM, (char*)pData, 3);

			unsigned char littleEndianBOM[] = { 0xFF, 0xFE };
			unsigned char bigEndianBOM[] = { 0xFE, 0xFF };
			unsigned char utf8BOM[] = { 0xEF, 0xBB, 0xBF };

			unsigned char* lpHeader = (unsigned char*)szBOM;

			if (lpHeader[0] == littleEndianBOM[0] && lpHeader[1] == littleEndianBOM[1])
				enc = encoding::UTF16_LE;
			else if (lpHeader[0] == bigEndianBOM[0] && lpHeader[1] == bigEndianBOM[1])
				enc = encoding::UTF16_BE;
			else if (lpHeader[0] == utf8BOM[0] && lpHeader[1] == utf8BOM[1] && lpHeader[2] == utf8BOM[2])
				enc = encoding::UTF8_BOM;
			else
			{
				// 위 3가지 경우가 아닐 경우 파일 내용을 분석해 UTF8과 Ansi를 구분함
				if (IsUTF8((const void*)pData, nLen))
					enc = encoding::UTF8;
			}

			// 인코딩 처리
			WCHAR* pBuffer = new WCHAR[nLen + 2];
			memset(pBuffer, 0, nLen + 2);

			switch (enc)
			{
			case ANSI:
			{
				int nLength = MultiByteToWideChar(CP_ACP, 0, (char*)pData, nLen, NULL, NULL);
				memset(pBuffer, 0, sizeof(WCHAR) * (nLength + 1));
				MultiByteToWideChar(CP_ACP, 0, (char*)pData, nLen, pBuffer, nLength);
				break;
			}
			case UTF8:
			{
				int nLength = MultiByteToWideChar(CP_UTF8, 0, (char*)pData, nLen, NULL, NULL);
				memset(pBuffer, 0, sizeof(WCHAR) * (nLength + 1));
				MultiByteToWideChar(CP_UTF8, 0, (char*)pData, nLen, pBuffer, nLength);
				break;
			}
			case UTF8_BOM:
			{
				int nLength = MultiByteToWideChar(CP_UTF8, 0, (char*)pData + 3, nLen - 3, NULL, NULL);
				memset(pBuffer, 0, sizeof(WCHAR) * (nLength + 1));
				MultiByteToWideChar(CP_UTF8, 0, (char*)pData + 3, nLen - 3, pBuffer, nLength);
				break;
			}
			case UTF16_LE:
			{
				wcscpy_s(pBuffer, nLen + 2, (WCHAR*)pData + 1);
				break;
			}
			case UTF16_BE:
			{
				wcscpy_s(pBuffer, nLen + 2, (WCHAR*)pData + 1);

				// Swap Byte
				WCHAR ch;
				WCHAR* tmpBuf = new WCHAR[nLen + 2];
				memset(tmpBuf, 0, nLen + 2);
				memmove(tmpBuf, pBuffer, nLen);

				int nPos = 0;
				while (nPos <= nLen)
				{
					ch = pBuffer[nPos];
					if (ch == 0x00)
					{
						memcpy(pBuffer, tmpBuf, nLen);
						break;
					}

					tmpBuf[nPos++] = MAKEWORD(HIBYTE(ch), LOBYTE(ch));
				}

				delete[] tmpBuf;
				break;
			}
			default:
				break;
			}

			sContent = (CString)pBuffer;

			delete[] szBOM;
			delete[] pData;
			delete[] pBuffer;
		}
	}
	hFile.Close();

	return sContent;
}

/*-------------------------------------------------------------------------*/
//	PC에 저장된 텍스트 파일의 첫머리를 얻어서 유니코드인지 아닌지를 평가하는 함수
/*-------------------------------------------------------------------------*/
bool CRegexStudyApp::IsUTF8(const void* pBuffer, long size)
{
	bool bUTF8 = true;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
	while (start < end)
	{
		if (*start < 0x80) // (10000000)[output][/output]
		{
			start++;
		}
		else if (*start < (0xC0)) // (11000000)
		{
			bUTF8 = false;
			break;
		}
		else if (*start < (0xE0)) // (11100000)
		{
			if (start >= end - 1)
				break;
			if ((start[1] & (0xC0)) != 0x80)
			{
				bUTF8 = false;
				break;
			}
			start += 2;
		}
		else if (*start < (0xF0)) // (11110000)
		{
			if (start >= end - 2)
				break;
			if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
			{
				bUTF8 = false;
				break;
			}
			start += 3;
		}
		else
		{
			bUTF8 = false;
			break;
		}
	}
	return bUTF8;
}
/**
- 빌드시 Application 에서 설정한 실행파일 정보를 얻어온다.
- Get the executable file information set by the application at the time of build.
- 获取应用程序在构建时设置的可执行文件信息。
*/
bool CRegexStudyApp::GetApplicationInfo()
{
	DWORD	dwVER = 0;
	TCHAR	cBuf[64];
	CString	sBuffer;

	//-----get information from the resource file
	m_sApplicationInfo[0] = GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\ProductName"));
	//version number
	wsprintf(cBuf, _T("%s"), GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\FileVersion")));
	m_sApplicationInfo[1] = cBuf;
	m_sApplicationInfo[2] = GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\CompanyName"));
	m_sApplicationInfo[3] = GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\FileDescription"));
	m_sApplicationInfo[4] = GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\LegalCopyright"));
	m_sApplicationInfo[5] = GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\Comments"));
	m_sApplicationInfo[6] = GETAPP()->GetVsVersionInfo(_T("\\StringFileInfo\\%04x%04x\\InternalName"));
	return 0;
}

/*-----------------------------------------------------------------------------------------------*/
//	Get the application executable file information.
//	It needs version.lib.
/*-----------------------------------------------------------------------------------------------*/
/**
- Get the application executable file information. It needs version.lib.
@param		CString	sKey version key string you want to read.
@return		CString result string
*/
CString CRegexStudyApp::GetVsVersionInfo(CString sKey)
{
	BYTE* block;
	DWORD FAR* trans;
	DWORD FAR* buffer;
	DWORD		handle;
	UINT		bytes;
	TCHAR* lpszFileName = _T("RegexStudy.exe");
	TCHAR		name[512];
	CString		strReturn = _T("");


	//(1)-----현재실행중인 process의 이름을 얻어온다.

	//(2)-----Get Version information size
	bytes = (UINT)::GetFileVersionInfoSize(lpszFileName, &handle);

	if (bytes != 0)
	{
		block = new BYTE[bytes];
		//Get Version Data
		if (::GetFileVersionInfo(lpszFileName, handle, bytes, block))
		{
			if (::VerQueryValue(block,
				_T("\\VarFileInfo\\translation"),
				(LPVOID*)&trans, 
				(UINT FAR*) & bytes) )
			{
				// Product Name
				wsprintf(name, (sKey), LOWORD(*trans), HIWORD(*trans));
				if (::VerQueryValue(block, name, (LPVOID*)&buffer, (UINT FAR*) & bytes))
					strReturn.Format(_T("%s"), (LPCTSTR)buffer);
			}
		}
		delete[] block;
	}
	return strReturn;
}
