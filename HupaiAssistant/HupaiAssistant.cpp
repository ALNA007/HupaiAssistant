
// HupaiAssistant.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HupaiAssistant.h"
#include "MainDlg.h"
#include "TinyXML/tinyxml.h"
#include "tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//--------------------------------------------------------------------------------------------------

//
// Class: Setting
//

Settings::Bid::Bid() {

	trigger_time = Tools::MakeTime(0, 0, 0, 0);				// �Զ�����ʱ�䣨���ڵ�ǰʱ��ſ��Դ����Զ�������
	add_price = 300;										// ��ͼۻ����ϵļӼ۷���
	commit_advance = 0;										// ��ǰ������
	commit_delay = Tools::MakeTime(0, 0, 0, 0);				// ���������ʱ���ӳٶ���ʱ�����ύ��
	commit_before = Tools::MakeTime(11, 29, 56, 0);			// �����ʱ��ʱǿ���ύ
}


Settings::Settings() {

	LoadSettings();
}


BOOL Settings::LoadSettings() {

	TiXmlDocument config_doc(CONFIG_FILE_PATH);
	TiXmlElement *eRoot, *e, *e1;


	//
	// ���������ļ�
	//
	config_doc.LoadFile(TIXML_ENCODING_UTF8);
	ASSERT(eRoot = config_doc.RootElement());

	//
	// ��ȡ�����ļ�����
	//
	ASSERT(cfg_version = eRoot->Attribute("version"));
	ASSERT(cfg_time = eRoot->Attribute("time"));
	ASSERT(cfg_desc = eRoot->Attribute("description"));
	const char *pMode;
	ASSERT(pMode = eRoot->Attribute("mode"));
	if(0 == strcmp(pMode, "moni")) {
		this->isRealMode = FALSE;
	} else if(0 == strcmp(pMode, "real")) {
		this->isRealMode = TRUE;
	} else {
		return FALSE;
	}
	
	//
	// ��ȡ����������Ϣ
	//
	ASSERT(e = eRoot->FirstChildElement("BidInfo"));
	// ��������
	ASSERT(e1 = e->FirstChildElement("BidDate"));
	this->bid_date = e1->GetText();
	// ���Ľ���ʱ��
	ASSERT(e1 = e->FirstChildElement("EndTime"));
	this->bid_time = e1->GetText();
	// ����ָ��
	ASSERT(e1 = e->FirstChildElement("Amount"));
	this->bid_amount = e1->GetText();
	// ��ʾ��
	ASSERT(e1 = e->FirstChildElement("CapPrice"));
	this->bid_cap_price = e1->GetText();

	//
	// ��ȡIE���������
	//
	ASSERT(e = eRoot->FirstChildElement("IE"));
	// �������С
	ASSERT(e1 = e->FirstChildElement("Width"));
	this->ie_width = atoi(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("Height"));
	this->ie_height = atoi(e1->GetText());
	// URL
	ASSERT(e1 = isRealMode ? e->FirstChildElement("URL") : e->FirstChildElement("URL_Practice"));
	this->ie_url = e1->GetText();

	//
	// ��ȡ�ͻ��˲����£�������ť��λ������
	//
	ASSERT(e = isRealMode ? eRoot->FirstChildElement("Position_alltobid") : eRoot->FirstChildElement("Position_51hupai"));
	// �ο��������
	ASSERT(e1 = e->FirstChildElement("Index"));
	this->pt_index = Tools::PointFromStr(e1->GetText());
	// �Ӽ�
	ASSERT(e1 = e->FirstChildElement("JJ_Input"));
	this->pt_jiajia_input = Tools::PointFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("JJ_Button"));
	this->pt_jiajia = Tools::PointFromStr(e1->GetText());
	// ����
	ASSERT(e1 = e->FirstChildElement("CJ_Input"));
	this->pt_chujia_input = Tools::PointFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("CJ_Button"));
	this->pt_chujia = Tools::PointFromStr(e1->GetText());
	// ��֤�벿��
	ASSERT(e1 = e->FirstChildElement("YZM_Input"));
	this->pt_yzm_input = Tools::PointFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("YZM_Refresh"));
	this->pt_yzm_refresh = Tools::PointFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("YZM_Submit"));
	this->pt_yzm_ok = Tools::PointFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("YZM_Cancle"));
	this->pt_yzm_cancle = Tools::PointFromStr(e1->GetText());
	// ȷ�ϰ�ť����ָ������ť���
	ASSERT(e1 = e->FirstChildElement("OK_Button"));
	this->pt_ok = Tools::PointFromStr(e1->GetText());
	// OCR����ʶ�𲿷֣�����
	ASSERT(e1 = e->FirstChildElement("OCR_Time"));
	this->rgn_ocr_time = Tools::RectFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("OCR_Price"));
	this->rgn_ocr_price = Tools::RectFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("YZM_Picture"));
	this->rgn_yzm_picture = Tools::RectFromStr(e1->GetText());
	ASSERT(e1 = e->FirstChildElement("YZM_Info"));
	this->rgn_yzm_info = Tools::RectFromStr(e1->GetText());

	//
	// �ȼ�����
	//
	ASSERT(e = eRoot->FirstChildElement("HotKey"));
	// ����Ĭ�Ϸ������ԣ���48s+700��
	ASSERT(e1 = e->FirstChildElement("StartFJ"));
	this->hotkey_start_fuji = Tools::LongFromStr(e1->GetText());
	// ���ȷ�ϰ�ť���Ի������һ����ť�����
	ASSERT(e1 = e->FirstChildElement("PressOK"));
	this->hotkey_ok = Tools::LongFromStr(e1->GetText());
	// ˢ����֤��
	ASSERT(e1 = e->FirstChildElement("PressRefresh"));
	this->hotkey_refresh = Tools::LongFromStr(e1->GetText());
	// �����֤��
	ASSERT(e1 = e->FirstChildElement("ClearYZM"));
	this->hotkey_clear = Tools::LongFromStr(e1->GetText());
	// ���ȷ����֤�밴ť
	ASSERT(e1 = e->FirstChildElement("PressConfirm"));
	this->hotkey_confirm = Tools::LongFromStr(e1->GetText());
	// ���ȡ����֤�밴ť
	ASSERT(e1 = e->FirstChildElement("PressCancle"));
	this->hotkey_cancle = Tools::LongFromStr(e1->GetText());
	// �˳��κ��Զ�ģʽ
	ASSERT(e1 = e->FirstChildElement("Enter"));
	this->hoteky_enter = Tools::LongFromStr(e1->GetText());
	// �˳��κ��Զ�ģʽ
	ASSERT(e1 = e->FirstChildElement("Escape"));
	this->hoteky_escape = Tools::LongFromStr(e1->GetText());


	//
	// ��ȡ����ģʽ & ��������
	//
	ASSERT(e = eRoot->FirstChildElement("AutoBid"));
	// ����ָ��ʱ���Զ����� �� �ֶ����� ��AutoTrigger = 0 �� 1��
	ASSERT(e1 = e->FirstChildElement("AutoTrigger"));
	bid.auto_trigger = ("1" == e1->GetText()) ? TRUE : FALSE;
	ASSERT(e1 = e->FirstChildElement("TriggerTime"));
	bid.trigger_time = Tools::TimeFromStr(e1->GetText());
	// ��ͼۼӼ���
	ASSERT(e1 = e->FirstChildElement("AddPrice"));
	bid.add_price = atoi(e1->GetText());
	// ��ǰ���ٳ��ۣ�
	ASSERT(e1 = e->FirstChildElement("CommitAdvance"));
	bid.commit_advance = atoi(e1->GetText());
	// ���������ʱ���ӳٶ���ʱ���ٳ��ۣ�
	ASSERT(e1 = e->FirstChildElement("CommitDelay"));
	bid.commit_delay = atoi(e1->GetText());
	// �������ʱ�䣺�ڴ�ʱ�������ۣ�
	ASSERT(e1 = e->FirstChildElement("CommitBefore"));
	bid.commit_before = atoi(e1->GetText());

	//
	// ������Ϣ���ؽ���
	//
	return TRUE;
}


BOOL Settings::SaveSettings() {

	return TRUE;
}


Status::Status() {
	serverHour = serverMinute = serverSecond = 0;
	serverDelay = 0;
	price = 0;
}

//--------------------------------------------------------------------------------------------------


//
// CHupaiAssistantApp
//

BEGIN_MESSAGE_MAP(CHupaiAssistantApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CHupaiAssistantApp::CHupaiAssistantApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


CHupaiAssistantApp theApp;


BOOL CHupaiAssistantApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

