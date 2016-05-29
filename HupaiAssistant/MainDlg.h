
// HupaiAssistantDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


#define DISP_WIDTH						500
#define DISP_HEIGHT						300

//
// �ȼ�����
//
#define HOTKEY_START					WM_USER + 1000
#define HOTKEY_OK						WM_USER + 1001
#define HOTKEY_YZM_REFRESH				WM_USER + 1002
#define HOTKEY_YZM_CLEAR				WM_USER + 1003
#define HOTKEY_YZM_OK					WM_USER + 1004
#define HOTKEY_YZM_CANCLE				WM_USER + 1005
#define HOTKEY_ENTER					WM_USER + 1006
#define HOTKEY_ESCAPE					WM_USER + 1007


// CHupaiAssistantDlg �Ի���
class CMainDlg : public CDialogEx
{
public:
	CMainDlg(CWnd* pParent = NULL);
	~CMainDlg();

protected:
	enum { IDD = IDD_MAIN_DIALOG };
	HICON m_hIcon;

	CButton		m_EnableHotKey;			// ��ϵͳ�ȼ���
	BOOL		m_HotKeyEnabled;		// 
	CHotKeyCtrl	m_HotKey;				// �ȼ��ؼ�
	CButton		m_CalcHotKey;			// �����ȼ�ֵ�İ�ť

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	DECLARE_MESSAGE_MAP()

private:
	CRect		rgnDisp;

	CPen		penOutline;
	CFont		font;
	CFont		fontS;
	CFont		fontM;
	CFont		fontL;

	void _RegistHotKey();
	void _UnregisteHotKey();
	void RegistHotKey();
	void UnregisteHotKey();
	// static BOOL IEScreenShot(CDC *, CBitmap *, CRect *);

public:
	// ���ϵͳ��Ϣ��ϵͳʱ�䡢��ǰ��ͼ�
	static volatile BOOL canCheckOCR;
	static volatile BOOL isCheckOCR;
	static void Thread_CheckOCR(void *);
	// ������֤��
	static volatile BOOL canBltYZM;
	static volatile BOOL isBltYZM;
	static void Thread_BltYZM(void *);
	// �Զ������߳�
	static volatile BOOL canAutoConfirm;
	static volatile BOOL isAutoConfirm;
	static void Thread_AutoConfirm(void *);
	afx_msg void OnBnClickedHotkeyMode();
	afx_msg void OnBnClickedHotkeyCalc();
};
