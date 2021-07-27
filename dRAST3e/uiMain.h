#pragma once
#include "Singleton.h"
#include "afxdialogex.h"
#include "adp.h"
#include "gripper.h"
#include "TCP_subject.h"

class uiMain : public Singleton<uiMain>, public Observer<TCPSubject>
{
public:
	void setLogEdit(CEdit* edit)
	{
		TCPSubject::getInstance().attach(*this);
		edit_Log = edit;
		CString String;
		String = "emulator";
		edit->SetWindowTextW(String);
	}

	void unit_connect()
	{
		// test ¸ñÀû
		unit_adp::getInstance().thread_connect(123);
		unit_gripper::getInstance().thread_connect(456);
	}

	virtual void update(TCPSubject* subject)
	{
		CString copy;
		CString aaaa(subject->getMessage().c_str());

		edit_Log->GetWindowTextW(copy);


		edit_Log->SetWindowTextW(copy + "\r\n" + aaaa);
	}
private:
	CEdit* edit_Log = nullptr;

};
