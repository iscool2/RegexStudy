https://m2.material.io/design/color/the-color-system.html#tools-for-picking-colors


//===============================================
//이메일 스트링 체크
//===============================================
#include <regex>
int BUF_SIZE = 80;
char* buf = (char*)malloc(sizeof(char)*BUF_SIZE);
strcpy_s(buf, BUF_SIZE, "aaa@aaa.com");
std::tr1::regex email("[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*.[a-zA-Z]{2,3}");

if (std::tr1::regex_match(buf, email) == false) printf( "입력하신 Email 값이 E-mail의 형식에 맞지 않습니다.");


=======================================================
지침
애플리케이션은 여러 줄 편집 컨트롤의 인스턴스를 만들고 초기화한 다음 사용자 편집 명령을 처리하는 코드를 포함해야 합니다.

다음 C++ 코드 예는 창의 클라이언트 영역에 여러 줄 편집 컨트롤을 추가하여 간단한 워드 프로세서의 많은 기능을 구현합니다. 시스템은 자동으로 편집 컨트롤에 대한 줄 바꿈 작업을 수행하고 세로 스크롤 막대에 대한 처리도 처리합니다(CreateWindow 함수 호출에서 ES_AUTOVSCROLL을 지정하여 만들어짐).

사용자 편집 명령은 WM_COMMAND 알림 메시지를 통해 창 프로세스로 전송됩니다.
C++

복사
#define ID_EDITCHILD 100
 
LRESULT CALLBACK MainWndProc(HWND hwnd,      // window handle 
                             UINT message,   // type of message 
                             WPARAM wParam,  // additional information 
                             LPARAM lParam)  // additional information 
{ 
    static HWND hwndEdit; 
 
    TCHAR lpszLatin[] =  L"Lorem ipsum dolor sit amet, consectetur "
                         L"adipisicing elit, sed do eiusmod tempor " 
                         L"incididunt ut labore et dolore magna " 
                         L"aliqua. Ut enim ad minim veniam, quis " 
                         L"nostrud exercitation ullamco laboris nisi " 
                         L"ut aliquip ex ea commodo consequat. Duis " 
                         L"aute irure dolor in reprehenderit in " 
                         L"voluptate velit esse cillum dolore eu " 
                         L"fugiat nulla pariatur. Excepteur sint " 
                         L"occaecat cupidatat non proident, sunt " 
                         L"in culpa qui officia deserunt mollit " 
                         L"anim id est laborum."; 
 
    switch (message) 
    { 
        case WM_CREATE: 
            hwndEdit = CreateWindowEx(
                                0, L"EDIT",   // predefined class 
                                NULL,         // no window title 
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
                                ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
                                0, 0, 0, 0,   // set size in WM_SIZE message 
                                hwnd,         // parent window 
                                (HMENU) ID_EDITCHILD,   // edit control ID 
                                (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), 
                                NULL);        // pointer not needed 
 
            // Add text to the window. 
            SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpszLatin); 
 
            return 0; 
 
        case WM_COMMAND: 
            switch (wParam) 
            { 
                case IDM_EDUNDO: 
                    // Send WM_UNDO only if there is something to be undone. 
 
                    if (SendMessage(hwndEdit, EM_CANUNDO, 0, 0)) 
                        SendMessage(hwndEdit, WM_UNDO, 0, 0); 
                    else 
                    {
                        MessageBox(hwndEdit, 
                                   L"Nothing to undo.", 
                                   L"Undo notification", 
                                   MB_OK); 
                    }
                    break; 
 
                case IDM_EDCUT: 
                    SendMessage(hwndEdit, WM_CUT, 0, 0); 
                    break; 
 
                case IDM_EDCOPY: 
                    SendMessage(hwndEdit, WM_COPY, 0, 0); 
                    break; 
 
                case IDM_EDPASTE: 
                    SendMessage(hwndEdit, WM_PASTE, 0, 0); 
                    break; 
 
                case IDM_EDDEL: 
                    SendMessage(hwndEdit, WM_CLEAR, 0, 0); 
                    break; 

                case IDM_ABOUT: 
                    DialogBox(hInst,                // current instance 
                              L"AboutBox",           // resource to use 
                              hwnd,                 // parent handle 
                              (DLGPROC) About); 
                    break; 

                default: 
                    return DefWindowProc(hwnd, message, wParam, lParam); 
            } 
            break; 

        case WM_SETFOCUS: 
            SetFocus(hwndEdit); 
            return 0; 

        case WM_SIZE: 
            // Make the edit control the size of the window's client area. 

            MoveWindow(hwndEdit, 
                       0, 0,                  // starting x- and y-coordinates 
                       LOWORD(lParam),        // width of client area 
                       HIWORD(lParam),        // height of client area 
                       TRUE);                 // repaint window 
            return 0; 

        case WM_DESTROY: 
            PostQuitMessage(0); 
            return 0; 

        default: 
            return DefWindowProc(hwnd, message, wParam, lParam); 
    } 
    return NULL; 
}

//=========================================================================
#include <sstream>

#ifdef _UNICODE
typedef std::wstring tstring;
typedef std::wstringstream tstringstream;
#else
typedef std::string tstring;
typedef std::stringstream tstringstream;
#endif

int i = 5;
tstring s;
tstringstream out;
out << i;
s = out.str();
//At this point, s is a std::string (or std::wstring) that contains the number as a string.
//Use it with SetDlgItemText().
SetDlgItemText(theDlgWnd, theEditID, s.c_str());

I imagine that you want to keep the previous string and just append the new one. In this case I would keep the entire string myself, concatenate, and then pass to the control with WM_SETTEXT.

-----------------------------------------------------------------------------
//At procedure level, or maybe file level, you declare:
tstring strConversation;

//Then you append to this string variable any new text.  Let's assume there is a function for that.
void AppendNewText(tstring &newText)
{
    strConversation += strConversation.size() ? TEXT("\r\n") : TEXT("");
    strConversation += newText;
    //Finally, you set the text in the control.  This may or may not be appropriate here.
    SendMessage(myEditControl, WM_SETTEXT, 0, strConversation.c_str());
}


EDIT: I just remembered that you use SetDlgItemText():

SetDlgItemText(theDlgWnd, theEditID, strConversation.c_str());

//==========================================================================================
#include <iostream>
#include <format>
#include <limits>

// use C++ min/max functions, not Windows
#define NOMINMAX
#include <windows.h>

int main( )
{
   LARGE_INTEGER frequency;
   LARGE_INTEGER a;
   LARGE_INTEGER b;

   QueryPerformanceFrequency( &frequency );
   std::cout << std::format("Frequency: {} Ticks-Per-Second\n", frequency.QuadPart );

   QueryPerformanceCounter( &a );
   std::cout << std::format("A: {}\n", a.QuadPart );

   QueryPerformanceCounter( &b );
   std::cout << std::format("B: {}\n", b.QuadPart );

   float elapsed_seconds = static_cast< float >( b.QuadPart - a.QuadPart ) / frequency.QuadPart;
   std::cout << std::format("Elapsed time (B-A): {}\n", elapsed_seconds );

   std::cout << "\nPress ENTER to continue...";
   std::cin.clear( );
   std::cin.sync( );
   std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
}

//result:
Frequency: 10000000 Ticks-Per-Second
A: 2996187775081
B: 2996187778131
Elapsed time (B-A): 0.000305

Press ENTER to continue...

//=========================================================================================
Supported Regular Expression Syntax
The following tables are copied from MSDN. You can note that the syntax is not exactly the same as in Perl. For example, the grouping operator is {}, while in Perl it is (), and it doesn't have the {n} (match exactly n times) as in the Perl syntax<.

Metacharacter	Meaning
.	Matches any single character.
[ ]	Indicates a character class. Matches any character inside the brackets (for example, [abc] matches "a", "b", and "c").
^	If this metacharacter occurs at the start of a character class, it negates the character class. A negated character class matches any character except those inside the brackets (for example, [^abc] matches all characters except "a", "b", and "c").
If ^ is at the beginning of the regular expression, it matches the beginning of the input (for example, ^[abc] will only match input that begins with "a", "b", or "c").

-	In a character class, indicates a range of characters (for example, [0-9] matches any of the digits "0" through "9").
?	Indicates that the preceding expression is optional: it matches once or not at all (for example, [0-9][0-9]? matches "2" and "12").
+	Indicates that the preceding expression matches one or more times (for example, [0-9]+ matches "1", "13", "666", and so on).
*	Indicates that the preceding expression matches zero or more times.
??, +?, *?	Non-greedy versions of ?, +, and *. These match as little as possible, unlike the greedy versions which match as much as possible. Example: given the input "<abc><def>", <.*?> matches "<abc>" while <.*> matches "<abc><def>".
( )	Grouping operator. Example: (\d+,)*\d+ matches a list of numbers separated by commas (such as "1" or "1,23,456").
{ }	Indicates a match group. The actual text in the input that matches the expression inside the braces can be retrieved through the CAtlREMatchContext object.
\	Escape character: interpret the next character literally (for example, [0-9]+ matches one or more digits, but [0-9]\+ matches a digit followed by a plus character). Also used for abbreviations (such as \a for any alphanumeric character; see table below).
If \ is followed by a number n, it matches the nth match group (starting from 0). Example: <{.*?}>.*?</\0> matches "<head>Contents</head>".

Note that in C++ string literals, two backslashes must be used: "\\+", "\\a", "<{.*?}>.*?</\\0>".

$	At the end of a regular expression, this character matches the end of the input. Example: [0-9]$ matches a digit at the end of the input.
|	Alternation operator: separates two expressions, exactly one of which matches (for example, T|the matches "The" or "the").
!	Negation operator: the expression following ! does not match the input. Example: a!b matches "a" not followed by "b".
CAtlRegExp can handle abbreviations, such as \d instead of [0-9]. The abbreviations are provided by the character traits class passed in the CharTraits parameter. The predefined character traits classes provide the following abbreviations:

Abbreviation	Matches
\a	Any alphanumeric character: ([a-zA-Z0-9])
\b	White space (blank): ([ \\t])
\c	Any alphabetic character: ([a-zA-Z])
\d	Any decimal digit: ([0-9])
\h	Any hexadecimal digit: ([0-9a-fA-F])
\n	Newline: (\r|(\r?\n))
\q	A quoted string: (\"[^\"]*\")|(\'[^\']*\')
\w	A simple word: ([a-zA-Z]+)
\z	An integer: ([0-9]+)
Using the code
Although CAtlRegExp is part of the ATL server classes, you don't have to be an ATL project in order to use this class, simply #include "atlrx.h" is enough.

I have written a simple Dialog based program to test/demo the CAtlRegExp. The core of the program is listed as follows:

Shrink ▲   
// create regular expression content

CAtlRegExp<> regex;
REParseError status = regex.Parse(m_szRegex, m_bCaseSensitive);

if (REPARSE_ERROR_OK != status) {
  // invalid pattern, show error

  m_szStatus = TEXT("Parser Error: ");
  m_szStatus += REError2String(status);
} else {
  // valid regex pattern, now try to match the content

  CAtlREMatchContext<> mc;
  if (!regex.Match(m_szInput, &mc)) {
    // content not match

    m_szStatus = TEXT("No match");
  } else {
    // content match, show match-group

    m_szStatus = TEXT("Success match");
    for (UINT nGroupIndex = 0; nGroupIndex < mc.m_uNumGroups; 
         ++nGroupIndex) {
      const CAtlREMatchContext<>::RECHAR* szStart = 0;
      const CAtlREMatchContext<>::RECHAR* szEnd = 0;
      mc.GetMatch(nGroupIndex, &szStart, &szEnd);
      ptrdiff_t nLength = szEnd - szStart;
      CString text(szStart, nLength);
      m_ctrlListBox.AddString(text);
    }
  }
}
And the function REError2String is listed as follows:

Shrink ▲   
// refer to REParseError for more information

CString CMfcRegexDlg::REError2String(REParseError status)
{
  switch (status) {
    case REPARSE_ERROR_OK:
         return TEXT("No error occurred");
    case REPARSE_ERROR_OUTOFMEMORY:
         return TEXT("Out of memory");
    case REPARSE_ERROR_BRACE_EXPECTED:
         return TEXT("A closing brace was expected");
    case REPARSE_ERROR_PAREN_EXPECTED:
         return TEXT("A closing parenthesis was expected");
    case REPARSE_ERROR_BRACKET_EXPECTED:
         return TEXT("A closing bracket was expected");
    case REPARSE_ERROR_UNEXPECTED:
         return TEXT("An unspecified fatal error occurred");
    case REPARSE_ERROR_EMPTY_RANGE:
         return TEXT("A range expression was empty");
    case REPARSE_ERROR_INVALID_GROUP:
         return TEXT("A back reference was made to a group" 
                     " that did not exist");
    case REPARSE_ERROR_INVALID_RANGE:
         return TEXT("An invalid range was specified");
    case REPARSE_ERROR_EMPTY_REPEATOP:
         return TEXT("A repeat operator (* or +) was applied" 
                     " to an expression that could be empty");
    case REPARSE_ERROR_INVALID_INPUT:
         return TEXT("The input string was invalid");
    default: return TEXT("Unknown error");
  }
}
Special note about MBCS
By default, CAtlRegExp uses CAtlRECharTraits, which is CAtlRECharTraitsA for non-Unicode version. 
However, unless you are using strict and pure ASCII, you should use CAtlRECharTraitsMB; 
otherwise, you may encounter some un-expected results in non-ASCII text. 
For example, the Chinese character for Chinese Character ("word") in Big5 encoding is the two byte word "\0xA6 r", 
which has a 'r' in as the second byte.




//====================================================================================================
MFC EditBox에 한글을 입력하다가 ( 즉, 조립중인 문자열이 발생되어 질때 )
LButtonClick 과 같은 이벤트가 발생하였을 때, EditBox에 Caption을 엎어쳐 주게되면,
순간적으로는 Caption의 내용이 정상적으로 엎어쳐 진 것 같다. 
하지만..........
다른 컨트롤을 선택해보면, ( Invalidate() 가 호출되면 )
사실은 EditBox의 Caption에는 엎어쳐준것과 조립중이던 문자열의 조합으로
이상한 쓰레기 값이 들어오게 된다.
이 이유는 한글을 입력할때에는, 조립중인 문자열이 발생하는 것을 윈도우 핸들이 저장하고 있다가
모든 것이 끝나면, 그 내용을 출력해주기 때문이다.
이를 해결하는 방법을 알아보자
일단 LbuttonClick 이벤트가 발생되어지는 Cpp 파일내에
imm.h 헤더를 추가해주자.
그리고 나서 프로젝트 link에 imm32.lib를 추가해주자
그 후에 Button이 클릭되는 시점
HIMC hImc;
hImc = ImmGetContext(m_hWnd);
ImmNotifyIME(hImc,NI_COMPOSITIONSTR,CPS_CANCEL,0);
ImmReleaseContext(m_hWnd, hImc);
코드를 추가하면 끝! 올레!!


//====================================================================================================
[MFC] EditBox 한글이 초기에 적어지도록 셋팅
editbox 컨트롤에서 커서를 놓고 글을 적기 시작하면 무조건 디폴트로 영문먼져 써집니다.
한글만 입력해야하는  editbox에서는 매번 포커스를 해당 editbox에 놓을때마다
한영키를 눌러줘야하는 불편함이 있죠 이런 불편함을 해결하는 방법을 소개 합니다.

1. imm32.lib 라이브러리 추가 (프로젝트 속성또는 소스코드에)
2. #include <imm.h> 추가 (전역클레스에 추가 Stdafx.h)
3. 해당 Edit Box에 SetFocus를 이벤트 함수를 아래와 같이 추가 한다.
void CTestDlg::OnSetfocusMessageEdit()
{

    HIMC himc=ImmGetContext(GetDlgItem(IDC_EDIT1)->GetSafeHwnd());
    ImmSetConversionStatus(himc, IME_CMODE_NATIVE,IME_SMODE_CONVERSATION);
    ImmReleaseContext(GetDlgItem(IDC_EDIT1)->GetSafeHwnd(),himc);   
}

//====================================================================================================
Changing Fonts in RichEdit Control
To Sanjeet

Try this.

int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
if (CRichEditView::OnCreate(lpCreateStruct) == -1)
return -1;

CHARFORMAT cfDefault;
cfDefault.cbSize = sizeof(cfDefault);
cfDefault.dwEffects = CFE_PROTECTED;
cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
cfDefault.yHeight = 12 * 20;
cfDefault.crTextColor = RGB(255,255,0);
cfDefault.bCharSet = 0;
strcpy( cfDefault.szFaceName, _T("Courier New") );// or "Times New Roman" etc etc

GetRichEditCtrl().SetDefaultCharFormat(cfDefault);
GetRichEditCtrl().SetEventMask(ENM_CHANGE | ENM_SELCHANGE | ENM_PROTECTED);
GetRichEditCtrl().SetBackgroundColor( FALSE, RGB(0,0,0) );

return 0;
}


//====================================================================================================
partially change color of text in edit control?
I would like to change the color of a substring in the edit box. Is that possible?

For Example:
All is black except this is Blue

I am using OnCtrlColor() to change colors and I am able to change single color for the whole edit box.

Thanks

Assuming u r using MFC, try this:

1. Instead of CEditControl use CRichEditCtrl;
2. In InitInstance do this before you instantiate the dialog object.
AfxEnableControlContainer();
AfxInitRichEdit();
3. In OnInitDialog add this code:

// TODO: Add extra initialization here
m_oRichEdit.SetWindowText(_T("hello world !! This is a test string"));
m_oRichEdit.SetSel(0,5);//select hello as the word to be formatted with different color
CHARFORMAT cf;
cf.cbSize = sizeof(CHARFORMAT);
cf.dwMask = CFM_COLOR;
cf.crTextColor = RGB(255,0,0);
cf.dwEffects = 0;//we do not want CFE_AUTOCOLOR , since this will choose GetSysColor value.
m_oRichEdit.SetWordCharFormat(cf);
m_oRichEdit.SetSel(0,0);//now, deselect text

You should see hello in RED now.

Hope this helps,
Kiran



//====================================================================================================
모두의 코드(https://modoocode.com/303#google_vignette)
씹어먹는 C++ - <17 - 2. C++ 정규 표현식(<regex>) 라이브러리 소개>
작성일 : 2020-1-3 이 글은 45361 번 읽혔습니다.
이번 강좌에서는
std::regex_match 를 이용해서 정규 표현식으로 전체 문자열 패턴 매칭하기.
std::regex_search 를 이용해서 정규 표현식으로 문자열 검색하기
std::regex_replace 를 이용해서 정규 표현식으로 문자열 치환하기
에 대해 다룹니다.


안녕하세요 여러분! 
이번 강좌에서는 C++ 11 부터 표준에 포함된 정규 표현식(regular expression) 라이브러리에 대해서 
간단하게 알아보는 시간을 가지도록 하겠습니다. 
아마 프로그래밍을 오래 하신 분들이라면 정규 표현식 자체는 아마 여러 상황에서 사용해보셨으리라 생각합니다.
정규 표현식은 문자열에서 패턴을 찾는데 사용하는데, 이를 통해
주어진 문자열이 주어진 규칙에 맞는지 확인할 때
주어진 문자열에서 원하는 패턴의 문자열을 검색할 때
주어진 문자열에서 원하는 패턴의 문자열로 치환할 때
와 같은 경우에 매우 유용하게 사용됩니다.

그렇다면 각각의 상황에 맞게 C++ 에서 제공하는 정규 표현식 라이브러리를 어떻게 사용할지 살펴봅시다.

<전체 문자열 매칭하기>
만약에 여러분이 어떠한 서버를 관리하고 있는데, 해당 서버에서 매 시간 마다 로그 파일을 생성한다고 해봅시다. 
이 때 로그 파일은 db-(시간)-log.txt 와 같은 형태로 생성된다고 합니다.
그러다면 여러 가지 파일들이 섞여 있는 폴더에서 우리가 원하는 로그 파일들만 어떻게 간단히 읽어들 수 있을까요? 
일단 정규 표현식을 사용할 줄 아는 분들이라면 위 패턴을 보고 아래와 같은 정규 표현식을 떠올리실 것입니다.

db-\d*-log\.txt

여기서 \d* 는 임의의 개수의 숫자를 의미하는 것이고, . 
앞에 \ 을 붙여준 이유는 . 을 그냥 썼을 때 임의의 문자로 해석되기 때문입니다.

그렇다면 해당 정규표현식을 바탕으로 C++ 을 통해 파일 이름이 
주어진 패턴을 만족하는지 확인하는 프로그램을 작성해보도록 하겠습니다.

#include <iostream>
#include <regex>
#include <vector>

int main() {
  // 주어진 파일 이름들.
  std::vector<std::string> file_names = {"db-123-log.txt", "db-124-log.txt",
                                         "not-db-log.txt", "db-12-log.txt",
                                         "db-12-log.jpg"};
  std::regex re("db-\\d*-log\\.txt");
  for (const auto &file_name : file_names) {
    // std::boolalpha 는 bool 을 0 과 1 대신에 false, true 로 표현하게 해줍니다.
    std::cout << file_name << ": " << std::boolalpha
              << std::regex_match(file_name, re) << '\n';
  }
}

성공적으로 컴파일 하였다면
<실행 결과>
db-123-log.txt: true
db-124-log.txt: true
not-db-log.txt: false
db-12-log.txt: true
db-12-log.jpg: false
와 같이 주어진 정규 표현식에 맞는 파일 이름들만 true 로 나옴을 볼 수 있습니다.

std::regex re("db-\\d*-log\\.txt");

C++ 에서 정규 표현식을 사용하기 위해서는 먼저 위와 같이 정규 표현식 객체를 정의해야 합니다. 
참고로 정규 표현식 문법의 종류와, 정규 표현식을 처리하는 엔진 역시 여러가지 종류가 있는데, 
위 생성자에 추가적인 인자로 전달할 수 있습니다. 예를 들어서 grep 의 정규 표현식 문법을 사용하고 싶다면
std::regex re("db-\\d*-log\\.txt", std::regex::grep);
과 같이 전달하면 됩니다. 만약에 인자를 지정하지 않았다면 디폴트로 std::regex::ECMAScript 가 들어가게 됩니다. 
어떤 문법을 사용할 지 이외에도 몇 가지 특성들을 더 추가할 수 있는데, 
예를 들어서 std::regex::icase 를 전달한다면 대소 문자를 구분하지 않게 됩니다. 
이 때 특성을 추가하는 방법은 | 로 연결하면 됩니다. 예를 들어서

std::regex re("db-\\d*-log\\.txt", std::regex::grep | std::regex::icase);와 같이 말이지요.


참고로 정규 표현식의 성능이 중요할 경우에는 std::regex::optmize 를 추가적으로 전달할 수 있습니다. 
이 경우 정규 표현식 객체를 생성하는데에는 시간이 좀 더 걸리지만 정규 표현식 객체를 사용하는 작업은 좀 더 빠르게 수행됩니다.
std::cout << file_name << ": " << std::boolalpha
          << std::regex_match(file_name, re) << '\n';
자 그렇다면 만들어진 정규식 객체를 사용하는 부분을 살펴봅시다. 
std::regex_match 는 첫 번째 인자로 전달된 문자열 (위 경우 file_name) 이 두 번째 인자로 전달된 정규 표현식 객체 (위 경우 re) 와 완전히 매칭이 된다면 true 를 리턴합니다. 완전히 매칭 된다는 말은 문자열 전체가 정규 표현식의 패턴에 부합해야 한다는 것이지요.

<부분 매칭 뽑아내기>
앞서 regex_match 를 사용해서 전체 문자열이 주어진 정규 표현식 패턴을 만족하는지 알아 낼 수 있다고 하였습니다. 
그렇다면 해당 조건을 만족하는 문자열에서 패턴 일부분 을 뽑아내고 싶다면 어떨까요?
예를 들어서 사용자로 부터 전화번호를 받는 정규 표현식을 생각해봅시다. 
전화번호는 간단히 생각해서 다음과 같은 규칙을 만족한다고 생각합니다.
(숫자)-(숫자)-(숫자) 꼴로 있어야 합니다.
맨 앞자리는 반드시 3 자리이며 0 과 1 로만 이루어져 있어야 합니다.
가운데 자리는 3 자리 혹은 4 자리 여야 합니다.
마지막 자리는 4 자리 여야 합니다.

예를 들어 아래와 같은 번호들이 조건을 만족하겠죠.
010-1234-5678
010-123-4567
011-1234-5678

그렇다면 다음과 같이 정규 표현식을 작성할 수 있겠습니다.
[01]{3}-\d{3,4}-\d{4}
맨 앞에 [01] 의 뜻은 0 혹은 1 이라는 의미이고, 뒤에 {3} 은 해당 종류의 문자가 3 번 나타날 수 있다는 의미입니다.

#include <iostream>
#include <regex>
#include <vector>

int main() {
  std::vector<std::string> phone_numbers = {"010-1234-5678", "010-123-4567",
                                            "011-1234-5567", "010-12345-6789",
                                            "123-4567-8901", "010-1234-567"};
  std::regex re("[01]{3}-\\d{3,4}-\\d{4}");
  for (const auto &number : phone_numbers) {
    std::cout << number << ": " << std::boolalpha
              << std::regex_match(number, re) << '\n';
  }
}
성공적으로 컴파일 하였다면
<실행 결과>
010-1234-5678: true
010-123-4567: true
011-1234-5567: true
010-12345-6789: false
123-4567-8901: false
010-1234-567: false
예상한 대로 잘 작동함을 알 수 있습니다.

만약에 조건에 만족하는 전화번호 중에서 가운데 번호를 추출하고 싶다면 어떨까요? 
정규 표현식을 배운 분들은 아시겠지만, 
캡쳐 그룹 (capture group) 을 사용하면 된다는 것을 알고 계실 것입니다. 
C++ 의 경우도 마찬가지 입니다.

std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");

위와 같이 () 로 원하는 부분을 감싸게 된다면 해당 부분에 매칭된 문자열을 얻을 수 있게 됩니다.
그렇다면 매칭된 부분을 어떻게 얻을 수 있는지 살펴보도록 합시다.

#include <iostream>
#include <regex>
#include <vector>

int main() {
  std::vector<std::string> phone_numbers = {"010-1234-5678", "010-123-4567",
                                            "011-1234-5567", "010-12345-6789",
                                            "123-4567-8901", "010-1234-567"};
  std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
  std::smatch match;  // 매칭된 결과를 string 으로 보관
  for (const auto &number : phone_numbers) {
    if (std::regex_match(number, match, re)) {
      for (size_t i = 0; i < match.size(); i++) {
        std::cout << "Match : " << match[i].str() << std::endl;
      }
      std::cout << "-----------------------\n";
    }
  }
}
성공적으로 컴파일 하였다면
<실행 결과>
Match : 010-1234-5678
Match : 1234
-----------------------
Match : 010-123-4567
Match : 123
-----------------------
Match : 011-1234-5567
Match : 1234
-----------------------
와 같이 나옵니다.

먼저 매칭된 문자열을 보관하는 객체를 정의한 부분 부터 설펴봅시다.
std::smatch match;
위 smatch 의 경우 매칭된 문자열을 std::string 의 형태로 돌려줍니다. 
그 외에도 const char* 로 돌려주는 cmatch 가 있습니다.
if (std::regex_match(number, match, re)) {
다음에 regex_match 에 매칭된 결과를 보관할 match 와 정규 표현식 re 를 모두 전달합니다. 
만일 number 가 re 의 패턴에 부합하다면 match 에 매칭된 결과가 들어 있을 것입니다.
for (size_t i = 0; i < match.size(); i++) {
  std::cout << "Match : " << match[i].str() << std::endl;
}
자 그럼 이제 match 에서 매칭된 문자열들을 match[i].str() 을 통해 접근할 수 있습니다. 
참고로 우리의 match 가 smatch 이므로 match[i].str() 은 std::string 이 됩니다. 
반면에 match 가 cmatch 였다면 match[i].str() 는 const char* 이 되겠지요.
참고로 regex_match 의 경우 전체 문자열이 매칭이 된 것이기 때문에 첫 번째 결과에 전체 문자열이 나타나게 됩니다. 
그 다음으로 () 안에 들어있던 문자열이 나타나게 되죠. 
만약에 정규 표현식 안에 () 가 여러개 있다면 마찬가지로 for 문을 통해 순차적으로 접근할 수 있습니다.

<원하는 패턴 검색하기>
앞서 regex_match 를 통해 문자열 전체가 패턴에 부합하는지 확인하는 작업을 하였습니다. 
이번에는 전체 말고 패턴을 만족하는 문자열 일부 를 검색하는 작업을 수행해보도록 하겠습니다.
우리가 하고 싶은 일은 HTML 문서에서 아래와 같은 형태의 태그만 읽어들이는 것입니다.
<div class="sk...">...</div>
그렇다면 해당 조건을 만족하는 정규 표현식은 아래와 같이 작성할 수 있습니다.
<div class="sk[\w -]*">\w*</div>
자 그렇다면 해당 정규 표현식을 사용해서 문자열에서 원하는 패턴을 어떻게 검색하는지 살펴보겠습니다.

#include <iostream>
#include <regex>

int main() {
  std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

  std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
  std::smatch match;
  while (std::regex_search(html, match, re)) {
    std::cout << match.str() << '\n';
    html = match.suffix();
  }
}
성공적으로 컴파일 하였다면
<실행 결과>
<div class="sk-circle1 sk-circle">a</div>
<div class="sk-circle2 sk-circle">b</div>
<div class="sk-circle3 sk-circle">asd</div>
<div class="sk-circle4 sk-circle">asdfasf</div>
<div class="sk-circle5 sk-circle">123</div>
<div class="sk-circle6 sk-circle">aax</div>
<div class="sk-circle7 sk-circle">sxz</div>
와 같이 잘 나옵니다.

while (std::regex_search(html, match, re)) {
문자열에서 원하는 패턴을 검색하는 일은 regex_search 를 사용하면 됩니다. 
regex_match 처럼, 
첫 번째에 검색을 하고픈 문자열을, 
두 번째에 일치된 패턴을 보관할 match 객체를, 
마지막 인자로 실제 정규 표현식 객체를 전달하면 됩니다. 
만일 html 에서 정규 표현식과 매칭이 되는 패턴이 존재한다면 regex_search 가 true 를 리턴하게 되지요.

std::cout << match.str() << '\n';
그리고 매칭된 패턴은 위와 같이 match.str() 을 통해서 접근할 수 있습니다. 
우리의 match 가 smatch 의 객체 이므로 만들어진 match.str() 은 string 이 됩니다.

문제는 만일 그냥 std::regex_search(html, match, re) 를 다시 실행하게 된다면 
그냥 이전에 찾았던 패턴을 다시 뱉을 것입니다. 
따라서 우리는 html 을 업데이트 해서 검색된 패턴 바로 뒤 부터 다시 검색할 수 있도록 바꿔야합니다.

html = match.suffix();
match.suffix() 를 하면 std::sub_match 객체를 리턴합니다. 
sub_match 는 단순히 어떠한 문자열의 시작과 끝을 가리키는 반복자 두 개를 가지고 있다고 보시면 됩니다. 
이 때 suffix 의 경우, 원 문자열에서 검색된 패턴 바로 뒤 부터, 
이전 문자열의 끝 까지에 해당하는 sub_match 객체를 리턴합니다.

<prefix 와 suffix 예시>
이 때 sub_match 클래스에는 string 으로 변환할 수 있는 캐스팅 연산자가 들어 있습니다. 
따라서 위와 같이 html 에 그냥 대입하게 되면 알아서 문자열로 변환되서 들어가게 됩니다. 
덕분에 이미 찾은 패턴 뒤 부터 다시 새로운 검색을 시작할 수 있겠죠.

std::regex_iterator
regex_iterator 를 사용하면 좀 더 편리하게 검색을 수행할 수 있습니다. 예를 들어서;

#include <iostream>
#include <regex>

int main() {
  std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

  std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
  std::smatch match;

  auto start = std::sregex_iterator(html.begin(), html.end(), re);
  auto end = std::sregex_iterator();

  while (start != end) {
    std::cout << start->str() << std::endl;
    ++start;
  }
}
성공적으로 컴파일 하였다면

<실행 결과>
<div class="sk-circle1 sk-circle">a</div>
<div class="sk-circle2 sk-circle">b</div>
<div class="sk-circle3 sk-circle">asd</div>
<div class="sk-circle4 sk-circle">asdfasf</div>
<div class="sk-circle5 sk-circle">123</div>
<div class="sk-circle6 sk-circle">aax</div>
<div class="sk-circle7 sk-circle">sxz</div>
와 같이 잘 나옵니다.

std::regex_iterator 는 주어진 문자열에서 정규 표현식으로 매칭된 문자열들을 쭈르륵 뽑아낼 수 있는 반복자 입니다.

auto start = std::sregex_iterator(html.begin(), html.end(), re);
regex_iterator 의 경우 위와 같이 생성자를 호출함으로써 생성할 수 있습니다. 
첫 번째와 두 번째 인자로 검색을 수행할 문자열의 시작과 끝을 전달하고, 
마지막 인자로 사용하고픈 정규 표현식 객체를 전달하면 됩니다. 
참고로 sregex_iterator 는 regex_iterator 중에서 string 을 사용하는 반복자 입니다.
regex_iterator 의 경우 처음 생성될 때와, ++ 연산자로 증감 될 때마다 regex_search 를 통해 
초기에 주어진 문자열 범위 내에서 패턴에 맞는 문자열을 검색합니다. 
또한 * 연산자를 통해서 역참조 하게 된다면 현재 검색된 패턴에 대한 match_results 객체를 얻어낼 수 있습니다.
따라서 아래와 같이 간단하게 패턴과 매칭되는 문자열들을 뽑아낼 수 있게 됩니다.

while (start != end) {
  std::cout << start->str() << std::endl;
  ++start;
}

<원하는 패턴 치환하기>
마지막으로 살펴볼 기능은 정규 표현식을 통해서 원하는 패턴의 문자열을 다른 문자열로 치환(replace)하는 작업입니다. 
해당 작업은 std::regex_replace 를 통해서 구현할 수 있습니다.
예를 들어서 html 에서 sk-circle1 과 같은 문자열을 1-sk-circle 로 바꿔보는 정규 표현식을 생각해봅시다. 
이를 위해서 먼저 sk-circle1 과 같은 형태를 어떤 regex 로 매칭 시킬지 생각해야 하는데 이는 간단히
sk-circle\d
로 할 수 있습니다. 

그 다음에, 이를 어떠한 형태로 치환할지를 생각해야 합니다. 
간단히 생각해서
숫자-sk-circle
로 해야 하는데, 문제는 위 숫자 에 해당하는 부분이 매칭된 패턴에 \d 에 해당하는 부분이라는 점입니다. 
하지만 다행이도, 캡쳐 그룹을 이용하면 이를 간단히 해결할 수 있습니다. 먼저
sk-circle(\d)
를 통해서 숫자에 해당하는 부분을 첫 번째 캡쳐그룹으로 만듧니다. 
그 다음에, 치환을 할 때 첫 번째 캡쳐 그룹을 표현하기 위해 $1 라고 명시할 수 있습니다.
(이와 같은 요소를 back reference 라고 부릅니다.) 
따라서
$1-sk-circle
과 같이 표현할 수 있습니다.
이를 바탕으로 C++ 코드를 작성해봅시다.

#include <iostream>
#include <regex>

int main() {
  std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

  std::regex re(R"r(sk-circle(\d))r");
  std::smatch match;

  std::string modified_html = std::regex_replace(html, re, "$1-sk-circle");
  std::cout << modified_html;
}
성공적으로 컴파일 하였다면
<실행 결과>
<div class="social-login">
  <div class="small-comment">다음으로 로그인 </div>
  <div>
    <i class="xi-facebook-official fb-login"></i>
    <i class="xi-google-plus goog-login"></i>
  </div>
</div>
<div class="manual">
  <div class="small-comment">
    또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
  </div>
  <input name="name" id="name" placeholder="이름">
  <input name="password" id="password" type="password" placeholder="비밀번호">
</div>
<div id="adding-comment" class="sk-fading-circle">
  <div class="1-sk-circle sk-circle">a</div>
  <div class="2-sk-circle sk-circle">b</div>
  <div class="3-sk-circle sk-circle">asd</div>
  <div class="4-sk-circle sk-circle">asdfasf</div>
  <div class="5-sk-circle sk-circle">123</div>
  <div class="6-sk-circle sk-circle">aax</div>
  <div class="7-sk-circle sk-circle">sxz</div>
</div>
와 같이 잘 나옵니다.

std::regex_replace(html, re, "$1-sk-circle");
regex_replace 로 문자열을 치환하고 싶다면 
첫 번째 인자로 치환하고자 하는 문자열을, 
두 번째 인자로 정규 표현식 객체를, 
마지막으로 치환 시에 어떠한 패턴으로 바꿀 지 적어주면 됩니다. 
regex_replace 의 오버로딩 형태는 여러가지가 있는데 위 형태의 경우 치환된 문자열을 생성해서 돌려줍니다.

만약에 치환된 문자열을 생성하지 않고 그냥 stdout 에 출력하고 싶다면;

std::regex_replace(std::ostreambuf_iterator<char>(std::cout), html.begin(),
                   html.end(), re, "$1-sk-circle");
와 같이 쓰면 됩니다. 이 경우 std::regex_replace 의 첫 번째 인자로 출력할 위치의 시작점을 가리키는 반복자를 넣어주면 됩니다.

<중첩된 캡쳐 그룹>
만약에 더 나아가서 다음과 같이 치환을 하고 싶다 해봅시다.
<div class="sk-circle1 sk-circle">a</div>
에서
<div class="1-sk-circle">a</div>
로 말이지요. 즉 뒷 부분의 sk-circle 을 완전히 날려버리는 것입니다. 
이를 위해서 두 개의 캡쳐그룹이 필요합니다. 일단, "" 안에 전체 문자열을 건드려야 하기 때문에

(sk-circle\d sk-circle)
과 같이 전체 패턴에 해당하는 캡쳐 그룹이 필요하지요. 
그 다음에, 숫자 부분만 다시 뽑아내야 하므로

(sk-circle(\d) sk-circle)
와 같이 해야 됩니다. 
문제는 위와 같이 캡쳐 그룹이 중첩되었을 때 어느 것이 $1 이고 $2 인지 알아야 하는데, 
괄호가 열리는 순서대로 $1, $2, ... 로 진행한다고 생각하면 됩니다. 
즉 해당 패턴 전체 캡쳐 그룹이 $1 이고 \d 에 해당 하는 캡쳐 그룹이 $2 가 되죠.

따라서 치환될 패턴은

$2-sk-circle
이 됨을 알 수 있겠네요. 실제로 코드를 작성해보면

#include <iostream>
#include <regex>

int main() {
  std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

  std::regex re(R"r((sk-circle(\d) sk-circle))r");
  std::smatch match;

  std::string modified_html = std::regex_replace(html, re, "$2-sk-circle");
  std::cout << modified_html;
}

성공적으로 컴파일 하였다면
<실행 결과>
<div class="social-login">
  <div class="small-comment">다음으로 로그인 </div>
  <div>
    <i class="xi-facebook-official fb-login"></i>
    <i class="xi-google-plus goog-login"></i>
  </div>
</div>
<div class="manual">
  <div class="small-comment">
    또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
  </div>
  <input name="name" id="name" placeholder="이름">
  <input name="password" id="password" type="password" placeholder="비밀번호">
</div>
<div id="adding-comment" class="sk-fading-circle">
  <div class="1-sk-circle">a</div>
  <div class="2-sk-circle">b</div>
  <div class="3-sk-circle">asd</div>
  <div class="4-sk-circle">asdfasf</div>
  <div class="5-sk-circle">123</div>
  <div class="6-sk-circle">aax</div>
  <div class="7-sk-circle">sxz</div>
</div>
와 같이 잘 바뀌었음을 알 수 있습니다.

자 그럼 이것으로 C++ 정규 표현식 라이브러리를 어떻게 사용하는지 간단하게 알아보았습니다. 

//================================================================================
void 정규식 테스트()
{

	//using namespace std;
	bool bret;

	//---ansi
	std::string strin;
	strin = "010-9734-4522";
	std::regex e("^010-\\d{4}-\\d{4}$");
	bret = 0;
	bret = std::regex_match(strin, e);

	//----unicode
	CString s;
	std::wstring wstrin;
	s = _T("010-9744-7788");
	wstrin = s.GetString();
	std::wregex ew(_T("^010-\\d{4}-\\d{4}$"));
	bret = 0;
	bret = std::regex_match(wstrin, ew);


	if (bret) {	AfxMessageBox(_T("패턴과 일치하는 문자가 있음: OK"), MB_ICONINFORMATION); }
	else      { AfxMessageBox(_T("패턴과 일치하는 문자가 없음: Failed!"), MB_ICONEXCLAMATION);	}
}


// regex_match example
#include <iostream>
#include <string>
#include <regex>

int main ()
{

  if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
    std::cout << "string literal matched\n";

  const char cstr[] = "subject";
  std::string s ("subject");
  std::regex e ("(sub)(.*)");

  if (std::regex_match (s,e))
    std::cout << "string object matched\n";

  if ( std::regex_match ( s.begin(), s.end(), e ) )
    std::cout << "range matched\n";

  std::cmatch cm;    // same as std::match_results<const char*> cm;
  std::regex_match (cstr,cm,e);
  std::cout << "string literal with " << cm.size() << " matches\n";

  std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
  std::regex_match (s,sm,e);
  std::cout << "string object with " << sm.size() << " matches\n";

  std::regex_match ( s.cbegin(), s.cend(), sm, e);
  std::cout << "range with " << sm.size() << " matches\n";

  // using explicit flags:
  std::regex_match ( cstr, cm, e, std::regex_constants::match_default );

  std::cout << "the matches were: ";
  for (unsigned i=0; i<cm.size(); ++i) {
    std::cout << "[" << cm[i] << "] ";
  }

  std::cout << std::endl;

  return 0;
}

//=========================================================================================================================
typedef sub_match<const char*> csub_match;
typedef sub_match<const wchar_t*> wcsub_match;
typedef sub_match<string::const_iterator> ssub_match;
typedef sub_match<wstring::const_iterator> wssub_match;

// 20090908 pumpguy Add
#ifdef _UNICODE
typedef wcsub_match _tcsub_match ;
typedef wssub_match _tssub_match ;
#else
typedef csub_match _tcsub_match ;
typedef ssub_match _tssub_match ;
#endif
// 20090908 pumpguy Add End

 

 

typedef basic_regex<char> regex;
typedef basic_regex<wchar_t> wregex;
typedef match_results<const char*> cmatch;
typedef match_results<const wchar_t*> wcmatch;
typedef match_results<string::const_iterator> smatch;
typedef match_results<wstring::const_iterator> wsmatch;

// 20090908 pumpguy Add
#ifdef _UNICODE
typedef wregex _tregex ;
typedef wcmatch _tcmatch ;
typedef wsmatch _tsmatch ;
#else
typedef regex _tregex ;
typedef cmatch _tcmatch ;
typedef smatch _tsmatch ;
#endif
// 20090908 pumpguy Add End

 

 

typedef regex_iterator<const char*> cregex_iterator;
typedef regex_iterator<const wchar_t*> wcregex_iterator;
typedef regex_iterator<string::const_iterator> sregex_iterator;
typedef regex_iterator<wstring::const_iterator> wsregex_iterator;

// 20090908 pumpguy Add
#ifdef _UNICODE
typedef wcregex_iterator _tcregex_iterator ;
typedef wsregex_iterator _tsregex_iterator ;
#else
typedef cregex_iterator _tcregex_iterator ;
typedef sregex_iterator _tsregex_iterator ;
#endif
// 20090908 pumpguy Add End

 

typedef regex_token_iterator<const char*> cregex_token_iterator;
typedef regex_token_iterator<const wchar_t*> wcregex_token_iterator;
typedef regex_token_iterator<string::const_iterator> sregex_token_iterator;
typedef regex_token_iterator<wstring::const_iterator> wsregex_token_iterator;

// 20090908 pumpguy Add
#ifdef _UNICODE
typedef wcregex_token_iterator _tcregex_token_iterator ;
typedef wsregex_token_iterator _tsregex_token_iterator ;
#else
typedef cregex_token_iterator _tcregex_token_iterator ;
typedef sregex_token_iterator _tsregex_token_iterator ;
#endif
// 20090908 pumpguy Add End

_tXXXXXX 로 쓰면, Project에서 설정된 CodePage로 지정된다.. ㅎㅎ

참고로, std::string, std::wstring도 위와 같이 _tstring으로 묶어서 써보면 편할것이다..
[출처] regex 사용시 Unicode에 대한 꽁수~|작성자 연시아범


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
Metacharacters Defined
MChar	Definition
^	Start of a string.
$	End of a string.
.	Any character (except \n newline)
|	Alternation.
{...}	Explicit quantifier notation.
[...]	Explicit set of characters to match.
(...)	Logical grouping of part of an expression.
*	0 or more of previous expression.
+	1 or more of previous expression.
?	0 or 1 of previous expression; also forces minimal matching when an expression might match several strings within a search string.
\	Preceding one of the above, it makes it a literal instead of a special character. Preceding a special matching character, see below.

Metacharacter Examples
Pattern	Sample Matches
^abc	abc, abcdefg, abc123, ...
abc$	abc, endsinabc, 123abc, ...
a.c	abc, aac, acc, adc, aec, ...
bill|ted	ted, bill
ab{2}c	abbc
a[bB]c	abc, aBc
(abc){2}	abcabc
ab*c	ac, abc, abbc, abbbc, ...
ab+c	abc, abbc, abbbc, ...
ab?c	ac, abc
a\sc	a c

Character Escapes http://tinyurl.com/5wm3wl
Escaped Char	Description
ordinary characters	Characters other than . $ ^ { [ ( | ) ] } * + ? \ match themselves.
\a	Matches a bell (alarm) \u0007.
\b	Matches a backspace \u0008 if in a []; otherwise matches a word boundary (between \w and \W characters).
\t	Matches a tab \u0009.
\r	Matches a carriage return \u000D.
\v	Matches a vertical tab \u000B.
\f	Matches a form feed \u000C.
\n	Matches a new line \u000A.
\e	Matches an escape \u001B.
\040	Matches an ASCII character as octal (up to three digits); numbers with no leading zero are backreferences if they have only one digit or if they correspond to a capturing group number. (For more information, see Backreferences.) For example, the character \040 represents a space.
\x20	Matches an ASCII character using hexadecimal representation (exactly two digits).
\cC	Matches an ASCII control character; for example \cC is control-C.
\u0020	Matches a Unicode character using a hexadecimal representation (exactly four digits).
\*	When followed by a character that is not recognized as an escaped character, matches that character. For example, \* is the same as \x2A.


Character Classes http://tinyurl.com/5ck4ll
Char Class	Description
.	Matches any character except \n. If modified by the Singleline option, a period character matches any character. For more information, see Regular Expression Options.
[aeiou]	Matches any single character included in the specified set of characters.
[^aeiou]	Matches any single character not in the specified set of characters.
[0-9a-fA-F]	Use of a hyphen (–) allows specification of contiguous character ranges.
\p{name}	Matches any character in the named character class specified by {name}. Supported names are Unicode groups and block ranges. For example, Ll, Nd, Z, IsGreek, IsBoxDrawing.
\P{name}	Matches text not included in groups and block ranges specified in {name}.
\w	Matches any word character. Equivalent to the Unicode character categories [\p{Ll}\p{Lu}\p{Lt}\p{Lo}\p{Nd}\p{Pc}]. If ECMAScript-compliant behavior is specified with the ECMAScript option, \w is equivalent to [a-zA-Z_0-9].
\W	Matches any nonword character. Equivalent to the Unicode categories [^\p{Ll}\p{Lu}\p{Lt}\p{Lo}\p{Nd}\p{Pc}]. If ECMAScript-compliant behavior is specified with the ECMAScript option, \W is equivalent to [^a-zA-Z_0-9].
\s	Matches any white-space character. Equivalent to the Unicode character categories [\f\n\r\t\v\x85\p{Z}]. If ECMAScript-compliant behavior is specified with the ECMAScript option, \s is equivalent to [ \f\n\r\t\v].
\S	Matches any non-white-space character. Equivalent to the Unicode character categories [^\f\n\r\t\v\x85\p{Z}]. If ECMAScript-compliant behavior is specified with the ECMAScript option, \S is equivalent to [^ \f\n\r\t\v].
\d	Matches any decimal digit. Equivalent to \p{Nd} for Unicode and [0-9] for non-Unicode, ECMAScript behavior.
\D	Matches any nondigit. Equivalent to \P{Nd} for Unicode and [^0-9] for non-Unicode, ECMAScript behavior.




////////////////////////////////////////////////////////////////////////////////////////////

/*
	std::wregex re(strptn);
	bret = std::regex_match(strin, re);
*/

/*
regex_search는 검색하는 문장의 가장 첫번째 검색된 결과만 가져온다...



만약 Text내의 모든 검색된 결과를 가져올려면 아래와 같이 사용하면 된다.



CString strRtn = _T("");

 std::tr1::_tregex rgPattern(_T("(\\\\[f|C].*?;)"));

 _tstring tstrMText = CString2string(m_strMText);

 std::tr1::_tsregex_token_iterator p(tstrMText.begin(), tstrMText.end(), rgPattern, 0);
 std::tr1::_tsregex_token_iterator end;

 for (;p != end; ++p)
 {
  strRtn += string2CString(_tstring(p->first, p->second));
 }
 strRtn = _T("{") + strRtn + strTrans + _T("}");
 return strRtn;
[출처] regex_search에 대한 고찰|작성자 연시아범*
*/