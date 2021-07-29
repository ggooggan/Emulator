// TAB_IO.cpp: 구현 파일
//

#include "pch.h"
#include "dRAST3e.h"
#include "TAB_IO.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(TAB_IO, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_IO_1, &TAB_IO::OnBnClickedCheckIo1)
	ON_BN_CLICKED(IDC_CHECK_IO_2, &TAB_IO::OnBnClickedCheckIo2)
END_MESSAGE_MAP()


// TAB_IO 메시지 처리기

/* click */

void TAB_IO::OnBnClickedCheckIo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void TAB_IO::OnBnClickedCheckIo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
