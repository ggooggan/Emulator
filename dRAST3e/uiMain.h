#pragma once
#include "Singleton.h"
#include "afxdialogex.h"

#include "TCP_subject.h"
#include "adp.h"
#include "gripper.h"
#include "temperature.h"
#include "io.h"
#include "stage.h"

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
		unit_adp::getInstance().thread_connect(6000);
		unit_stage::getInstance().thread_connect(7000);
		unit_temperature::getInstance().thread_connect(5000);
		unit_io::getInstance().thread_connect(7500);
		unit_gripper::getInstance().thread_connect(6500);
	}

	virtual void update(TCPSubject* subject)
	{
		CString copy;
		CString msg(subject->getMessage().c_str());

		edit_Log->GetWindowTextW(copy);

		edit_Log->SetWindowTextW(copy + "\r\n" + msg);
		edit_Log->LineScroll(edit_Log->GetLineCount());
	}
private:
	CEdit* edit_Log = nullptr;

};
