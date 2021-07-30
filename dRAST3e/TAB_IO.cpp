// TAB_IO.cpp: 구현 파일
//

#include <vector>
#include "pch.h"
#include "dRAST3e.h"
#include "TAB_IO.h"
#include "afxdialogex.h"
#include "io.h"
// TAB_IO 대화 상자

IMPLEMENT_DYNAMIC(TAB_IO, CDialogEx)

TAB_IO::TAB_IO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IO, pParent)
{

}

TAB_IO::~TAB_IO()
{
}

void TAB_IO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	/* Default */
	CString barout_1, barout_2;
	barout_1 = "SAMPLE";
	barout_2 = "SAMPLE,CARTRIDGE";

	GetDlgItem(IDC_EDIT_BAROUT01)->SetWindowTextW(barout_1);
	GetDlgItem(IDC_EDIT_BAROUT02)->SetWindowTextW(barout_2);

	for(int nIO = 1201  ; nIO <= 1279; nIO++)
		((CButton*)GetDlgItem(nIO))->SetCheck(1);

	std::vector<int> io_Value;
	for (int nIO = 1201; nIO <= 1279; nIO++)
	{
		bool bCheck = ((CButton*)GetDlgItem(nIO))->GetCheck();
		if (bCheck) io_Value.push_back(1);
		else io_Value.push_back(0);
	}

	io_command::getInstance().setValue(std::string(CT2CA(barout_1.operator LPCWSTR())), std::string(CT2CA(barout_2.operator LPCWSTR())), io_Value);
}


BEGIN_MESSAGE_MAP(TAB_IO, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BarcodeAply, &TAB_IO::OnBnClickedButtonBarcodeaply)
END_MESSAGE_MAP()


// TAB_IO 메시지 처리기


void TAB_IO::OnBnClickedButtonBarcodeaply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::vector<int> io_Value;
	for (int nIO = 1201; nIO <= 1279; nIO++)
	{
		bool bCheck = ((CButton*)GetDlgItem(nIO))->GetCheck();
		if (bCheck) io_Value.push_back(1);
		else io_Value.push_back(0);
	}

	CString barout_1, barout_2;

	GetDlgItem(IDC_EDIT_BAROUT01)->GetWindowTextW(barout_1);
	GetDlgItem(IDC_EDIT_BAROUT02)->GetWindowTextW(barout_2);

	io_command::getInstance().setValue(std::string(CT2CA(barout_1.operator LPCWSTR())), std::string(CT2CA(barout_2.operator LPCWSTR())), io_Value);
}
