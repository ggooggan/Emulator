#pragma once


// TAB1 대화 상자

class TAB1 : public CDialog
{
	DECLARE_DYNAMIC(TAB1)

public:
	TAB1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TAB1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAST3E_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
