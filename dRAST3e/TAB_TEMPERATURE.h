#pragma once


// TAB_TEMPERATURE 대화 상자

class TAB_TEMPERATURE : public CDialogEx
{
	DECLARE_DYNAMIC(TAB_TEMPERATURE)

public:
	TAB_TEMPERATURE(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TAB_TEMPERATURE();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTempaply();
	CEdit tmp01;
};
