// TAB_TEMPERATURE.cpp: 구현 파일
//

#include "pch.h"
#include "dRAST3e.h"
#include "TAB_TEMPERATURE.h"
#include "afxdialogex.h"
#include "temperature.h"

// TAB_TEMPERATURE 대화 상자

IMPLEMENT_DYNAMIC(TAB_TEMPERATURE, CDialogEx)

TAB_TEMPERATURE::TAB_TEMPERATURE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEMP, pParent)
{
	
}

TAB_TEMPERATURE::~TAB_TEMPERATURE()
{
}

void TAB_TEMPERATURE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	/* default */ 
	GetDlgItem(IDC_EDIT_TEMP1)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP2)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP3)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP4)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP5)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP6)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP7)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP8)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP9)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP10)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP11)->SetWindowTextW(_T("0.0"));
	GetDlgItem(IDC_EDIT_TEMP12)->SetWindowTextW(_T("0.0"));


}


BEGIN_MESSAGE_MAP(TAB_TEMPERATURE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEMPAPLY, &TAB_TEMPERATURE::OnBnClickedButtonTempaply)
END_MESSAGE_MAP()


// TAB_TEMPERATURE 메시지 처리기


void TAB_TEMPERATURE::OnBnClickedButtonTempaply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str; 
	str = _T("asdfasdf");
	
	GetDlgItem(IDC_EDIT_TEMP1)->SetWindowTextW(str);
	// 설정된 온도 읽어서 전달.
	temperature_command::getInstance().setValue("123123");

	UpdateData();
}
