#pragma once


// TAB_IO 대화 상자

class TAB_IO : public CDialogEx
{
	DECLARE_DYNAMIC(TAB_IO)

public:
	TAB_IO(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TAB_IO();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckIo1();
	afx_msg void OnBnClickedCheckIo2();
	afx_msg void OnBnClickedCheckIo3();
	afx_msg void OnBnClickedCheckIo4();
	afx_msg void OnBnClickedCheckIo5();
	afx_msg void OnBnClickedCheckIo6();
	afx_msg void OnBnClickedCheckIo7();
	afx_msg void OnBnClickedCheckIo8();
	afx_msg void OnBnClickedCheckIo9();
	afx_msg void OnBnClickedCheckIo10();
};
