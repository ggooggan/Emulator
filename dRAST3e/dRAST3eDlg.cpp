
// dRAST3eDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "dRAST3e.h"
#include "dRAST3eDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "uiMain.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// CdRAST3eDlg 대화 상자



CdRAST3eDlg::CdRAST3eDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAST3E_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdRAST3eDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_mainTap);
	//DDX_Control(pDX, IDC_BUTTON_TCP_DELAY, mButton_TCPDELAY);
}

BEGIN_MESSAGE_MAP(CdRAST3eDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Connect, &CdRAST3eDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDOK, &CdRAST3eDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Main, &CdRAST3eDlg::OnTcnSelchangeTabMain)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CdRAST3eDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_TCP_DELAY, &CdRAST3eDlg::OnBnClickedButtonTCPDELAY)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CdRAST3eDlg 메시지 처리기

BOOL CdRAST3eDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	GRIPPERSubject::getInstance().attach(*this);
	ADPSubject::getInstance().attach(*this);

	// https://3001ssw.tistory.com/14
	this->m_mainTap.SetCurSel(0);


	CString strTab = _T("");
	strTab.Format(_T("IO"));
	this->m_mainTap.InsertItem(0, strTab);
	strTab.Format(_T("TEMP"));
	this->m_mainTap.InsertItem(1, strTab);

	CRect rect;
	this->m_mainTap.GetClientRect(&rect);

	this->m_tab_io.Create(IDD_DIALOG_IO, &this->m_mainTap);
	this->m_tab_io.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	this->m_tab_io.ShowWindow(SW_SHOW);

	this->m_tab_temperature.Create(IDD_DIALOG_TEMP, &this->m_mainTap);
	this->m_tab_temperature.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	this->m_tab_temperature.ShowWindow(SW_HIDE);

	CString init_Delay;
	init_Delay = "1";
	GetDlgItem(IDC_EDIT_TCP_DELAY)->SetWindowTextW(init_Delay);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CdRAST3eDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CdRAST3eDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CdRAST3eDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CEdit* pEdit;
void CdRAST3eDlg::OnBnClickedButtonConnect()
{
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Log);
	uiMain::getInstance().setLogEdit(pEdit);
	uiMain::getInstance().unit_connect();
}

void CdRAST3eDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

void CdRAST3eDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDC_TAB_Main == pNMHDR->idFrom)
	{
		int iSelect = this->m_mainTap.GetCurSel();

		switch (iSelect)
		{
		case 0:
			this->m_tab_io.ShowWindow(SW_SHOW);
			this->m_tab_temperature.ShowWindow(SW_HIDE);

			break;

		case 1:
			this->m_tab_io.ShowWindow(SW_HIDE);
			this->m_tab_temperature.ShowWindow(SW_SHOW);
			break;

		default:
			break;
		}
	}
	*pResult = 0;
}


void CdRAST3eDlg::OnBnClickedButtonTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	color_check_gripper = RGB(200, 0, 0);
	GetDlgItem(IDC_STATIC_DISPENSING)->Invalidate();
	GetDlgItem(IDC_STATIC_COOLINGDISPENSNG)->Invalidate();
	GetDlgItem(IDC_STATIC_GRIPPER)->Invalidate();
	GetDlgItem(IDC_STATIC_TIPALIGNER)->Invalidate();
	GetDlgItem(IDC_STATIC_STAGE)->Invalidate();

	gripper_command::getInstance().panelCheck_init(); // 상태 초기화

	
}
void CdRAST3eDlg::OnBnClickedButtonTCPDELAY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString value;
	GetDlgItem(IDC_EDIT_TCP_DELAY)->GetWindowTextW(value);

	int nTestNum;
	nTestNum = _ttoi(value) * 1000;
	uiMain::getInstance().tcp_delay(nTestNum);


}



HBRUSH CdRAST3eDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_GRIPPER) {
		// 첫번째 스태틱 컨트롤을 위해 OnCtlColor 함수가 호출된 경우.
		// 스태틱 컨트롤의 텍스트 색상을 설정한다.
		pDC->SetBkColor(color_check_gripper);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DISPENSING) {
		pDC->SetBkColor(color_check_gripper);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_COOLINGDISPENSNG) {
		pDC->SetBkColor(color_check_gripper);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIPALIGNER) {
		pDC->SetBkColor(color_check_gripper);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_STAGE) {
		pDC->SetBkColor(color_check_gripper);
	}

	return hbr;
}


void CdRAST3eDlg::update(GRIPPERSubject* subject)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 바로 변경 하면, 보이지 않음...

	std::string message = subject->getMessage();

	int index_space = message.find("@");
	std::string command = message.substr(0, index_space);
	std::string command_value = message.substr(index_space + 1);

	if (command_value == "ON")		color_check_gripper = RGB(0, 200, 0);
	else 		color_check_gripper = RGB(200, 0, 0);

	if (command == "DISPENSING")GetDlgItem(IDC_STATIC_DISPENSING)->Invalidate();
	else if (command == "COOLING")GetDlgItem(IDC_STATIC_COOLINGDISPENSNG)->Invalidate();
	else if (command == "GRIPPER") GetDlgItem(IDC_STATIC_GRIPPER)->Invalidate();
	else if (command == "STAGE") GetDlgItem(IDC_STATIC_STAGE)->Invalidate();

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void CdRAST3eDlg::update(ADPSubject* subject)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 바로 변경 하면, 보이지 않음...

	std::string message = subject->getMessage();

	int index_space = message.find("@");
	std::string command = message.substr(0, index_space);
	std::string command_value = message.substr(index_space + 1);

	if (command_value == "ON")		color_check_gripper = RGB(0, 200, 0);
	else 		color_check_gripper = RGB(200, 0, 0);

	if (command == "ALIGNER")GetDlgItem(IDC_STATIC_TIPALIGNER)->Invalidate();

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}