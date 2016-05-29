
// HupaiAssistant.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"					// ������

#define CONFIG_FILE_PATH				"./config.xml"


class Settings
{
public:
	Settings();

public:
	// ���������ļ� & ��������
	BOOL LoadSettings(void);
	BOOL SaveSettings(void);

public:
//------------------------------------------------------------------------------
	//
	// �����ļ��汾��Ϣ
	//
	CString cfg_version;
	CString cfg_time;
	CString cfg_desc;
	BOOL	isRealMode;

	//
	// ������Ϣ
	//
	CString bid_date;
	CString bid_time;
	CString bid_amount;
	CString bid_cap_price;

	//
	// IE���������
	//
	int ie_width;
	int ie_height;
	CString ie_url;

	//
	// ����ϵͳ���沼��
	//
	CPoint pt_index;					// �ο��㣨������Ͻǵĵ㣩�ڿͻ�����λ��
	CPoint pt_jiajia;					// �Ӽ۰�ť
	CPoint pt_jiajia_input;				// �Ӽ������
	CPoint pt_chujia;					// ���۰�ť
	CPoint pt_chujia_input;				// �۸������
	CPoint pt_yzm_input;				// ��֤�룺����
	CPoint pt_yzm_refresh;				// ��֤�룺ˢ��
	CPoint pt_yzm_ok;					// ��֤�룺ȷ��
	CPoint pt_yzm_cancle;				// ��֤�룺ȡ��
	CPoint pt_ok;						// ֻ��һ����ť�������ȷ��
	CRect rgn_ocr_time;					// ����ʶ�𣺷�����ʱ��
	CRect rgn_ocr_price;				// ����ʶ�𣺵�ǰ��ͼ�
	CRect rgn_yzm_picture;				// ��֤��ͼƬ��
	CRect rgn_yzm_info;					// ��֤����ʾ��Ϣ��

	//
	// ϵͳ�ȼ�
	//
	DWORD hotkey_start_fuji;				// ����Ĭ�ϳ��۳��򣨷�����
	DWORD hotkey_ok;
	DWORD hotkey_refresh;
	DWORD hotkey_clear;
	DWORD hotkey_confirm;
	DWORD hotkey_cancle;
	DWORD hoteky_enter;
	DWORD hoteky_escape;

	//
	// �Զ�����ģʽ
	//
	struct Bid {
		Bid();
		BOOL auto_trigger;				// �Զ����������˴���ʱ���Զ����ۣ�
		int trigger_time;				// ����ʱ�䣺һ���еĵڼ�����
		int add_price;					// ��ͼۼӼ۷���
		int commit_advance;				// ��߼���ǰ������
		int commit_delay;				// ������߼��ӳٶ��ٺ������
		int commit_before;				// �������ʱ�䣨ǿ�Ƴ��ۣ�
	} bid;								// == ����ģʽ��48s+700 ==
//------------------------------------------------------------------------------
};


class Status
{
public:
	Status();
	volatile int serverHour;
	volatile int serverMinute;
	volatile int serverSecond;
	volatile int serverDelay;
	volatile int price;
};


class CHupaiAssistantApp : public CWinApp
{
public:
	CHupaiAssistantApp();

public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()

public:
	Settings	settings;
	Status		status;
};

extern CHupaiAssistantApp theApp;
