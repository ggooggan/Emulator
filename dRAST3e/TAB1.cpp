// TAB1.cpp: 구현 파일
//

#include "pch.h"
#include "dRAST3e.h"
#include "TAB1.h"
#include "afxdialogex.h"


// TAB1 대화 상자

IMPLEMENT_DYNAMIC(TAB1, CDialog)

TAB1::TAB1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DRAST3E_DIALOG, pParent)
{

}

TAB1::~TAB1()
{
}

void TAB1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TAB1, CDialog)
END_MESSAGE_MAP()


// TAB1 메시지 처리기
