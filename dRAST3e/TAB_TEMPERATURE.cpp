// TAB_TEMPERATURE.cpp: 구현 파일
//
#include <vector>
#include <boost/lexical_cast.hpp>
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
	for (int nTemp = 1006; nTemp <= 1017; nTemp++)
		GetDlgItem(nTemp)->SetWindowTextW(_T("0.0"));

	std::vector<std::string> temp_Value;
	CString value;

	for (int nTemp = 1006; nTemp <= 1017; nTemp++)
	{
		GetDlgItem(nTemp)->GetWindowTextW(value);
		temp_Value.push_back(std::string(CT2CA(value.operator LPCWSTR())));
	}

	temperature_command::getInstance().setValue(temp_Value);
}


BEGIN_MESSAGE_MAP(TAB_TEMPERATURE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEMPAPLY, &TAB_TEMPERATURE::OnBnClickedButtonTempaply)
END_MESSAGE_MAP()


// TAB_TEMPERATURE 메시지 처리기


void TAB_TEMPERATURE::OnBnClickedButtonTempaply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 설정된 온도 읽어서 전달.

	std::vector<std::string> temp_Value;
	CString value;

	for (int nTemp = 1006; nTemp <= 1017; nTemp++)
	{
		GetDlgItem(nTemp)->GetWindowTextW(value);
		temp_Value.push_back(std::string(CT2CA(value.operator LPCWSTR())));
	}

	temperature_command::getInstance().setValue(temp_Value);

	//UpdateData();
}
