
// dRAST3eDlg.h: 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "TAB_TEMPERATURE.h"
#include "TAB_IO.h"
#include "GRIPPER_subject.h"

// CdRAST3eDlg 대화 상자
class CdRAST3eDlg : public CDialogEx, public Observer<GRIPPERSubject>
{
// 생성입니다.
public:
	CdRAST3eDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	TAB_TEMPERATURE m_tab_temperature;
	TAB_IO m_tab_io;
	CWnd* m_pwnShow;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAST3E_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedOk();
	CTabCtrl m_mainTap;
	//afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonTest();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	COLORREF color_check_gripper = RGB(200, 0, 0);
	COLORREF get_Panel = RGB(200, 0, 0);
	COLORREF put_Panel = RGB(0, 200, 0);

	virtual void update(GRIPPERSubject* subject);
};
